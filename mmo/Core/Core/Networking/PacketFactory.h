#pragma once
#include "Core/API.h"
#include "Core/Networking/Packets/Packet.h"
#include "Core/Networking/Serialization/NetworkBinaryReader.h"
#include "Core/Networking/Serialization/NetworkBinaryWriter.h"
#include "Core/Networking/Packets/BasePacket.h"

class CORE_API PacketFactory
{
public:
	const NetworkBuffer& SerializePacket(BasePacket* packet);
	void DeserializePacket(const uint8_t* buffer, BasePacket& packet);
};