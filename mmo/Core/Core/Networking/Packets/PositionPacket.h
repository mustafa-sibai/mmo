#pragma once
#include "Core/API.h"
#include "Core/Math/Vector2.h"
#include "Packet.h"
#include "Core/Networking/Packets/BasePacket.h"

class CORE_API PositionPacket : public BasePacket
{
private:
	Vector2f position;

public:
	PositionPacket();
	PositionPacket(const Vector2f& position);
	~PositionPacket();

	void Serialize(NetworkBinaryWriter& writer) const override;
	void Deserialize(NetworkBinaryReader& reader) override;

	inline const Vector2f& GetPosition() const { return position; }

	inline PacketHeader::PacketType GetType() const override { return PacketHeader::PacketType::Position; }
	inline size_t GetSize() const override { return sizeof(PositionPacket); }
};