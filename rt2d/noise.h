/**
 * @file noise.h
 *
 * @brief The Noise header file.
 *
 * This file is part of RT2D, a 2D OpenGL framework.
 *
 * https://github.com/sol-prog/Perlin_Noise
 * from the README:
 *
 * Perlin_Noise
 * ============
 *
 * Here you could find the code for "Perlin noise in C++11", for more informations visit the project webpage:
 *
 * [http://solarianprogrammer.com/2012/07/18/perlin-noise-cpp-11/](http://solarianprogrammer.com/2012/07/18/perlin-noise-cpp-11/)
 *
 * You could use this program under the terms of GPL v3, for more details see:
 *
 * http://www.gnu.org/copyleft/gpl.html
 *
 * Copyright 2012 Sol from www.solarianprogrammer.com
 **/

#ifndef NOISE_H
#define NOISE_H

/// @brief The Noise class generates Perlin Noise.
class PerlinNoise
{
public:
	/// @brief Initialize with the reference values for the permutation vector
	/// @return void
	PerlinNoise();
	/// @brief Generate a new permutation vector based on the value of seed
	/// @param seed the seed of the noise
	/// @return void
	PerlinNoise(unsigned int seed);
	/// @brief get a noise value, for 2D images z can have any value
	/// @param x x
	/// @param y y
	/// @param z z
	/// @return double nois value
	double noise(double x, double y, double z);
private:
	/// @brief fade a value
	/// @param t value
	/// @return double faded value
	double fade(double t);
	/// @brief lerp a value
	/// @param t value
	/// @param a min
	/// @param b max
	/// @return double lerped value
	double lerp(double t, double a, double b);
	/// @brief dotGridGradient
	/// @param hash hash
	/// @param x x
	/// @param y y
	/// @param z z
	/// @return double gradient
	double grad(int hash, double x, double y, double z);
	std::vector<int> p; ///< @brief The permutation vector
};

#endif /* NOISE_H */
