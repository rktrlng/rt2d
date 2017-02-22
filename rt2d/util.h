/**
 * @file util.h
 *
 * @brief The util header file.
 *
 * This file is part of RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *   - Initial commit
 */

#ifndef UTIL_H_
#define UTIL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/**
 * @brief returns the low byte of a word
 * @param wrd The word we need the low byte from
 * @return the low byte of the word
 */
uint8_t lowByte(uint16_t wrd);
/**
 * @brief returns the high byte of a word
 * @param wrd The word we need the high byte from
 * @return the high byte of the word
 */
uint8_t highByte(uint16_t wrd);
/**
 * @brief returns a word made of two bytes
 * @param high The high byte for the word
 * @param low The low byte for the word
 * @return the word
 */
uint16_t makeWord(unsigned char high, unsigned char low);
/**
 * @brief maps a value from 1 range to another
 * usage example: int val = map(973, 0, 1023, 0, 255); // returns: 242
 * @param x The value we need to map
 * @param in_min  The low range of the input value
 * @param in_max  The upper range of the input value
 * @param out_min The low range of the output value
 * @param out_max The upper range of the output value
 * @return double the value
 */
double map(double x, double in_min, double in_max, double out_min, double out_max);

/**
 * @brief constrains a value between a range
 * @param value The value we need to constrain
 * @param min  The low range of the input value
 * @param max  The upper range of the input value
 * @return double value
 */
double constrain(double value, double min, double max);

#ifdef __cplusplus
}
#endif

#endif // UTIL_H_
