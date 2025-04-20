#pragma once
#include "Core/API.h"
#include "Core/Math/Vector2.h"
#include "Core/Networking/Packets/BasePacket.h"

class CORE_API PositionPacket : public BasePacket
{
private:
	Vector2f position;

public:
	PositionPacket();
	PositionPacket(const Vector2f& position);
	~PositionPacket();

	const NetworkBuffer& Serialize();
	PositionPacket* Deserialize(const uint8_t* buffer);

	inline const Vector2f& GetPosition() const { return position; }
};