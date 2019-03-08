# README #

### Description ###

The Synthesizer is a learning project, where I'm attempting to build an audio system.
It currently supports basic WAV files, a subset of MIDI, and a few effects. It also
needs some dramatic architecture overhauls to extend well past this point. Much of the
lower level synthsis code is based on The Audio Programming Book, by Richard Boulanger
and Victor Lazzarini. The general structure is based on my experience with existing and
proprietary audio systems.

### Instructions ###

The code can be built using Visual Studio 2013 or later using the solution found in the 
source folder.

There's currently no UI (something that'll get fixed at some point, even if it's just a
console), so don't let that fool you. If you start pressing and holding on keys you'll
hear notes being played. These are generated by the underlying midi controller.

There are a few clicks and pops at the moment if you play too many notes but otherwise it works.
