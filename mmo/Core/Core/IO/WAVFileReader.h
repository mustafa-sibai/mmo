#pragma once
#include "Core/API.h"
#include <cstdint>
#include <fstream>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <cstring>

//https://docs.fileformat.com/audio/wav
#pragma pack(push, 1)
struct WAVHeader
{
	char     riff[4];        // "RIFF"
	uint32_t fileSize;       // Size of the entire file minus 8 bytes
	char     wave[4];        // "WAVE"
	char     fmt[4];         // "fmt "
	uint32_t subchunk1Size;  // Size of the fmt chunk (16 for PCM)
	uint16_t audioFormat;    // Audio format (1 = PCM)
	uint16_t numChannels;    // Number of channels
	uint32_t sampleRate;     // Sampling frequency
	uint32_t byteRate;       // == SampleRate * NumChannels * BitsPerSample/8
	uint16_t blockAlign;     // == NumChannels * BitsPerSample/8
	uint16_t bitsPerSample;  // Bits per sample (8, 16, etc.)
	char     data[4];        // "data"
	uint32_t dataSize;       // Size of the data section
};
#pragma pack(pop)

struct WAVData
{
	WAVHeader header;
	std::vector<uint8_t> data;  // PCM data bytes
};

class CORE_API WAVFileReader
{
private:
	WAVFileReader() = default;
	WAVFileReader(const WAVFileReader&) = delete;
	WAVFileReader(WAVFileReader&&) = delete;
	WAVFileReader& operator=(const WAVFileReader&) = delete;
	~WAVFileReader() = default;

public:
	static WAVData Read(const std::string& filepath);
};