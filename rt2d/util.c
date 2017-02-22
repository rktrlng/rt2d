/**
 * This file is part of RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *   - Initial commit
 */

#include <rt2d/util.h>

uint8_t lowByte(uint16_t wrd)
{
	return (uint8_t) ((wrd) & 0xFF);
}

uint8_t highByte(uint16_t wrd)
{
	return (uint8_t) ((wrd) >> 8);
}

uint16_t makeWord(unsigned char high, unsigned char low)
{
	return (high << 8) | low;
}

// map(973, 0, 1023, 0, 255); // returns: 242
double map(double x, double in_min, double in_max, double out_min, double out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

double constrain(double value, double min, double max)
{
	if (value < min) { value = min; }
	if (value > max) { value = max; }
	return value;
}
