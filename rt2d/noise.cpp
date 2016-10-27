/**
 * This file is part of RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *   - Initial commit
 *
 * Algorithm from: http://devmag.org.za/2009/04/25/perlin-noise/
 */

#include <iostream>
#include <vector>
#include <cstdlib>

#include "noise.h"

Noise::Noise()
{

}

Noise::~Noise()
{

}

std::vector<float> Noise::whiteNoise(int width, int height)
{
	std::vector<float> whiteNoise;

    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            float f = rand()%100;
            whiteNoise.push_back(f/100);
        }
    }

    return whiteNoise;
}

std::vector<float> Noise::smoothNoise(std::vector<float>& baseNoise, int octave, int width, int height)
{
	std::vector<float> smoothNoise;

	std::vector<std::vector<float> > newBaseNoise;
	int counter = 0;
	for (int i = 0; i < width; i++) {
		std::vector<float> xvec;
		for (int j = 0; j < height; j++) {
			xvec.push_back(baseNoise[counter]);
			counter++;
		}
		newBaseNoise.push_back(xvec);
		counter++;
	}

	int samplePeriod = 1 << octave; // calculates 2 ^ k
	float sampleFrequency = 1.0f / samplePeriod;

	counter = 0;
	for (int i = 0; i < width; i++) {
		//calculate the horizontal sampling indices
		int sample_i0 = (i / samplePeriod) * samplePeriod;
		int sample_i1 = (sample_i0 + samplePeriod) % width; //wrap around
		float horizontal_blend = (i - sample_i0) * sampleFrequency;

		for (int j = 0; j < height; j++) {
			//calculate the vertical sampling indices
			int sample_j0 = (j / samplePeriod) * samplePeriod;
			int sample_j1 = (sample_j0 + samplePeriod) % height; //wrap around
			float vertical_blend = (j - sample_j0) * sampleFrequency;

			//blend the top two corners
			float top = interpolate(newBaseNoise[sample_i0][sample_j0], newBaseNoise[sample_i1][sample_j0], horizontal_blend);

			//blend the bottom two corners
			float bottom = interpolate(newBaseNoise[sample_i0][sample_j1], newBaseNoise[sample_i1][sample_j1], horizontal_blend);

			//final blend
			smoothNoise.push_back(interpolate(top, bottom, vertical_blend));
			counter++;
		}
		counter++;
	}

	return smoothNoise;
}

std::vector<float> Noise::perlinNoise(std::vector<float>& baseNoise, int octaveCount, int width, int height)
{
	std::vector<std::vector<float> > smoothNoises;
	float persistance = 0.5f;

	//generate smooth noises for each octave
	for (int i = 0; i < octaveCount; i++) {
		smoothNoises.push_back(smoothNoise(baseNoise, i, width, height));
	}

	std::vector<float> perlinNoise;
	float amplitude = 1.0f;
	float totalAmplitude = 0.0f;

	//blend noise together
	int counter = 0;
	for (int octave = octaveCount - 1; octave >= 0; octave--) {
		amplitude *= persistance;
		totalAmplitude += amplitude;

		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {
				perlinNoise.push_back( smoothNoises[octave][counter] * amplitude );
				counter++;
			}
			counter++;
		}
	}

	//normalisation
	counter = 0;
	for (int i = 0; i < width; i++){
		for (int j = 0; j < height; j++){
			perlinNoise[counter] /= totalAmplitude;
			counter++;
		}
		counter++;
	}

	return perlinNoise;
}

float Noise::interpolate(float x0, float x1, float alpha)
{
	return x0 * (1 - alpha) + alpha * x1;
}
