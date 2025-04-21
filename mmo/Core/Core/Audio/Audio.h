#pragma once
#include "Core/API.h"
#include <xaudio2.h>

class CORE_API Audio
{
private:
	IXAudio2* xAudio2;
	IXAudio2MasteringVoice* masterVoice;
	IXAudio2SourceVoice* sourceVoice;

public:
	Audio();
	~Audio();

	void Initialize();
	void Play();
};