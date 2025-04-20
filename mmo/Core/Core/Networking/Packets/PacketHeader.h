#pragma once  
#include <cstdint>  
#include <cstring>
#include "Core/API.h"

class CORE_API PacketHeader
{
public:
	enum class PacketType
	{
		Unknown = -1,
		Position = 0,
	};

	PacketType type;
	uint32_t length;

	PacketHeader();
	PacketHeader(PacketType type, uint32_t length);
	~PacketHeader();
};