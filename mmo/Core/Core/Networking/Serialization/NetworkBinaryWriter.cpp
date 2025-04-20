#include "NetworkBinaryWriter.h"
#include <cstdint>
#include <winsock2.h>

NetworkBinaryWriter::NetworkBinaryWriter() :
	m_buffer(NetworkBuffer()), position(0)
{
}

NetworkBinaryWriter::~NetworkBinaryWriter()
{
}

// Copy constructor
NetworkBinaryWriter::NetworkBinaryWriter(const NetworkBinaryWriter& other)
	: m_buffer(other.m_buffer), position(other.position)
{
}

// Move constructor
NetworkBinaryWriter::NetworkBinaryWriter(NetworkBinaryWriter&& other) noexcept
	: m_buffer(std::move(other.m_buffer)), position(other.position)
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
void NetworkBinaryWriter::WriteInt16(int16_t value, OperationMode operationMode)
{
	// Convert to network byte order for consistent cross-platform use.
	int16_t netValue = htons(value);
	Write(&netValue, sizeof(netValue), operationMode);
}

void NetworkBinaryWriter::WriteUInt16(uint16_t value, OperationMode operationMode)
{
	// Convert to network byte order for consistent cross-platform use.
	uint16_t netValue = htons(value);
	Write(&netValue, sizeof(netValue), operationMode);
}

// Write an integer (written in network byte order)
void NetworkBinaryWriter::WriteInt32(int32_t value, OperationMode operationMode)
{
	// Convert to network byte order for consistent cross-platform use.
	int32_t netValue = htonl(value);
	Write(&netValue, sizeof(netValue), operationMode);
}

void NetworkBinaryWriter::WriteUInt32(uint32_t value, OperationMode operationMode)
{
	// Convert to network byte order for consistent cross-platform use.
	uint32_t netValue = htonl(value);
	Write(&netValue, sizeof(netValue), operationMode);
}

void NetworkBinaryWriter::WriteBool(bool value, OperationMode operationMode)
{
	uint8_t b = value ? 1 : 0;
	Write(&b, sizeof(b), operationMode);
}

void NetworkBinaryWriter::WriteFloat(float value, OperationMode operationMode)
{
	Write(&value, sizeof(value), operationMode);
}

void NetworkBinaryWriter::WriteDouble(double value, OperationMode operationMode)
{
	Write(&value, sizeof(value), operationMode);
}

// First writes the length (as int), then the string bytes.
void NetworkBinaryWriter::WriteString(const std::string& value, OperationMode operationMode)
{
	WriteInt32(static_cast<int32_t>(value.size()), operationMode);
	if (!value.empty()) {
		Write(value.data(), value.size(), operationMode);
	}
}

void NetworkBinaryWriter::WriteVector2f(const Vector2f& value, OperationMode operationMode)
{
	WriteFloat(value.x, operationMode);
	WriteFloat(value.y, operationMode);
}

void NetworkBinaryWriter::WriteVector2i(const Vector2i& value, OperationMode operationMode)
{
	WriteInt32(value.x, operationMode);
	WriteInt32(value.y, operationMode);
}

void NetworkBinaryWriter::WriteVector3f(const Vector3f& value, OperationMode operationMode)
{
	WriteFloat(value.x, operationMode);
	WriteFloat(value.y, operationMode);
	WriteFloat(value.z, operationMode);
}

void NetworkBinaryWriter::WriteVector3i(const Vector3i& value, OperationMode operationMode)
{
	WriteInt32(value.x, operationMode);
	WriteInt32(value.y, operationMode);
	WriteInt32(value.z, operationMode);
}

void NetworkBinaryWriter::WriteVector4f(const Vector4f& value, OperationMode operationMode)
{
	WriteFloat(value.x, operationMode);
	WriteFloat(value.y, operationMode);
	WriteFloat(value.z, operationMode);
	WriteFloat(value.w, operationMode);
}

void NetworkBinaryWriter::WriteVector4i(const Vector4i& value, OperationMode operationMode)
{
	WriteInt32(value.x, operationMode);
	WriteInt32(value.y, operationMode);
	WriteInt32(value.z, operationMode);
	WriteInt32(value.w, operationMode);
}

void NetworkBinaryWriter::Clear()
{
	position = 0;
	m_buffer.clear();
}

void NetworkBinaryWriter::Write(const void* data, size_t size, OperationMode operationMode)
{
	if (operationMode == OperationMode::Append)
	{
		Append(data, size);
	}
	else if (operationMode == OperationMode::Overwrite)
	{
		Overwrite(data, size);
	}
}

void NetworkBinaryWriter::Append(const void* data, size_t size)
{
	const uint8_t* ptr = static_cast<const uint8_t*>(data);
	m_buffer.insert(m_buffer.end(), ptr, ptr + size);
}

void NetworkBinaryWriter::Overwrite(const void* data, size_t size)
{
	const uint8_t* ptr = static_cast<const uint8_t*>(data);
	const uint8_t* bufferAddress = m_buffer.data();

	std::copy(ptr, ptr + size, m_buffer.begin() + position);
}