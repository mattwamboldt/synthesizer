#ifndef AUDIO_SYNTH_MIDICHANNEL_H
#define AUDIO_SYNTH_MIDICHANNEL_H

#include "midinote.h"

namespace Audio
{
	// Software representation of a midi channel
	// Current implementation is extremely inefficient, as the channel has a copy
	// of every note, instead of a vector of the 16 notes it's allowed to play at
	// once. I misunderstood at the time of writing how channels and mixing work
	class MidiChannel
	{
	public:
		void Init();

		void SetVolume(float value);
		float GetVolume() { return volume; }

		void NoteOff(Uint8 note, Uint8 velocity = 64);
		void NoteOn(Uint8 note, Uint8 velocity = 64);
		void Aftertouch(Uint8 note, Uint8 pressure);

		void AllNotesOff();

		void Write(PCM16* data, int count);

	private:
		MidiNote notes[NUM_MIDI_NOTES];
		float volume;
		BreakpointFile attack;
		BreakpointFile decay;
		BreakpointFile release;
	};
}

#endif
