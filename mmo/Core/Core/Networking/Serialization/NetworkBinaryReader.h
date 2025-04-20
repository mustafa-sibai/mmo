﻿#pragma once
#include "Core/API.h"
#include "Core/Networking/Serialization/NetworkBuffer.h"
#include "Core/Math/Math.h"
#include <vector>
#include <string>

class CORE_API NetworkBinaryReader
{
private:
	NetworkBuffer m_buffer;
	size_t m_position;

public:
	NetworkBinaryReader();
	explicit NetworkBinaryReader(const NetworkBuffer& buffer);
	~NetworkBinaryReader();

	// Copy constructor
	NetworkBinaryReader(const NetworkBinaryReader& other);

	// Move constructor
	NetworkBinaryReader(NetworkBinaryReader&& other) noexcept;

	// Copy assignment operator
	NetworkBinaryReader& operator=(const NetworkBinaryReader& other);

	// Move assignment operator
	NetworkBinaryReader& operator=(NetworkBinaryReader&& other) noexcept;

	int16_t ReadInt16();
	uint16_t ReadUInt16();

	int32_t ReadInt32();
	uint32_t ReadUInt32();

	bool ReadBool();
	float ReadFloat();
	double ReadDouble();
	std::string ReadString();

	Vector2f ReadVector2f();
	Vector2i ReadVector2i();

	Vector3f ReadVector3f();
	Vector3i ReadVector3i();

	Vector4f ReadVector4f();
	Vector4i ReadVector4i();

	// Seeks to a specific position in the buffer.
	void Seek(size_t position);

	inline void SetBuffer(const NetworkBuffer& buffer) { m_buffer = buffer; }
};