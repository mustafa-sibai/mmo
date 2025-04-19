#include "NetworkBinaryWriter.h"
#include <cstdint>
#include <cstring>
#include <winsock2.h>

NetworkBinaryWriter::NetworkBinaryWriter()
{
}

NetworkBinaryWriter::~NetworkBinaryWriter()
{
}

// Write an integer (written in network byte order)
void NetworkBinaryWriter::Write(int value)
{
	// Convert to network byte order for consistent cross-platform use.
	int netValue = htonl(value);
	Append(&netValue, sizeof(netValue));
}

void NetworkBinaryWriter::Write(bool value)
{
	uint8_t b = value ? 1 : 0;
	Append(&b, sizeof(b));
}

void NetworkBinaryWriter::Write(float value)
{
	Append(&value, sizeof(value));
}

void NetworkBinaryWriter::Write(double value)
{
	Append(&value, sizeof(value));
}

// First writes the length (as int), then the string bytes.
void NetworkBinaryWriter::Write(const std::string& value)
{
	Write(static_cast<int>(value.size()));
	if (!value.empty()) {
		Append(value.data(), value.size());
	}
}

void NetworkBinaryWriter::Append(const void* data, size_t size)
{
	const char* ptr = static_cast<const char*>(data);
	m_buffer.insert(m_buffer.end(), ptr, ptr + size);
}