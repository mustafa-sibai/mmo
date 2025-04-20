#pragma once
#include "Core/API.h"
#include "Core/Networking/Serialization/NetworkBuffer.h"
#include <vector>
#include <string>

class CORE_API NetworkBinaryWriter
{
private:
	NetworkBuffer m_buffer;

public:
	NetworkBinaryWriter();
	~NetworkBinaryWriter();

	// Copy constructor
	NetworkBinaryWriter(const NetworkBinaryWriter& other);

	// Move constructor
	NetworkBinaryWriter(NetworkBinaryWriter&& other) noexcept;

	// Copy assignment operator
	NetworkBinaryWriter& operator=(const NetworkBinaryWriter& other);

	// Move assignment operator
	NetworkBinaryWriter& operator=(NetworkBinaryWriter&& other) noexcept;

	// Write an integer (written in network byte order)

	void WriteInt16(int16_t value);
	void WriteUInt16(uint16_t value);

	void WriteInt32(int32_t value);
	void WriteUInt32(uint32_t value);

	// Write a bool (as one byte: 1 for true, 0 for false)
	void WriteBool(bool value);
	void WriteFloat(float value);
	void WriteDouble(double value);

	// Write a std::string.
	// First writes the length (as int), then the string bytes.
	void WriteString(const std::string& value);

	inline void Clear() { m_buffer.clear(); }

	inline const NetworkBuffer& GetBuffer() const { return m_buffer; }

private:
	// Utility: Append raw bytes to the buffer
	void Append(const void* data, size_t size);
};