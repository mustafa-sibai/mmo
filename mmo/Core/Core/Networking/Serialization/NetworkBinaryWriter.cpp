#include "NetworkBinaryWriter.h"
#include <cstdint>
#include <winsock2.h>

NetworkBinaryWriter::NetworkBinaryWriter()
{
}

NetworkBinaryWriter::~NetworkBinaryWriter()
{
}

// Copy constructor
NetworkBinaryWriter::NetworkBinaryWriter(const NetworkBinaryWriter& other)
	: m_buffer(other.m_buffer)
{
}

// Move constructor
NetworkBinaryWriter::NetworkBinaryWriter(NetworkBinaryWriter&& other) noexcept
	: m_buffer(std::move(other.m_buffer))
{
}

// Copy assignment operator
NetworkBinaryWriter& NetworkBinaryWriter::operator=(const NetworkBinaryWriter& other) {
	if (this != &other)
	{
		m_buffer = other.m_buffer;
	}
	return *this;
}

// Move assignment operator
NetworkBinaryWriter& NetworkBinaryWriter::operator=(NetworkBinaryWriter&& other) noexcept {
	if (this != &other)
	{
		m_buffer = std::move(other.m_buffer);
	}
	return *this;
}

// Write an integer (written in network byte order)
void NetworkBinaryWriter::WriteInt16(int16_t value)
{
	// Convert to network byte order for consistent cross-platform use.
	int16_t netValue = htons(value);
	Append(&netValue, sizeof(netValue));
}

void NetworkBinaryWriter::WriteUInt16(uint16_t value)
{
	// Convert to network byte order for consistent cross-platform use.
	uint16_t netValue = htons(value);
	Append(&netValue, sizeof(netValue));
}

// Write an integer (written in network byte order)
void NetworkBinaryWriter::WriteInt32(int32_t value)
{
	// Convert to network byte order for consistent cross-platform use.
	int32_t netValue = htonl(value);
	Append(&netValue, sizeof(netValue));
}

void NetworkBinaryWriter::WriteUInt32(uint32_t value)
{
	// Convert to network byte order for consistent cross-platform use.
	uint32_t netValue = htonl(value);
	Append(&netValue, sizeof(netValue));
}

void NetworkBinaryWriter::WriteBool(bool value)
{
	uint8_t b = value ? 1 : 0;
	Append(&b, sizeof(b));
}

void NetworkBinaryWriter::WriteFloat(float value)
{
	Append(&value, sizeof(value));
}

void NetworkBinaryWriter::WriteDouble(double value)
{
	Append(&value, sizeof(value));
}

// First writes the length (as int), then the string bytes.
void NetworkBinaryWriter::WriteString(const std::string& value)
{
	WriteInt32(static_cast<int32_t>(value.size()));
	if (!value.empty()) {
		Append(value.data(), value.size());
	}
}

void NetworkBinaryWriter::Append(const void* data, size_t size)
{
	const uint8_t* ptr = static_cast<const uint8_t*>(data);
	m_buffer.insert(m_buffer.end(), ptr, ptr + size);
}