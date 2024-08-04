# Introduction
GDRtMidi is a Godot 4.3+ wrapper for the popular C++ midi library RtMidi. 

This is a fork of [kumikohime's RtMidi wrapper](https://github.com/kumikohime/gdrtmidi) that has been upgraded to work with Godot 4.3+.

## Disclaimer
1. I make no promises to maintain this fork.
2. There are no pre-built binaries.
3. This has only been tested on Windows with the debug build.
4. Only the Midi Out interface is supported.

# Building

1. Clone the repo.
2. Initialise the submodules by running `git submodule update --init`.
3. Compile the project with `scons platform=windows/linux/osx`. It will take a while building `godot-cpp`.

# Usage

Check out the demo project under `demo/` for example usage.
Also refer to the RtMidiOut Class Interface

https://www.music.mcgill.ca/~gary/rtmidi/classRtMidiOut.html
