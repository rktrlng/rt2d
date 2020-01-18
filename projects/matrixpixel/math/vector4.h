#ifndef VECTOR4_H_
#define VECTOR4_H_

#include <iostream>

namespace math {

class Vector4 {
public:
    double x, y, z, w;

    Vector4() {
        this->x = 0.0;
        this->y = 0.0;
        this->z = 0.0;
        this->w = 1.0;
    }

    Vector4(double _x, double _y, double _z, double _w) {
        this->x = _x;
        this->y = _y;
        this->z = _z;
        this->w = _w;
    }

    ~Vector4() {

    }

    void print() {
        std::cout << "(" << this->x << "," << this->y << "," << this->z << "," << this->w << ")" << std::endl;
    }

private:

};

} // namespace math

#endif // VECTOR4_H_
