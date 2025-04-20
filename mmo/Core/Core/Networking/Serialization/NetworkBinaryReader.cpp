#include "NetworkBinaryReader.h"
#include <stdexcept>
#include <winsock2.h>

NetworkBinaryReader::NetworkBinaryReader()
	: m_buffer(NetworkBuffer()), m_position(0)
{
}

NetworkBinaryReader::NetworkBinaryReader(const NetworkBuffer& buffer)
	: m_buffer(buffer), m_position(0)
{
}

NetworkBinaryReader::~NetworkBinaryReader()
{
}

// Copy constructor
NetworkBinaryReader::NetworkBinaryReader(const NetworkBinaryReader& other)
	: m_buffer(other.m_buffer), m_position(other.m_position)
{
}

// Move constructor
NetworkBinaryReader::NetworkBinaryReader(NetworkBinaryReader&& other) noexcept
	: m_buffer(std::move(other.m_buffer)), m_position(other.m_position)
{
	other.m_position = 0;
}

// Copy assignment operator
NetworkBinaryReader& NetworkBinaryReader::operator=(const NetworkBinaryReader& other) {
	if (this != &other) {
		m_buffer = other.m_buffer;
		m_position = other.m_position;
	}
	return *this;
}

// Move assignment operator
NetworkBinaryReader& NetworkBinaryReader::operator=(NetworkBinaryReader&& other) noexcept {
	if (this != &other) {
		m_buffer = std::move(other.m_buffer);
		m_position = other.m_position;
		other.m_position = 0;
	}
	return *this;
}

int16_t NetworkBinaryReader::ReadInt16()
{
	if (m_position + sizeof(int16_t) > m_buffer.size())
		throw std::runtime_error("NetworkBinaryReader::ReadInt16 - Buffer overflow");

	int16_t netValue = 0;
	std::memcpy(&netValue, &m_buffer[m_position], sizeof(int16_t));
	m_position += sizeof(int16_t);
	return ntohs(netValue);
}

uint16_t NetworkBinaryReader::ReadUInt16()
{
	if (m_position + sizeof(uint16_t) > m_buffer.size())
		throw std::runtime_error("NetworkBinaryReader::ReadUInt16 - Buffer overflow");

	uint16_t netValue = 0;
	std::memcpy(&netValue, &m_buffer[m_position], sizeof(uint16_t));
	m_position += sizeof(uint16_t);
	return ntohs(netValue);
}

int32_t NetworkBinaryReader::ReadInt32()
{
	if (m_position + sizeof(int32_t) > m_buffer.size())
		throw std::runtime_error("NetworkBinaryReader::ReadInt32 - Buffer overflow");

	int32_t netValue = 0;
	std::memcpy(&netValue, &m_buffer[m_position], sizeof(int32_t));
	m_position += sizeof(int32_t);
	return ntohl(netValue);
}

uint32_t NetworkBinaryReader::ReadUInt32()
{
	if (m_position + sizeof(uint32_t) > m_buffer.size())
		throw std::runtime_error("NetworkBinaryReader::ReadUInt32 - Buffer overflow");

	uint32_t netValue = 0;
	std::memcpy(&netValue, &m_buffer[m_position], sizeof(uint32_t));
	m_position += sizeof(uint32_t);
	return ntohl(netValue);
}

bool NetworkBinaryReader::ReadBool()
{
	if (m_position + sizeof(uint8_t) > m_buffer.size())
		throw std::runtime_error("NetworkBinaryReader::ReadBool - Buffer overflow");

	uint8_t value = 0;
	std::memcpy(&value, &m_buffer[m_position], sizeof(uint8_t));
	m_position += sizeof(uint8_t);
	return (value != 0);
}

float NetworkBinaryReader::ReadFloat()
{
	if (m_position + sizeof(float) > m_buffer.size())
		throw std::runtime_error("NetworkBinaryReader::ReadFloat - Buffer overflow");

	float value = 0;
	std::memcpy(&value, &m_buffer[m_position], sizeof(float));
	m_position += sizeof(float);
	return value;
}

double NetworkBinaryReader::ReadDouble()
{
	if (m_position + sizeof(double) > m_buffer.size())
		throw std::runtime_error("NetworkBinaryReader::ReadDouble - Buffer overflow");

	double value = 0;
	std::memcpy(&value, &m_buffer[m_position], sizeof(double));
	m_position += sizeof(double);
	return value;
}

std::string NetworkBinaryReader::ReadString()
{
	int32_t length = ReadInt32();
	if (length < 0)
		throw std::runtime_error("NetworkBinaryReader::ReadString - Negative length");

	if (m_position + static_cast<size_t>(length) > m_buffer.size())
		throw std::runtime_error("NetworkBinaryReader::ReadString - Buffer overflow");

	std::string result(reinterpret_cast<const char*>(&m_buffer[m_position]), static_cast<size_t>(length));
	m_position += length;
	return result;
}

Vector2f NetworkBinaryReader::ReadVector2f()
{
	return Vector2f(ReadFloat(), ReadFloat());
}

Vector2i NetworkBinaryReader::ReadVector2i()
{
	return Vector2i(ReadInt32(), ReadInt32());
}

Vector3f NetworkBinaryReader::ReadVector3f()
{
	return Vector3f(ReadFloat(), ReadFloat(), ReadFloat());
}

Vector3i NetworkBinaryReader::ReadVector3i()
{
	return Vector3i(ReadInt32(), ReadInt32(), ReadInt32());
}

Vector4f NetworkBinaryReader::ReadVector4f()
{
	return Vector4f(ReadFloat(), ReadFloat(), ReadFloat(), ReadFloat());
}

Vector4i NetworkBinaryReader::ReadVector4i()
{
	return Vector4i(ReadInt32(), ReadInt32(), ReadInt32(), ReadInt32());
}

void NetworkBinaryReader::Seek(size_t position)
{
	if (position > m_buffer.size())
		throw std::runtime_error("NetworkBinaryReader::Seek - Position out of bounds");
	
	m_position = position;
}