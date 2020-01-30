#ifndef VECTOR4_H_
#define VECTOR4_H_

#include <iostream>
#include <cmath>

namespace math {

struct Vector4 {
    double x, y, z, w;

    Vector4() {
        this->x = 0.0;
        this->y = 0.0;
        this->z = 0.0;
        this->w = 1.0;
    }

    Vector4(double _x, double _y, double _z, double _w = 1.0) {
        this->x = _x;
        this->y = _y;
        this->z = _z;
        this->w = _w;
    }

    ~Vector4() {

    }

    void print() {
        std::cout << "vec4 { " << this->x << ", " << this->y << ", " << this->z << ", " << this->w << " }" << std::endl;
    }
};

extern "C" {
    double dot(Vector4 a, Vector4 b);
    Vector4 cross(Vector4 a, Vector4 b);
    double magnitude(Vector4 v);
    double magnitudeSquared(Vector4 v);
    Vector4 normalize(Vector4 v);
}

} // namespace math

#endif // VECTOR4_H_
