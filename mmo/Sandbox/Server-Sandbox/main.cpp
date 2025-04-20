#include <iostream>
#include "Core/Window.h"
#include <Core/Networking/Networking.h>
#include <Core/Math/Math.h>

int main()
{
	Window window;
	window.Create(L"TCPServer Sandbox", 1280, 720);

	TCPServer server;
	server.Initialize("3001");

	//Send
	NetworkBuffer buffer = (new PositionPacket(Vector2f(1, 2)))->Serialize();

	//Receive
	BasePacket* packet = (new BasePacket())->Deserialize(buffer.data(), buffer.size());

	if (packet->GetType() == BasePacket::PacketType::Position)
	{
		PositionPacket* positionPacket = (new PositionPacket())->Deserialize(buffer.data());
		std::cout << "Position: " << positionPacket->GetPosition() << std::endl;
	}

	while (window.IsOpen())
	{
		window.Update();
		server.Update();
	}
}