/**
 * @file stringutil.h
 *
 * @brief The stringutil header file.
 *
 * This file is part of RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *   - Initial commit
 *   - <VZout> Work around MinGW bug.
 *      - https://gcc.gnu.org/bugzilla/show_bug.cgi?id=52015
 */

#ifndef STRINGUTIL_H_
#define STRINGUTIL_H_

#include <string>
#include <sstream>

namespace rt2d
{
    /**
	 * @brief converts any value to a string
	 *
	 * @param val
	 * the value that needs to be converted to a string
     *
     * @return temp_str
	 * the returned string
	 */
    template<typename T>
    inline std::string to_string(T val)
    {
        std::stringstream temp_str;
        temp_str << (val);
        return temp_str.str();
    }
}

#endif
