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

    void print() {
        std::cout << "mat4 {" << std::endl;
        for (size_t i = 0; i < 4; i++) {
            for (size_t j = 0; j < 4; j++) {
                std::cout << "  " << this->m[i][j] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << "}" << std::endl;
    }
};

extern "C" {
    Vector4 matmulMV(const Matrix4 m, const Vector4 v);
    Matrix4 matmulMM(const Matrix4 a, const Matrix4 b);
    Matrix4 rotationZMatrix(const double angle);
    Matrix4 rotationYMatrix(const double angle);
    Matrix4 rotationXMatrix(const double angle);
    Matrix4 scaleMatrix(const Vector4 scale);
    Matrix4 rotationMatrix(const Vector4 angles);
    Matrix4 translationMatrix(const Vector4 delta);
    Matrix4 modelMatrix(const Vector4 position, const Vector4 rotation, const Vector4 scale);
    Vector4 scale(const Vector4 origin, const Vector4 scale);
    Vector4 rotateZ(const Vector4 vec, const double angle);
    Vector4 rotateY(const Vector4 vec, const double angle);
    Vector4 rotateX(const Vector4 vec, const double angle);
    Vector4 rotate(const Vector4 vec, const Vector4 angles);
    Vector4 translate(const Vector4 origin, const Vector4 delta);
}

} // namespace math

#endif // MATRIX4_H_
