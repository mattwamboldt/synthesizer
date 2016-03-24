#ifndef AUDIO_FILE_MIDI
#define AUDIO_FILE_MIDI

#include "../audio.h"
#include <vector>
#include <string>

namespace Audio
{
	class MidiController;
	// A Midi track is a collection of timed midi events or commands that modify
	// the midi system to generate music. It also defines the playback speed
	// TODO: The whole midi system is a WIP and would be better arranged using
	// the command pattern for it's events. I'm trying to directly process the
	// events using a loop.
	class MidiTrack
	{
	public:
		void Advance(MidiController* controller);
		MidiEvent Current(){ return events[currentEvent]; }
		
		bool Load(SDL_RWops* file);
	private:
		Uint32 ReadLength(SDL_RWops* file);
		Uint8 NextByte(SDL_RWops* file);
		std::string MidiTrack::ReadString(SDL_RWops* file, Uint32 length);
		bool IsCommandByte(){ return currentByte & 128;} //The first bit is 1 on a command byte

		Uint32 numBytes;
		Uint32 numBytesRemaining;
		Uint8 currentByte;
		Uint16 sequenceNumber;

		Uint32 pulseCounter;

		int currentEvent;
		std::vector<MidiEvent> events;
		std::string name;
		std::string copyright;
		std::string text;
		std::string instrument;
	};

	// A Midi file is a collection of tracks which comtain commands for
	// the underlying midi controller
	class MidiFile
	{
	public:
		bool Load(const char* path);
		void Advance(MidiController* controller);
		Uint16 pulsesPerBeat;

	private:
		std::vector<MidiTrack> tracks;
		Uint16 format; //Format 0 is a one track file, 1 is multitrack simul and 2 is multisong
		Uint16 numTracks;
	};
}

#endif
