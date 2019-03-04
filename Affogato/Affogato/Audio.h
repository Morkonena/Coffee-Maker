//
// Created by Mörkönenä on 24.2.2019
//

#ifndef CORE_AUDIO_H
#define CORE_AUDIO_H

#include <Standard.h>

namespace FMOD
{
	class Sound;
	class Channel;
}

namespace Core
{
	class Audio
	{
	private:
		FMOD::Sound* Sound;
		FMOD::Channel* Channel;

		float Frequency;
		int Length;
		int Priority;

	public:
		Audio(String filename);

		void Play();
		void Pause();
		void Resume();
		void Stop();

		void SetPosition(int milliseconds) const;
		int  GetPosition() const;

		void SetLooping(bool loop);

		void SetSpeed(float speed);
		void SetPitch(float pitch);

		float GetSpeed() const;
		float GetPitch() const;

		int GetLength() const;
	};
}

#endif // !CORE_AUDIO_H