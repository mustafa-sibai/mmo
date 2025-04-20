#pragma once
#include <Core/Networking/Serialization/NetworkBinaryWriter.h>
#include <Core/Networking/Serialization/NetworkBinaryReader.h>
#include <Core/Math/Vector2.h>
#include "PacketHeader.h"

class BasePacket {
public:
	virtual ~BasePacket() = default;

	virtual void Serialize(NetworkBinaryWriter& writer) const = 0;
	virtual void Deserialize(NetworkBinaryReader& reader) = 0;
	virtual PacketHeader::PacketType GetType() const = 0;
	virtual size_t GetSize() const = 0;
};