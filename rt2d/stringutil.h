#ifndef STRINGUTIL_H_
#define STRINGUTIL_H_

#include <string>
#include <sstream>

// Work around MinGW bug. Thanks Viktor.
// https://gcc.gnu.org/bugzilla/show_bug.cgi?id=52015
namespace rt2d
{
    template<typename T>
    inline std::string to_string(T val)
    {
        std::stringstream temp_str;
        temp_str << (val);
        return temp_str.str();
    }
}

#endif
