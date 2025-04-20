#include "PositionPacket.h"

PositionPacket::PositionPacket()
{
}

PositionPacket::PositionPacket(const Vector2f& position) :
	position(position)
{
}

PositionPacket::~PositionPacket()
{
}

void PositionPacket::Serialize(NetworkBinaryWriter& writer) const
{
	writer.WriteFloat(position.x);
	writer.WriteFloat(position.y);
}

void PositionPacket::Deserialize(NetworkBinaryReader& reader)
{
	position.x = reader.ReadFloat();
	position.y = reader.ReadFloat();
}