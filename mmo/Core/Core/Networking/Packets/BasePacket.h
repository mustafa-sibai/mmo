#pragma once
#include "Core/API.h"
#include <Core/Networking/Serialization/NetworkBinaryWriter.h>
#include <Core/Networking/Serialization/NetworkBinaryReader.h>
#include <Core/Math/Vector2.h>

class CORE_API BasePacket
{
protected:
	NetworkBinaryWriter writer;
	NetworkBinaryReader reader;

public:
	enum class PacketType
	{
		Unknown = -1,
		Position = 5,
	};

	PacketType type;
	uint32_t length;

	BasePacket();
	BasePacket(PacketType type);
	virtual ~BasePacket() = default;

	BasePacket* Serialize();
	BasePacket* Deserialize(const uint8_t* buffer);
	BasePacket* Deserialize(const uint8_t* buffer, unsigned long long size);

	PacketType GetType() const { return type; }
	size_t GetSize() const { return length; }
};