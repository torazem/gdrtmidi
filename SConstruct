#!/usr/bin/env python
import os
import sys

env = SConscript("godot-cpp/SConstruct")

# For reference:
# - CCFLAGS are compilation flags shared between C and C++
# - CFLAGS are for C-specific compilation flags
# - CXXFLAGS are for C++-specific compilation flags
# - CPPFLAGS are for pre-processor flags
# - CPPDEFINES are for pre-processor defines
# - LINKFLAGS are for linking flags

# tweak this if you want to use different folders, or more folders, to store your source code in.
env.Append(CPPPATH=['./src/', './rtmidi/'])
sources = ["src/register_types.cpp", "src/gdrtmidiout.cpp", "rtmidi/RtMidi.cpp"]
# Glob('./*.cpp', './rtmidi/*.cpp')

if env["platform"] == "macos":
    # Not yet tested
    library = env.SharedLibrary(
        "demo/bin/libgdrtmidi.{}.{}.framework/libgdrtmidi.{}.{}".format(
            env["platform"], env["target"], env["platform"], env["target"]
        ),
        source=sources,
    )
else:
    env.Append(CCFLAGS=["/EHsc"])
    env.Append(CPPDEFINES=['__WINDOWS_MM__'])
    env.Append(LIBS=['winmm'])
    library = env.SharedLibrary(
        "demo/bin/libgdrtmidi{}{}".format(env["suffix"], env["SHLIBSUFFIX"]),
        source=sources,
    )

Default(library)
