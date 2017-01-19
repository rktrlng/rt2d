#ifndef SOUND_H_
#define SOUND_H_

#include <string>

class Sound
{
public:
    Sound();
	Sound(std::string filename);
	virtual ~Sound();

    enum State {STATE_PLAYING, STATE_STOPPED, STATE_PAUSED};

    bool load(std::string filename);
    void play();
    void pause();
    void stop();
    void rewind();
    State state();

    void pitch(float p);
    void gain(float g);
    void loop(bool l);
    void position(float x, float y, float z);
    void velocity(float x, float y, float z);

protected:
	void init();

    ALuint _buffer;
	ALuint _source;
};

#endif /* SOUND_H_ */
