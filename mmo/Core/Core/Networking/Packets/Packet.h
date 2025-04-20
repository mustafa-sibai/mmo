#pragma once  
#include <Core/Networking/Packets/PacketHeader.h>
#include <Core/Networking/Packets/BasePacket.h>

class Packet
{
private:
	PacketHeader* header;
	BasePacket* body;

public:
	Packet();
	Packet(PacketHeader* header, BasePacket* body);

	inline const PacketHeader* GetHeader() const { return header; }
	inline BasePacket* GetBody() const { return body; }
};