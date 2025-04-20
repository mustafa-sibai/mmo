#pragma once
#include "Core/API.h"
#include "Core/Networking/Serialization/NetworkBuffer.h"
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

	// Reads an int16, assuming network byte order in the buffer.
	int16_t ReadInt16();
	uint16_t ReadUInt16();

	// Reads an int32, assuming network byte order in the buffer.
	int32_t ReadInt32();
	uint32_t ReadUInt32();

	// Reads a bool (stored as one byte, 0 = false, nonzero = true).
	bool ReadBool();

	// Reads a float (the sender and receiver must agree on the representation).
	float ReadFloat();

	// Reads a double.
	double ReadDouble();

	// Reads a string:
	// First an int (length in network byte order), then that many bytes.
	std::string ReadString();

	// Seeks to a specific position in the buffer.
	void Seek(size_t position);

	inline void SetBuffer(const NetworkBuffer& buffer) { m_buffer = buffer; }
};