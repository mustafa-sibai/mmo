#include "Audio.h"
#include <iostream>
#include "Core/IO/WAVFileReader.h"

Audio::Audio() :
	xAudio2(nullptr),
	masterVoice(nullptr),
	sourceVoice(nullptr)
{
}

Audio::~Audio()
{
}

void Audio::Initialize()
{
	if (FAILED(CoInitializeEx(nullptr, COINIT_MULTITHREADED)))
	{
		std::cerr << "CoInitializeEx failed" << std::endl;
		return;
	}

	if (FAILED(XAudio2Create(&xAudio2, 0, XAUDIO2_USE_DEFAULT_PROCESSOR)))
	{
		std::cerr << "XAudio2Create failed" << std::endl;
		CoUninitialize();
		return;
	}

	if (FAILED(xAudio2->CreateMasteringVoice(&masterVoice)))
	{
		std::cerr << "CreateMasteringVoice failed" << std::endl;
		xAudio2->Release();
		CoUninitialize();
		return;
	}
}

//TEST
void Audio::Play()
{
	// Load WAV data
	WAVData wav = WAVFileReader::Read("music.wav");

	// Set up WAVEFORMATEX
	WAVEFORMATEX format = {};
	format.wFormatTag = WAVE_FORMAT_PCM;
	format.nChannels = wav.header.numChannels;
	format.nSamplesPerSec = wav.header.sampleRate;
	format.wBitsPerSample = wav.header.bitsPerSample;
	format.nBlockAlign = wav.header.blockAlign;
	format.nAvgBytesPerSec = wav.header.byteRate;

	if (FAILED(xAudio2->CreateSourceVoice(&sourceVoice, &format)))
	{
		std::cerr << "Source voice not created." << std::endl;
		return;
	}

	// Submit buffer
	XAUDIO2_BUFFER buffer = {};
	buffer.AudioBytes = wav.header.dataSize;
	buffer.pAudioData = wav.data.data();
	buffer.Flags = XAUDIO2_END_OF_STREAM;

	if (FAILED(sourceVoice->SubmitSourceBuffer(&buffer)))
	{
		std::cerr << "Failed to submit audio buffer." << std::endl;
		return;
	}

	// Start playback
	if (FAILED(sourceVoice->Start(0)))
	{
		std::cerr << "Failed to start playback." << std::endl;
	}

	// Wait for playback to finish
	XAUDIO2_VOICE_STATE state;
	do
	{
		sourceVoice->GetState(&state);
		Sleep(100);
	} while (state.BuffersQueued > 0);
}