#pragma once
#include "Core/API.h"
#include <vector>
#include <string>

class CORE_API NetworkBinaryWriter
{
private:
	std::vector<char> m_buffer;

public:
	NetworkBinaryWriter();
	~NetworkBinaryWriter();

	// Write an integer (written in network byte order)
	void Write(int value);

	// Write a bool (as one byte: 1 for true, 0 for false)
	void Write(bool value);
	void Write(float value);
	void Write(double value);

	// Write a std::string.
	// First writes the length (as int), then the string bytes.
	void Write(const std::string& value);

	inline void Clear() { m_buffer.clear(); }

	inline const std::vector<char>& GetBuffer() const { return m_buffer; }

private:
	// Utility: Append raw bytes to the buffer
	void Append(const void* data, size_t size);
};