#include "PositionPacket.h"

PositionPacket::PositionPacket() :
	BasePacket(BasePacket::PacketType::Position),
	position(Vector2f(0, 0))
{
}

PositionPacket::PositionPacket(const Vector2f& position) :
	BasePacket(BasePacket::PacketType::Position),
	position(position)
{
}

PositionPacket::~PositionPacket()
{
}

const NetworkBuffer& PositionPacket::Serialize()
{
	BasePacket::Serialize();
	writer.WriteVector2f(position);
	writer.Seek(sizeof(int32_t));
	writer.WriteInt32(static_cast<int32_t>(writer.GetBuffer().size()), NetworkBinaryWriter::OperationMode::Overwrite);
	return writer.GetBuffer();
}

PositionPacket* PositionPacket::Deserialize(const uint8_t* buffer)
{
	BasePacket::Deserialize(buffer);
	position = reader.ReadVector2f();
	return this;
}