#ifndef WAV_H
#define WAV_H

#include <stdio.h>
#include <string>
#include <AL/al.h>
#include <AL/alc.h>

bool loadWavFile(const std::string filename, ALuint* buffer);

#endif
