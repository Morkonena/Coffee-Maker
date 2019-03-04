#include <Asset.h>
#include "Audio.h"
#include "AudioSystem.h"

#include <fmod.hpp>
#include <Log.h>

using namespace Core;

Audio::Audio(String filename)
{
	Asset asset(filename);

	FMOD_CREATESOUNDEXINFO info = {0};
	info.length = asset.GetLength();
	info.cbsize = sizeof(FMOD_CREATESOUNDEXINFO);

	if (AudioSystem::System->createSound(static_cast<const char*>(asset.GetData()), FMOD_OPENMEMORY, &info, &Sound) != FMOD_OK)
	{
		PERROR("ERROR_CREATE_AUDIO: ", filename.c_str());
		throw;
	}

	if (Sound->getDefaults(&Frequency, &Priority) != FMOD_OK)
	{
		PERROR("ERROR_AUDIO_PROPERTIES: (Couldn't get audio properties)");
		Sound->release();
		throw;
	}

	uint length;

	if (Sound->getLength(&length, FMOD_TIMEUNIT_MS) != FMOD_OK)
	{
		PERROR("ERROR_AUDIO_LENGTH: (Couldn't get audio length)");
		Sound->release();
		throw;
	}

	Length = length;
}

void Audio::Play()
{
	AudioSystem::System->playSound(Sound, 0, false, &Channel);
}

void Audio::Pause()
{
	Channel->setPaused(true);
}

void Audio::Resume()
{
	Channel->setPaused(false);
}

void Audio::Stop()
{
	Channel->stop();
	Channel = nullptr;
}

void Audio::SetPosition(int milliseconds) const
{
	if (!Channel)
	{
		PERROR("ERROR_AUDIO_POSITION: (Audio must be in play/pause mode when setting position)");
		throw;
	}

	if (Channel->setPosition((uint)milliseconds, FMOD_TIMEUNIT_MS) != FMOD_OK)
	{
		PERROR("ERROR_AUDIO_POSITION: (Couldn't set audio position)");
		throw;
	}
}

int Audio::GetPosition() const
{
	if (!Channel)
	{
		PERROR("ERROR_AUDIO_POSITION: (Audio must be in play/pause mode when getting position)");
		throw;
	}

	uint position;

	if (Channel->getPosition(&position, FMOD_TIMEUNIT_MS) != FMOD_OK)
	{
		PERROR("ERROR_AUDIO_POSITION: (Couldn't get audio position)");
		throw;
	}

	return position;
}

void Audio::SetLooping(bool loop)
{
	Sound->setMode(loop ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF);
}

void Audio::SetSpeed(float speed)
{
	if (!Channel)
	{
		PERROR("ERROR_AUDIO_SPEED: (Audio must be in play/pause mode when setting speed)");
		throw;
	}

	Channel->setFrequency(Frequency * speed);
}

void Audio::SetPitch(float pitch)
{
	if (!Channel)
	{
		PERROR("ERROR_AUDIO_PITCH: (Audio must be in play/pause mode when setting pitch)");
		throw;
	}

	Channel->setPitch(pitch);
}

float Audio::GetSpeed() const
{
	if (!Channel)
	{
		PERROR("ERROR_AUDIO_SPEED: (Audio must be in play/pause mode when getting speed)");
		throw;
	}
	
	float frequency;

	if (Channel->getFrequency(&frequency) != FMOD_OK)
	{
		PERROR("ERROR_AUDIO_SPEED: (Couldn't get audio frequency)");
		throw;
	}

	return frequency / Frequency;
}

float Audio::GetPitch() const
{
	if (!Channel)
	{
		PERROR("ERROR_AUDIO_PITCH: (Audio must be in play/pause mode when getting pitch)");
		throw;
	}

	float pitch;

	if (Channel->getFrequency(&pitch) != FMOD_OK)
	{
		PERROR("ERROR_AUDIO_PITCH: (Couldn't get audio pitch)");
		throw;
	}

	return pitch;
}

int Audio::GetLength() const
{
	return Length;
}
