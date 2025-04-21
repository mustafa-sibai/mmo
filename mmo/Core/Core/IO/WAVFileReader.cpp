#include "WAVFileReader.h"

WAVData WAVFileReader::Read(const std::string& filepath)
{
	std::ifstream in(filepath, std::ios::binary);

	if (!in)
		throw std::runtime_error("Cannot open file: " + filepath);

	WAVHeader header;
	in.read(reinterpret_cast<char*>(&header), sizeof(header));

	if (!in)
		throw std::runtime_error("Failed to read WAV header");

	// Basic validation
	if (std::strncmp(header.riff, "RIFF", 4) != 0 ||
		std::strncmp(header.wave, "WAVE", 4) != 0 ||
		std::strncmp(header.fmt, "fmt ", 4) != 0)
	{
		throw std::runtime_error("Invalid or unsupported WAV file format");
	}

	// Read PCM data
	WAVData wav;
	wav.header = header;
	wav.data.resize(header.dataSize);
	in.read(reinterpret_cast<char*>(wav.data.data()), wav.header.dataSize);

	if (!in)
		throw std::runtime_error("Failed to read WAV data chunk");

	return wav;
}