#ifndef MATRIX4_H_
#define MATRIX4_H_

#include <iostream>
#include <cmath>
#include "vector4.h"

namespace math {

class Matrix4 {
public:
    double m[4][4] = {
        { 1.0, 0.0, 0.0, 0.0 },
        { 0.0, 1.0, 0.0, 0.0 },
        { 0.0, 0.0, 1.0, 0.0 },
        { 0.0, 0.0, 0.0, 1.0 }
    }; // Identity

    Matrix4() {

    }

    ~Matrix4() {

    }

    static Vector4 matmul(const Matrix4 m, const Vector4 v) {
        Vector4 result = Vector4();
        result.x = (m.m[0][0] * v.x) + (m.m[0][1] * v.y) + (m.m[0][2] * v.z) + (m.m[0][3] * v.w);
        result.y = (m.m[1][0] * v.x) + (m.m[1][1] * v.y) + (m.m[1][2] * v.z) + (m.m[1][3] * v.w);
        result.z = (m.m[2][0] * v.x) + (m.m[2][1] * v.y) + (m.m[2][2] * v.z) + (m.m[2][3] * v.w);
        result.w = (m.m[3][0] * v.x) + (m.m[3][1] * v.y) + (m.m[3][2] * v.z) + (m.m[3][3] * v.w);
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
        Matrix4 sm = Matrix4();
        sm.m[0][0] = scale.x; sm.m[0][1] = 0.0;     sm.m[0][2] = 0.0;     sm.m[0][3] = 0.0;
        sm.m[1][0] = 0.0;     sm.m[1][1] = scale.y; sm.m[1][2] = 0.0;     sm.m[1][3] = 0.0;
        sm.m[2][0] = 0.0;     sm.m[2][1] = 0.0;     sm.m[2][2] = scale.z; sm.m[2][3] = 0.0;
        sm.m[3][0] = 0.0;     sm.m[3][1] = 0.0;     sm.m[3][2] = 0.0;     sm.m[3][3] = 1.0;
        return sm;
    }

    static Matrix4 rotationZMatrix4(const double angle) {
        Matrix4 rm = Matrix4();
        rm.m[0][0] = cos(angle); rm.m[0][1] = -sin(angle); rm.m[0][2] = 0.0; rm.m[0][3] = 0.0;
        rm.m[1][0] = sin(angle); rm.m[1][1] = cos(angle);  rm.m[1][2] = 0.0; rm.m[1][3] = 0.0;
        rm.m[2][0] = 0.0;        rm.m[2][1] = 0.0;         rm.m[2][2] = 0.0; rm.m[2][3] = 0.0;
        rm.m[3][0] = 0.0;        rm.m[3][1] = 0.0;         rm.m[3][2] = 0.0; rm.m[3][3] = 1.0;
        return rm;
    }

    static Matrix4 rotationYMatrix4(const double angle) {
        Matrix4 rm = Matrix4();
        rm.m[0][0] = cos(angle);  rm.m[0][1] = 0.0; rm.m[0][2] = sin(angle); rm.m[0][3] = 0.0;
        rm.m[1][0] = 0.0;         rm.m[1][1] = 1.0; rm.m[1][2] = 0.0;        rm.m[1][3] = 0.0;
        rm.m[2][0] = -sin(angle); rm.m[2][1] = 0.0; rm.m[2][2] = cos(angle); rm.m[2][3] = 0.0;
        rm.m[3][0] = 0.0;         rm.m[3][1] = 0.0; rm.m[3][2] = 0.0;        rm.m[3][3] = 1.0;
        return rm;
    }

    static Matrix4 rotationXMatrix4(const double angle) {
        Matrix4 rm = Matrix4();
        rm.m[0][0] = 1.0; rm.m[0][1] = 0.0;        rm.m[0][2] = 0.0;         rm.m[0][3] = 0.0;
        rm.m[1][0] = 0.0; rm.m[1][1] = cos(angle); rm.m[1][2] = -sin(angle); rm.m[1][3] = 0.0;
        rm.m[2][0] = 0.0; rm.m[2][1] = sin(angle); rm.m[2][2] = cos(angle);  rm.m[2][3] = 0.0;
        rm.m[3][0] = 0.0; rm.m[3][1] = 0.0;        rm.m[3][2] = 0.0;         rm.m[3][3] = 1.0;
        return rm;
    }

    static Matrix4 translationMatrix4(const Vector4 delta) {
        Matrix4 tm = Matrix4();
        tm.m[0][0] = 1.0; tm.m[0][1] = 0.0; tm.m[0][2] = 0.0; tm.m[0][3] = delta.x;
        tm.m[1][0] = 0.0; tm.m[1][1] = 1.0; tm.m[1][2] = 0.0; tm.m[1][3] = delta.y;
        tm.m[2][0] = 0.0; tm.m[2][1] = 0.0; tm.m[2][2] = 1.0; tm.m[2][3] = delta.z;
        tm.m[3][0] = 0.0; tm.m[3][1] = 0.0; tm.m[3][2] = 0.0; tm.m[3][3] = 1.0;
        return tm;
    }

};

} // namespace math

#endif // MATRIX4_H_
