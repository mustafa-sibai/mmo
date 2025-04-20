#include "BasePacket.h"

BasePacket::BasePacket() :
	type(PacketType::Unknown), length(0)
{
}

BasePacket::BasePacket(PacketType type) :
	type(type), length(0)
{
}

BasePacket* BasePacket::Serialize()
{
	writer.Clear();

	writer.WriteInt32(static_cast<int32_t>(type));
	writer.WriteInt32(length);

	return this;
}

BasePacket* BasePacket::Deserialize(const uint8_t* buffer)
{
	reader = NetworkBinaryReader(NetworkBuffer(buffer, buffer + sizeof(BasePacket)));
	type = static_cast<PacketType>(reader.ReadInt32());
	length = reader.ReadInt32();
	return this;
}

BasePacket* BasePacket::Deserialize(const uint8_t* buffer, unsigned long long size)
{
	reader = NetworkBinaryReader(NetworkBuffer(buffer, buffer + size));
	type = static_cast<PacketType>(reader.ReadInt32());
	length = reader.ReadInt32();
	return this;
}