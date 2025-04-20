#include "PacketFactory.h"
#include "Core/Networking/Packets/Packet.h"

const std::vector<uint8_t>& PacketFactory::SerializePacket(BasePacket* packet)
{
	NetworkBinaryWriter writer = NetworkBinaryWriter();

	// Pass the local header and a pointer to the packet
	Packet packetData(new PacketHeader(packet->GetType(), packet->GetSize()), packet);

	writer.WriteInt32(static_cast<int32_t>(packetData.GetHeader()->type));
	writer.WriteInt32(packetData.GetHeader()->length);

	packetData.GetBody()->Serialize(writer);

	return writer.GetBuffer();
}

void PacketFactory::DeserializePacket(const uint8_t* buffer, BasePacket& packet)
{
	/*Packet packetData;
	NetworkBinaryReader reader = NetworkBinaryReader(std::vector<uint8_t>(buffer, buffer + sizeof(PacketHeader)));
	packetData.header.type = static_cast<PacketHeader::PacketType>(reader.ReadInt32());
	packetData.header.length = reader.ReadInt32();
	packetData.body.Deserialize(reader);
	packet = packetData.body;*/
}