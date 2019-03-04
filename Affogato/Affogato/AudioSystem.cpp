#include "AudioSystem.h"
#include <Log.h>

#include <fmod.hpp>

using namespace Core;

FMOD::System* AudioSystem::System;

void AudioSystem::Initialize(int channels)
{
	if (FMOD::System_Create(&System) != FMOD_OK)
	{
		PERROR("ERROR_CREATE_AUDIO_SYSTEM");
		throw;
	}

	void* Data = 0;

	if (System->init(channels, FMOD_INIT_NORMAL, Data) != FMOD_OK)
	{
		PERROR("ERROR_INITIALIZE_AUDIO_SYSTEM");
		throw;
	}

	SUCCESS("Audio: OK");
}

void AudioSystem::Tick()
{
	System->update();
}
