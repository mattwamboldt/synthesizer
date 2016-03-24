#ifndef AUDIO_EFFECTS_TREMOLO_H
#define AUDIO_EFFECTS_TREMOLO_H

#include "iaudioeffect.h"
#include "..\synth\oscillator.h"

namespace Audio
{
	// Tremolo uses a secondary signal to control the amplitude of the source
	// Not to be confused with vibrato, which does the same thing for frequency
	class Tremolo : public IAudioEffect
	{
	public:
		Tremolo(float percent = 0.3, float frequency = 4.0, WaveType wave = SINE_WAVE);
		virtual void Write(PCM16* data, int count);

		double GetFrequency() { return osc.GetFrequency(); }
		void SetFrequency(double val) { return osc.SetFrequency(val); }
	private:
		Oscillator osc;
		double sourceFactor;
		double depthFactor;
	};
}

#endif