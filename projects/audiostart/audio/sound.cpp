#include <AL/al.h>
#include <string>
#include <iostream>
#include "sound.h"
#include "wav.h"

Sound::Sound()
{
	this->init();
}

Sound::Sound(std::string filename)
{
	this->init();
	this->load(filename);
}

Sound::~Sound()
{
    if (_source) {
        alDeleteSources(1, &_source);
    }
    if (_buffer) {
        alDeleteBuffers(1, &_buffer);
    }
}

void Sound::init()
{
	_buffer = 0;
    _source = 0;

    alGenSources((ALuint) 1, &_source);

    this->pitch(1.0);
    this->gain(1.0);
    this->position(0,0,0);
    this->velocity(0,0,0);
    this->loop(false);
}

void Sound::pitch(float p)
{
    alSourcef(_source, AL_PITCH, ALfloat(p));
}

void Sound::gain(float g)
{
    alSourcef(_source, AL_GAIN, ALfloat(g));
}

void Sound::position(float x, float y, float z)
{
    alSource3f(_source, AL_POSITION, ALfloat(z), ALfloat(y), ALfloat(z));
}

void Sound::velocity(float x, float y, float z)
{
    alSource3f(_source, AL_VELOCITY, ALfloat(z), ALfloat(y), ALfloat(z));
}

void Sound::loop(bool l)
{
    ALint toLoop = AL_FALSE;
    if (l) {
        toLoop = AL_TRUE;
    }
    alSourcef(_source, AL_LOOPING, toLoop);
}

bool Sound::load(std::string filename)
{
    std::cout << "Loading WAV: " << filename << std::endl;
    bool isLoaded = loadWavFile(filename, &_buffer);

    if (isLoaded) {
        alSourcei(_source, AL_BUFFER, _buffer);
    } else {
        std::cerr << "Unable to load: " << filename << std::endl;
    }
    return isLoaded;
}

Sound::State Sound::state()
{
    ALint source_state;
    State state = STATE_STOPPED;
    alGetSourcei(_source, AL_SOURCE_STATE, &source_state);
    switch (source_state) {
        default:
            break;
        case AL_PLAYING:
            state = STATE_PLAYING;
            break;
        case AL_PAUSED:
            state = STATE_PAUSED;
            break;
        case AL_STOPPED:
            state = STATE_STOPPED;
            break;
    }
    return state;
}

void Sound::play()
{
    alSourcePlay(_source);
}

void Sound::pause() {
    alSourcePause(_source);
}

void Sound::stop()
{
    alSourceStop(_source);
}

void Sound::rewind()
{
    alSourceRewind(_source);
}
