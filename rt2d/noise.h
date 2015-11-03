/**
 * @file noise.h
 * 
 * @brief The Noise header file.
 * 
 * This file is part of RT2D, a 2D OpenGL framework.
 * 
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *   - Initial commit
 * - Copyright [year] [your name] <you@yourhost.com>
 *   - [description]
 */

#ifndef NOISE_H
#define NOISE_H

class Noise
{
	public:
		Noise();
		virtual ~Noise();
		
		static std::vector<float> whiteNoise(int width, int height);
		static std::vector<float> smoothNoise(std::vector<float>& baseNoise, int octave, int width, int height);
		static std::vector<float> perlinNoise(std::vector<float>& baseNoise, int octaveCount, int width, int height);
		
	private:
		static float interpolate(float x0, float x1, float alpha);
};

#endif /* NOISE_H */ 
