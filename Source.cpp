#pragma comment(lib,"ws2_32.lib") 
#include <WinSock2.h> 
#include <string> 
#include <iostream> 
class chat
{private:
string mensaje
public:
void escribir()
{
cin>>mensaje;
}
void cha(){
recv(Connection,mensaje,sizeof(mensaje),NULL);
cout<<mensaje<<endl;}
};

SOCKET Connection;

void ClientThread()
{
	char buffer[256]; 
	while (true)
	{
		recv(Connection, buffer, sizeof(buffer), NULL); 
		std::cout << buffer << std::endl;
	}
}

int main()
{
	
	WSAData wsaData;
	WORD DllVersion = MAKEWORD(2, 1);
	if (WSAStartup(DllVersion, &wsaData) != 0)
	{
		MessageBoxA(NULL, "Winsock startup failed", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}

	SOCKADDR_IN addr; 
	int sizeofaddr = sizeof(addr); 
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(1111);
	addr.sin_family = AF_INET; 

	Connection = socket(AF_INET, SOCK_STREAM, NULL); 
	if (connect(Connection, (SOCKADDR*)&addr, sizeofaddr) != 0) 
	{
		MessageBoxA(NULL, "Failed to Connect", "Error", MB_OK | MB_ICONERROR);
		return 0; 
	}

	std::cout << "Connected!" << std::endl;
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientThread, NULL, NULL, NULL); 
	char buffer[256]; 
	while (true)
	{
		std::cin.getline(buffer, sizeof(buffer)); 
		send(Connection, buffer, sizeof(buffer), NULL); 
		Sleep(10);
	}
	return 0;
}

