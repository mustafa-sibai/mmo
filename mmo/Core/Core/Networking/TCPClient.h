#pragma once
#include "Core/API.h"
#include <WinSock2.h>
#include <string>

class CORE_API TCPClient
{
private:
	WSADATA wsaData;
	SOCKET clientSocket;
	sockaddr_in serverAddr;
	char buffer[1024] = { 0 };
	bool connected;

public:
	TCPClient();
	~TCPClient();

	void Initialize();
	void Connect(const std::string& ipAddress, const std::string& port);
	void Update();

	u_long GetAvailableData();

	inline bool IsConnected() { return connected; }
};