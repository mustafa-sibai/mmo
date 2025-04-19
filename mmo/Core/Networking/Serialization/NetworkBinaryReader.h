#pragma once
#include "../../API.h"
#include <vector>
#include <string>
#include <stdexcept>
#include <cstring>
#include <winsock2.h>

class CORE_API NetworkBinaryReader
{
private:
	const std::vector<char>& m_buffer;
	size_t m_position;

public:
	explicit NetworkBinaryReader(const std::vector<char>& buffer);
	~NetworkBinaryReader();

	// Reads an int, assuming network byte order in the buffer.
	int ReadInt();

	// Reads a bool (stored as one byte, 0 = false, nonzero = true).
	bool ReadBool();

	// Reads a float (the sender and receiver must agree on the representation).
	float ReadFloat();

	// Reads a double.
	double ReadDouble();

	// Reads a string:
	// First an int (length in network byte order), then that many bytes.
	std::string ReadString();
};