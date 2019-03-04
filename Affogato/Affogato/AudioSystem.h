//
// Created by Mörkönenä on 24.2.2018
//

#ifndef CORE_AUDIO_SYSTEM_H
#define CORE_AUDIO_SYSTEM_H

namespace FMOD
{
	class System;
}

namespace Core
{
	class AudioSystem
	{
	private:
		friend class Audio;
		static FMOD::System* System;

	public:
		static void Initialize(int channels = 32);
		static void Tick();
	};
}

#endif // !CORE_AUDIO_SYSTEM_H