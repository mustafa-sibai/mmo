#include "Server.h"
#include <iostream>
#include <ws2tcpip.h>
#include <chrono>
#include <thread>

Server::Server() :
	serverSocket(INVALID_SOCKET), clientSocket(INVALID_SOCKET), clientConnected(false)
{
}

Server::~Server()
{
	if (clientSocket != INVALID_SOCKET)
	{
		closesocket(clientSocket);
	}

	if (serverSocket != INVALID_SOCKET)
	{
		closesocket(serverSocket);
	}

	WSACleanup();
}

void Server::Initialize(const std::string& port)
{
	// Initialize Winsock
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		std::cerr << "WSAStartup failed." << std::endl;
		return;
	}

	struct addrinfo hints = {};
	struct addrinfo* result = nullptr;

	hints.ai_family = AF_INET;       // Allow IPv4
	hints.ai_socktype = SOCK_STREAM;  // TCP socket
	hints.ai_protocol = IPPROTO_TCP;  // TCP protocol
	hints.ai_flags = AI_PASSIVE;      // For binding

	// Resolve the server address and port
	if (getaddrinfo(nullptr, port.c_str(), &hints, &result) != 0)
	{
		std::cerr << "getaddrinfo failed." << std::endl;
		WSACleanup();
		return;
	}

	// Create a socket for the server
	serverSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (serverSocket == INVALID_SOCKET)
	{
		std::cerr << "Socket creation failed." << std::endl;
		freeaddrinfo(result);
		WSACleanup();
		return;
	}


	// Set the socket to non-blocking mode
	u_long mode = 1; // 1 to enable non-blocking mode
	if (ioctlsocket(serverSocket, FIONBIO, &mode) != 0)
	{
		std::cerr << "Failed to set socket to non-blocking mode." << std::endl;
		closesocket(serverSocket);
		freeaddrinfo(result);
		WSACleanup();
		return;
	}

	// Bind the socket
	if (bind(serverSocket, result->ai_addr, (int)result->ai_addrlen) == SOCKET_ERROR)
	{
		std::cerr << "Bind failed." << std::endl;
		freeaddrinfo(result);
		closesocket(serverSocket);
		WSACleanup();
		return;
	}

	freeaddrinfo(result);

	// Listen for incoming connections
	if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR)
	{
		std::cerr << "Listen failed." << std::endl;
		closesocket(serverSocket);
		WSACleanup();
		return;
	}

	std::cout << "Server initialized and listening on port " << port << std::endl;
}

void Server::Update()
{
	if (!clientConnected)
	{
		// Accept a client socket
		clientSocket = accept(serverSocket, nullptr, nullptr);
		if (clientSocket == INVALID_SOCKET)
		{
			int error = WSAGetLastError();
			if (error != WSAEWOULDBLOCK)
			{
				std::cerr << "Accept failed." << std::endl;
			}
			return;
		}

		clientConnected = true;
		std::cout << "Client connected!" << std::endl;
	}

	// Send hello string to the client once connected
	const char* helloMsg = "Hello I am the server!\n";
	int bytesSent = send(clientSocket, helloMsg, static_cast<int>(strlen(helloMsg)), 0);
	if (bytesSent == SOCKET_ERROR)
	{
		std::cerr << "Send failed with error: " << WSAGetLastError() << std::endl;
	}
}