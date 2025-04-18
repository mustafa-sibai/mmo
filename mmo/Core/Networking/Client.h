#pragma once
#include "../API.h"
#include <WinSock2.h>
#include <string>

class CORE_API Client
{
private:
	WSADATA wsaData;
	SOCKET clientSocket;
	sockaddr_in serverAddr;
	char buffer[1024] = { 0 };
	bool connected;

public:
	Client();
	~Client();

	void Initialize();
	void Connect(const std::string& ipAddress, const std::string& port);
	void Update();

	inline bool IsConnected() { return connected; }
};