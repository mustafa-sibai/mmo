#pragma once
#include "Core/API.h"
#include <WinSock2.h>
#include <string>

class CORE_API TCPServer
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
	TCPServer();
	~TCPServer();

	void Initialize(const std::string& port);
	void Update();

	void Send(const NetworkBuffer& buffer);
};