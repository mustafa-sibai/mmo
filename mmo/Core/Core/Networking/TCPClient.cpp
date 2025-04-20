#include "TCPClient.h"
#include <iostream>
#include <ws2tcpip.h>
#include <chrono>
#include <thread>
#include "Networking.h"

TCPClient::TCPClient() :
	wsaData(), clientSocket(INVALID_SOCKET), connected(false)
{
}

TCPClient::~TCPClient()
{
	if (clientSocket != INVALID_SOCKET)
	{
		closesocket(clientSocket);
	}

	WSACleanup();
}

void TCPClient::Initialize()
{
	// Initialize Winsock
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		std::cerr << "WSAStartup failed." << std::endl;
		return;
	}
}

void TCPClient::Connect(const std::string& ipAddress, const std::string& port)
{
	struct addrinfo hints = {};
	struct addrinfo* result = nullptr;

	hints.ai_family = AF_INET;			// IPv4
	hints.ai_socktype = SOCK_STREAM;  // TCP socket
	hints.ai_protocol = IPPROTO_TCP;  // TCP protocol

	// Resolve the server address and port
	if (getaddrinfo(ipAddress.c_str(), port.c_str(), &hints, &result) != 0)
	{
		std::cerr << "getaddrinfo failed." << std::endl;
		return;
	}

	// Create a socket for connecting to the server
	clientSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (clientSocket == INVALID_SOCKET)
	{
		std::cerr << "Socket creation failed." << std::endl;
		freeaddrinfo(result);
		WSACleanup();
		return;
	}

	// Set the socket to non-blocking mode
	u_long mode = 1; // 1 to enable non-blocking mode
	if (ioctlsocket(clientSocket, FIONBIO, &mode) != 0)
	{
		std::cerr << "Failed to set socket to non-blocking mode." << std::endl;
		closesocket(clientSocket);
		freeaddrinfo(result);
		WSACleanup();
		return;
	}

	const int maxAttempts = 1;
	int attempts = 0;

	// Connect to the server (non-blocking)
	while (attempts < maxAttempts)
	{
		int resultCode = connect(clientSocket, result->ai_addr, (int)result->ai_addrlen);
		if (resultCode == SOCKET_ERROR)
		{
			int error = WSAGetLastError();
			if (error == WSAEWOULDBLOCK)
			{
				// Connection is in progress, continue looping
				attempts++;
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
				continue;
			}
			else if (error == WSAEISCONN)
			{
				// Connection is complete
				break;
			}
			else
			{
				std::cerr << "Connection failed." << std::endl;
				closesocket(clientSocket);
				freeaddrinfo(result);
				WSACleanup();
				return;
			}
		}
		break;
	}

	freeaddrinfo(result);
	connected = true;
	std::cout << "Connected to the server!" << std::endl;
}

void TCPClient::Update()
{
	if (!connected)
		return;

	//get the size from recv before calling recv
	// Create a buffer to receive data
	NetworkBuffer nb(1024);

	// Receive data from the server
	int bytesReceived = recv(clientSocket, reinterpret_cast<char*>(nb.data()), 1024, 0);
	if (bytesReceived > 0)
	{

	}
	else if (bytesReceived == SOCKET_ERROR)
	{
		if (WSAGetLastError() == WSAEWOULDBLOCK)
		{
			// No data available yet, continue looping
		}
		else
		{
			std::cerr << "Receive failed." << std::endl;
			closesocket(clientSocket);
			WSACleanup();
			return;
		}
	}
}