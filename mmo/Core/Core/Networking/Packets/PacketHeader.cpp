#include "PacketHeader.h"

PacketHeader::PacketHeader()
	: type(PacketType::Unknown), length(0)
{
}

PacketHeader::PacketHeader(PacketType type, uint32_t length)
	: type(type), length(length)
{
}

PacketHeader::~PacketHeader()
{
}