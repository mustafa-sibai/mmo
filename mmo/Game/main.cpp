#include <iostream>
#include "Core/Window.h"
#include "Core/Networking/Server.h"
#include "Core/Networking/Client.h"

int main()
{
	Window window;
	window.Create(L"MMO", 1280, 720);

	Server server;
	server.Initialize("3000");

	Client client;
	client.Initialize();
	client.Connect("127.0.0.1", "3000");

	while (window.IsOpen())
	{
		window.Update();
		server.Update();
		client.Update();
	}
}