#include "audio.h"
#include <SDL/SDL.h>
#include "../debug.h"
#include "../perftimer.h"
#include <cstring>
#include <random>
#include "file/wave.h"
#include "file/midi.h"
#include "effects/delay.h"
#include "synth/midinote.h"
#include "file/breakpoint.h"
#include "synth/oscillator.h"
#include "synth/signalgenerator.h"
#include "synth/oscillatorbank.h"
#include "synth/wavetable.h"
#include "synth/wavebank.h"

#include <time.h>

namespace Audio
{
	SDL_AudioSpec audioSpec;
	MidiController midiController;

	WaveHeader outputTestHeader;
	WaveFile outputTest;

	void FillAudio(void *userData, Uint8 *audioData, int length)
	{
		// Clear our audio buffer to silence.
		memset(audioData, audioSpec.silence, length);
        midiController.Write((PCM16*)audioData, length / 2);

		if (!outputTest.paused)
		{
			outputTest.Append((PCM16*)audioData, length / 2);
		}
	}

	bool IsRecording()
	{
		return !outputTest.paused;
	}

	void StartRecord()
	{
		outputTest.paused = false;
	}

	void StopRecord()
	{
		outputTest.paused = true;
		outputTest.Write("test.wav");
		outputTest.Clear();
	}

	bool Init()
	{
		//Set our initial properties
		audioSpec.freq = 44100;
		audioSpec.format = AUDIO_S16;
		audioSpec.channels = 2;
		audioSpec.samples = 4400;
		audioSpec.callback = &FillAudio;

		outputTestHeader.bitsPerSample = 16;
		outputTestHeader.blockAlign = 2;
		outputTestHeader.format = 1;
		outputTestHeader.nAvgBytesPerSecond = audioSpec.freq * 2;
		outputTestHeader.numChannels = 2;
		outputTestHeader.numSamplesPerSecond = audioSpec.freq;
		outputTest.Init(outputTestHeader);
		outputTest.paused = true;

		SDL_OpenAudio(&audioSpec, 0);

		//If the audio device gives the expected format then unpause the device
		if (audioSpec.format != AUDIO_S16)
		{
			return false;
		}

		Oscillator::SetSamplingRate(audioSpec.freq);
		WaveTable::SetSamplingRate(audioSpec.freq);

		midiController.Init();

		SDL_PauseAudio(0);
		return true;
	}
}
