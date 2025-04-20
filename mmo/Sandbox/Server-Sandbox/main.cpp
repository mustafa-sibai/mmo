#include <iostream>
#include "Core/Window.h"
#include "Core/Networking/TCPServer.h"
#include "Core/Networking/PacketFactory.h"
#include "Core/Networking/Packets/PositionPacket.h"
#include "Core/Networking/Serialization/NetworkBuffer.h"
#include <Core/Math/Vector2.h>

int main()
{
	Window window;
	window.Create(L"TCPServer Sandbox", 1280, 720);

	TCPServer server;
	server.Initialize("3001");

	PacketFactory packetFactory;

	PositionPacket* positionPacket = new PositionPacket(Vector2f(1, 2));
	const NetworkBuffer buffer = packetFactory.SerializePacket(positionPacket);

	while (window.IsOpen())
	{
		window.Update();
		server.Update();
	}
}