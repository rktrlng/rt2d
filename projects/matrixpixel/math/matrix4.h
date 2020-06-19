#ifndef MATRIX4_H_
#define MATRIX4_H_

#include <iostream>
#include <cmath>
#include "vector4.h"

namespace math {

struct Matrix4 {
    double m[4][4] = {
        { 1.0, 0.0, 0.0, 0.0 },
        { 0.0, 1.0, 0.0, 0.0 },
        { 0.0, 0.0, 1.0, 0.0 },
        { 0.0, 0.0, 0.0, 1.0 }
    }; // Identity
};

    Vector4 matmulMV(Matrix4 m, Vector4 v);
    Matrix4 matmulMM(Matrix4 a, Matrix4 b);
    Matrix4 rotationZMatrix(double angle);
    Matrix4 rotationYMatrix(double angle);
    Matrix4 rotationXMatrix(double angle);
    Matrix4 scaleMatrix(Vector4 scale);
    Matrix4 rotationMatrix(Vector4 angles);
    Matrix4 translationMatrix(Vector4 delta);
    Matrix4 modelMatrix(Vector4 position, Vector4 rotation, Vector4 scale);
    Vector4 scale(Vector4 origin, Vector4 scale);
    Vector4 rotateZ(Vector4 vec, double angle);
    Vector4 rotateY(Vector4 vec, double angle);
    Vector4 rotateX(Vector4 vec, double angle);
    Vector4 rotate(Vector4 vec, Vector4 angles);
    Vector4 translate(Vector4 origin, Vector4 delta);
    void printMatrix(Matrix4 m);

} // namespace math

#endif // MATRIX4_H_
