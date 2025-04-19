#include "NetworkBinaryReader.h"

NetworkBinaryReader::NetworkBinaryReader(const std::vector<char>& buffer)
	: m_buffer(buffer), m_position(0)
{
}

NetworkBinaryReader::~NetworkBinaryReader()
{
}

int NetworkBinaryReader::ReadInt()
{
	if (m_position + sizeof(int) > m_buffer.size())
		throw std::runtime_error("NetworkBinaryReader::ReadInt - Buffer overflow");

	int netValue = 0;
	std::memcpy(&netValue, &m_buffer[m_position], sizeof(int));
	m_position += sizeof(int);
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
	int length = ReadInt();
	if (length < 0)
		throw std::runtime_error("NetworkBinaryReader::ReadString - Negative length");

	if (m_position + static_cast<size_t>(length) > m_buffer.size())
		throw std::runtime_error("NetworkBinaryReader::ReadString - Buffer overflow");

	std::string result(&m_buffer[m_position], length);
	m_position += length;
	return result;
}