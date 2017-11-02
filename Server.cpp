
#pragma comment(lib,"ws2_32.lib")
#include <WinSock2.h>
#include <string>
#include <iostream>

SOCKET Connections[100];
int ConnectionCounter = 0;

void ClientHandlerThread(int index) 
{
	char buffer[256]; 
	while (true)
	{
		recv(Connections[index], buffer, sizeof(buffer), NULL); 
		for (int i = 0; i < ConnectionCounter; i++) 
		{
			if (i == index) 
				continue; 
			send(Connections[i], buffer, sizeof(buffer), NULL);
		}
	}
}

int main()
{
	//Winsock Startup
	WSAData wsaData;
	WORD DllVersion = MAKEWORD(2, 1);
	if (WSAStartup(DllVersion, &wsaData) != 0) 
	{
		MessageBoxA(NULL, "WinSock startup failed", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}

	SOCKADDR_IN addr; 
	int addrlen = sizeof(addr); 
	addr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
	addr.sin_port = htons(1111); 
	addr.sin_family = AF_INET;

	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL); 
	bind(sListen, (SOCKADDR*)&addr, sizeof(addr)); 
	listen(sListen, SOMAXCONN); 

	SOCKET newConnection; 
	int ConnectionCounter = 0; 
	for (int i = 0; i < 100; i++)
	{
		newConnection = accept(sListen, (SOCKADDR*)&addr, &addrlen); 
		if (newConnection == 0) 
		{
			std::cout << "Failed to accept the client's connection." << std::endl;
		}
		else //
		{
			std::cout << "Client Connected!" << std::endl;
			char MOTD[256] = "Welcome! This is the Message of the Day."; 
			send(newConnection, MOTD, sizeof(MOTD), NULL); 
			Connections[i] = newConnection; 
			ConnectionCounter += 1; 
			CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandlerThread, (LPVOID)(i), NULL, NULL); 
		}
	}

	system("pause");
	return 0;
}
