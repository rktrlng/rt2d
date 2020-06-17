#include "vector4.h"

namespace math {

double dot(Vector4 a, Vector4 b)
{
    double x = a.x * b.x;
    double y = a.y * b.y;
    double z = a.z * b.z;

    return (x + y + z);
}

Vector4 cross(Vector4 a, Vector4 b)
{
    double x = (a.y * b.z) - (a.z * b.y);
    double y = (a.z * b.x) - (a.x * b.z);
    double z = (a.x * b.y) - (a.y * b.x);
    double w = 1.0;

    return Vector4(x,y,z,w);
}

double magnitude(Vector4 v)
{
    return sqrtf(magnitudeSquared(v));
}

double magnitudeSquared(Vector4 v)
{
    double x = v.x;
    double y = v.y;
    double z = v.z;

    return (x*x)+(y*y)+(z*z);
}

Vector4 normalize(Vector4 v) {
    double l = magnitude(v);
    Vector4 n = Vector4();
    if (l != 0.0) {
        n.x = v.x / l;
        n.y = v.y / l;
        n.z = v.z / l;
        n.w = v.w / l;
    }
    return n;
}

void print(Vector4 v) {
        std::cout << "vec4 { " << v.x << ", " << v.y << ", " << v.z << ", " << v.w << " }" << std::endl;
    }

} // namespace math
