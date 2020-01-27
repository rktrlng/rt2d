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

    /*
    static double dot(const Vector4 a, const Vector4 b)
    {
        double x = a.x * b.x;
        double y = a.y * b.y;
        double z = a.z * b.z;

        return (x + y + z);
    }

    static Vector4 cross(const Vector4 a, const Vector4 b)
    {
        double x = (a.y * b.z) - (a.z * b.y);
        double y = (a.z * b.x) - (a.x * b.z);
        double z = (a.x * b.y) - (a.y * b.x);
        double w = 1.0;

        return Vector4(x,y,z,w);
    }

    static double magnitude(const Vector4 v)
    {
        return sqrtf(magnitudeSquared(v));
    }

    static double magnitudeSquared(const Vector4 v)
    {
        double x = v.x;
        double y = v.y;
        double z = v.z;

        return (x*x)+(y*y)+(z*z);
    }

    static Vector4 normalize(const Vector4 v) {
        double l = Vector4::magnitude(v);
        Vector4 n = Vector4();
        if (l != 0.0) {
            n.x = v.x / l;
            n.y = v.y / l;
            n.z = v.z / l;
            n.w = v.w / l;
        }
        return n;
    }
    */

private:

};

} // namespace math

#endif // VECTOR4_H_
