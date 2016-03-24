#ifndef AUDIO_EFFECTS_DELAY
#define AUDIO_EFFECTS_DELAY

#include "../audio.h"
#include "iaudioeffect.h"

namespace Audio
{
	// A Delay is will play a signal over itself offset and reduced by some amount
	class Delay : public IAudioEffect
	{
	public:
		Delay(float time, float decay);
		~Delay();
		virtual void Write(PCM16* data, int count);

	private:
		PCM16* buffer;
		int size;
		int position;
		float decay;
	};
}

#endif
