#ifndef MATRIX4_H_
#define MATRIX4_H_

#include <iostream>
#include <cmath>
#include "vector4.h"

namespace math {

class Matrix4 {
public:
    double m[16] = {
        1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0
    }; // Identity

    Matrix4() {

    }

    ~Matrix4() {

    }

    void set(const double* other) {
        // this is unsafe
        for (size_t i = 0; i < 16; i++) {
            this->m[i] = other[i];
        }
    }

    void print() {
        std::cout << "--------" << std::endl;
        for (size_t i = 0; i < 16; i++) {
            std::cout << this->m[i] << " ";
            if (i == 3 || i == 7 || i == 11 || i == 15) {
                std::cout << std::endl;
            }
        }
    }

    static Vector4 matmul(const Matrix4 m, const Vector4 v) {
        Vector4 result = Vector4();
        result.x = (m.m[0] * v.x) + (m.m[1] * v.y) + (m.m[2] * v.z) + (m.m[3] * v.w);
        result.y = (m.m[4] * v.x) + (m.m[5] * v.y) + (m.m[6] * v.z) + (m.m[7] * v.w);
        result.z = (m.m[8] * v.x) + (m.m[9] * v.y) + (m.m[10] * v.z) + (m.m[11] * v.w);
        result.w = (m.m[12] * v.x) + (m.m[13] * v.y) + (m.m[14] * v.z) + (m.m[15] * v.w);
        return result;
    }

    // #################### Scale ####################
    static Vector4 scale(const Vector4 origin, const Vector4 scale) {
        return matmul(scaleMatrix4(scale), origin);
    }

    // #################### Rotation ####################
    static Vector4 rotateZ(const Vector4 v, const double angle) {
        return matmul(rotationZMatrix4(angle), v);
    }

    static Vector4 rotateY(const Vector4 v, const double angle) {
        return matmul(rotationYMatrix4(angle), v);
    }

    static Vector4 rotateX(const Vector4 v, const double angle) {
        return matmul(rotationXMatrix4(angle), v);
    }

    static Vector4 rotate(const Vector4 v, const Vector4 a) {
        Vector4 vec = Vector4(v.x, v.y, v.z, v.w);
        vec = rotateX(vec, a.x);
        vec = rotateY(vec, a.y);
        vec = rotateZ(vec, a.z);
        return vec;
    }

    // #################### Translation ####################
    static Vector4 translate(const Vector4 origin, const Vector4 delta) {
        return matmul(translationMatrix4(delta), origin);
    }

    // #################### Matrices ####################
    static Matrix4 scaleMatrix4(const Vector4 scale) {
        Matrix4 scalemat = Matrix4();
        double scl[16] = {
            scale.x, 0.0, 0.0, 0.0,
            0.0, scale.y, 0.0, 0.0,
            0.0, 0.0, scale.z, 0.0,
            0.0, 0.0, 0.0, 1.0
        };
        scalemat.set(scl);
        return scalemat;
    }

    static Matrix4 rotationZMatrix4(const double angle) {
        Matrix4 rotmat = Matrix4();
        double rotz[16] = {
            cos(angle), -sin(angle), 0.0, 0.0,
            sin(angle), cos(angle), 0.0, 0.0,
            0.0, 0.0, 1.0, 0.0,
            0.0, 0.0, 0.0, 1.0
        };
        rotmat.set(rotz);
        return rotmat;
    }

    static Matrix4 rotationYMatrix4(const double angle) {
        Matrix4 rotmat = Matrix4();
        double roty[16] = {
            cos(angle), 0.0, sin(angle), 0.0,
            0.0, 1.0, 0.0, 0.0,
            -sin(angle), 0.0, cos(angle), 0.0,
            0.0, 0.0, 0.0, 1.0
        };
        rotmat.set(roty);
        return rotmat;
    }

    static Matrix4 rotationXMatrix4(const double angle) {
        Matrix4 rotmat = Matrix4();
        double rotx[16] = {
            1.0, 0.0, 0.0, 0.0,
            0.0, cos(angle), -sin(angle), 0.0,
            0.0, sin(angle), cos(angle), 0.0,
            0.0, 0.0, 0.0, 1.0
        };
        rotmat.set(rotx);
        return rotmat;
    }

    static Matrix4 translationMatrix4(const Vector4 delta) {
        Matrix4 transmat = Matrix4();
        double trans[16] = {
            1.0, 0.0, 0.0, delta.x,
            0.0, 1.0, 0.0, delta.y,
            0.0, 0.0, 1.0, delta.z,
            0.0, 0.0, 0.0, 1.0
        };
        transmat.set(trans);
        return transmat;
    }

};

} // namespace math

#endif // MATRIX4_H_
