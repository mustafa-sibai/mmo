#include <iostream>
#include "Core/Window.h"
#include "Core/Networking/Server.h"

int main()
{
	Window window;
	window.Create(L"Server Sandbox", 1280, 720);

	Server server;
	server.Initialize("3001");

	while (window.IsOpen())
	{
		window.Update();
		server.Update();
	}
}