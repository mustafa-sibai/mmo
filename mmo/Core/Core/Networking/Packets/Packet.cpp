#include "Packet.h"

Packet::Packet() :
	header(), body(nullptr)
{
}

Packet::Packet(PacketHeader* header, BasePacket* body) :
	header(header), body(body)
{
}