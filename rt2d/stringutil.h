#ifndef STRINGUTIL_H_
#define STRINGUTIL_H_

#include <string>
#include <time.h>
#include <sstream>

namespace rt2d {

    template<typename T>
    inline std::string to_string(T number) {
        std::stringstream temp_stry;
    	temp_stry << (number);
    	return temp_stry.str();
    }
}

#endif
