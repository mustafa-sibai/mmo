#pragma once
#include "../API.h"
#include <WinSock2.h>
#include <string>

class CORE_API Server
{
private:
	WSADATA wsaData;
	SOCKET serverSocket;
	sockaddr_in serverAddr;

	SOCKET clientSocket;
	sockaddr_in	clientAddr;
	int clientAddrSize = sizeof(clientAddr);
	bool clientConnected;

public:
	Server();
	~Server();

	void Initialize(const std::string& port);
	void Update();
};