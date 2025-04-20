#include <iostream>
#include "Core/Window.h"
#include "Core/Networking/TCPClient.h"

int main()
{
	Window window;
	window.Create(L"Client Sandbox", 1280, 720);

	TCPClient client;
	client.Initialize();
	client.Connect("127.0.0.1", "3001");

	while (window.IsOpen())
	{
		window.Update();
		client.Update();
	}
}