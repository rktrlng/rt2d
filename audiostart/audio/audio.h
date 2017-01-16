#ifndef AUDIO_H_
#define AUDIO_H_

#include <AL/al.h>
#include <AL/alc.h>

class Audio {
    public:
        Audio();
        virtual ~Audio();
        static void init();

		static void volume(float vol) { alListenerf(AL_GAIN, vol); }

    protected:
        static ALCdevice *device;
        static ALCcontext *context;
};

#endif /* AUDIO_H_ */
