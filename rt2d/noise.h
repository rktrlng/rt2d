/**
 * @file noise.h
 *
 * @brief The Noise header file.
 *
 * This file is part of RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *   - Initial commit
 */

#ifndef NOISE_H
#define NOISE_H

/// @brief The Noise class generates noise (white, smooth, perlin).
class Noise
{
public:
	Noise(); ///< @brief Noise Constructor
	virtual ~Noise(); ///< @brief Noise Destructor

	/// @brief generate white noise
	/// @param width the width of the field
	/// @param height the height of the field
	/// @return std::vector<float> single-line grid of noise values
	static std::vector<float> whiteNoise(int width, int height);
	/// @brief generate smooth noise
	/// @param baseNoise a field of base noise that needs smoothing
	/// @param octave the octave of the noise
	/// @param width the width of the field
	/// @param height the height of the field
	/// @return std::vector<float> single-line grid of noise values
	static std::vector<float> smoothNoise(std::vector<float>& baseNoise, int octave, int width, int height);
	/// @brief generate smooth noise
	/// @param baseNoise a field of base noise that needs smoothing
	/// @param octaveCount how many fields with different octaves to blend
	/// @param width the width of the field
	/// @param height the height of the field
	/// @return std::vector<float> single-line grid of noise values
	static std::vector<float> perlinNoise(std::vector<float>& baseNoise, int octaveCount, int width, int height);

private:
	/// @brief interpolates 2 values
	/// @param x0 first parameter
	/// @param x1 second parameter
	/// @param alpha alpha value of interpolation
	/// @return float interpolated value
	static float interpolate(float x0, float x1, float alpha);
};

#endif /* NOISE_H */
