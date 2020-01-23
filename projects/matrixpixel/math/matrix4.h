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

    static void print(const Matrix4 matrix) {
        std::cout << "--------------" << std::endl;
        for (size_t i = 0; i < 4; i++) {
            for (size_t j = 0; j < 4; j++) {
                std::cout << matrix.m[i][j] << " ";
            }
            std::cout << std::endl;

        }
    }

    static Vector4 matmul(const Matrix4 m, const Vector4 v) {
        Vector4 result = Vector4();
        result.x = (m.m[0][0] * v.x) + (m.m[0][1] * v.y) + (m.m[0][2] * v.z) + (m.m[0][3] * v.w);
        result.y = (m.m[1][0] * v.x) + (m.m[1][1] * v.y) + (m.m[1][2] * v.z) + (m.m[1][3] * v.w);
        result.z = (m.m[2][0] * v.x) + (m.m[2][1] * v.y) + (m.m[2][2] * v.z) + (m.m[2][3] * v.w);
        result.w = (m.m[3][0] * v.x) + (m.m[3][1] * v.y) + (m.m[3][2] * v.z) + (m.m[3][3] * v.w);
        return result;
    }

    static Matrix4 matmul(const Matrix4 a, const Matrix4 b) {
        Matrix4 result = Matrix4();
        for (size_t i = 0; i < 4; i++) {
            for (size_t j = 0; j < 4; j++) {
                double sum = 0;
                for (size_t k = 0; k < 4; k++) {
                    sum += a.m[i][k] * b.m[k][j];
                }
                result.m[i][j] = sum;
            }
        }
        return result;
    }

    static Matrix4 modelMatrix(const Vector4 position, const Vector4 rotation, const Vector4 scale) {
        // get corresponding matrices
		Matrix4 scalematrix = Matrix4::scaleMatrix4(scale);
		Matrix4 rotmatrix = Matrix4::rotationMatrix4(rotation);
		Matrix4 transmatrix = Matrix4::translationMatrix4(position);

		// create modelmatrix. order is important (first scale, then rotate, finally translate).
		Matrix4 modelmatrix;
		modelmatrix = Matrix4::matmul(scalematrix, modelmatrix);
		modelmatrix = Matrix4::matmul(rotmatrix, modelmatrix);
		modelmatrix = Matrix4::matmul(transmatrix, modelmatrix);
        return modelmatrix;
    }

    /*
    static Matrix4 lookAt(Vector4 eye, Vector4 center, Vector4 up) {
        Vector4 centerminuseye = Vector4(center.x-eye.x, center.y-eye.y, center.z-eye.z, center.w-eye.w);
		Vector4 f = Vector4::normalize(centerminuseye);
        Vector4 crossfup = Vector4::cross(f, up);
        Vector4 s = Vector4::normalize(crossfup);
        Vector4 u = Vector4::cross(s, f);

		Matrix4 result = Matrix4();
		result.m[0][0] = s.x;
		result.m[1][0] = s.y;
		result.m[2][0] = s.z;
		result.m[0][1] = u.x;
		result.m[1][1] = u.y;
		result.m[2][1] = u.z;
		result.m[0][2] =-f.x;
		result.m[1][2] =-f.y;
		result.m[2][2] =-f.z;
		result.m[3][0] =-Vector4::dot(s, eye);
		result.m[3][1] =-Vector4::dot(u, eye);
		result.m[3][2] = Vector4::dot(f, eye);
		return result;
	}

    static Matrix4 perspectiveMatrix(const double fovy, const double aspect, const double zNear, const double zFar) {
		double rad = fovy;
		double tanHalfFovy = tan(rad / 2);

		Matrix4 result = Matrix4();
		result.m[0][0] = 1.0 / (aspect * tanHalfFovy);
		result.m[1][1] = 1.0 / (tanHalfFovy);
		result.m[2][2] = - (zFar + zNear) / (zFar - zNear);
		result.m[2][3] = - 1.0;
		result.m[3][2] = - (2 * zFar * zNear) / (zFar - zNear);
		return result;
	}
    */

    // #################### Matrices ####################
    static Matrix4 scaleMatrix4(const Vector4 scale) {
        Matrix4 sm = Matrix4();
        sm.m[0][0] = scale.x;
        sm.m[1][1] = scale.y;
        sm.m[2][2] = scale.z;

        // sm.m[0][0] = scale.x; sm.m[0][1] = 0.0;     sm.m[0][2] = 0.0;     sm.m[0][3] = 0.0;
        // sm.m[1][0] = 0.0;     sm.m[1][1] = scale.y; sm.m[1][2] = 0.0;     sm.m[1][3] = 0.0;
        // sm.m[2][0] = 0.0;     sm.m[2][1] = 0.0;     sm.m[2][2] = scale.z; sm.m[2][3] = 0.0;
        // sm.m[3][0] = 0.0;     sm.m[3][1] = 0.0;     sm.m[3][2] = 0.0;     sm.m[3][3] = 1.0;
        return sm;
    }

    static Matrix4 rotationMatrix4(const Vector4 angles) {
        Matrix4 result = Matrix4();

        Matrix4 rz = rotationZMatrix4(angles.z);
        Matrix4 ry = rotationYMatrix4(angles.y);
        Matrix4 rx = rotationXMatrix4(angles.x);

        result = matmul(result, rz);
        result = matmul(result, ry);
        result = matmul(result, rx);

        return result;
    }

    static Matrix4 translationMatrix4(const Vector4 delta) {
        Matrix4 tm = Matrix4();
        tm.m[0][3] = delta.x;
        tm.m[1][3] = delta.y;
        tm.m[2][3] = delta.z;

        // tm.m[0][0] = 1.0; tm.m[0][1] = 0.0; tm.m[0][2] = 0.0; tm.m[0][3] = delta.x;
        // tm.m[1][0] = 0.0; tm.m[1][1] = 1.0; tm.m[1][2] = 0.0; tm.m[1][3] = delta.y;
        // tm.m[2][0] = 0.0; tm.m[2][1] = 0.0; tm.m[2][2] = 1.0; tm.m[2][3] = delta.z;
        // tm.m[3][0] = 0.0; tm.m[3][1] = 0.0; tm.m[3][2] = 0.0; tm.m[3][3] = 1.0;
        return tm;
    }

// ######################## private ########################
private:
    static Matrix4 rotationZMatrix4(const double angle) {
        Matrix4 rm = Matrix4();
        rm.m[0][0] = cos(angle);
        rm.m[0][1] = -sin(angle);
        rm.m[1][0] = sin(angle);
        rm.m[1][1] = cos(angle);

        // rm.m[0][0] = cos(angle); rm.m[0][1] = -sin(angle); rm.m[0][2] = 0.0; rm.m[0][3] = 0.0;
        // rm.m[1][0] = sin(angle); rm.m[1][1] = cos(angle);  rm.m[1][2] = 0.0; rm.m[1][3] = 0.0;
        // rm.m[2][0] = 0.0;        rm.m[2][1] = 0.0;         rm.m[2][2] = 1.0; rm.m[2][3] = 0.0;
        // rm.m[3][0] = 0.0;        rm.m[3][1] = 0.0;         rm.m[3][2] = 0.0; rm.m[3][3] = 1.0;
        return rm;
    }

    static Matrix4 rotationYMatrix4(const double angle) {
        Matrix4 rm = Matrix4();
        rm.m[0][0] = cos(angle);
        rm.m[0][2] = sin(angle);
        rm.m[2][0] = -sin(angle);
        rm.m[2][2] = cos(angle);

        // rm.m[0][0] = cos(angle);  rm.m[0][1] = 0.0; rm.m[0][2] = sin(angle); rm.m[0][3] = 0.0;
        // rm.m[1][0] = 0.0;         rm.m[1][1] = 1.0; rm.m[1][2] = 0.0;        rm.m[1][3] = 0.0;
        // rm.m[2][0] = -sin(angle); rm.m[2][1] = 0.0; rm.m[2][2] = cos(angle); rm.m[2][3] = 0.0;
        // rm.m[3][0] = 0.0;         rm.m[3][1] = 0.0; rm.m[3][2] = 0.0;        rm.m[3][3] = 1.0;
        return rm;
    }

    static Matrix4 rotationXMatrix4(const double angle) {
        Matrix4 rm = Matrix4();
        rm.m[1][1] = cos(angle);
        rm.m[1][2] = -sin(angle);
        rm.m[2][1] = sin(angle);
        rm.m[2][2] = cos(angle);

        // rm.m[0][0] = 1.0; rm.m[0][1] = 0.0;        rm.m[0][2] = 0.0;         rm.m[0][3] = 0.0;
        // rm.m[1][0] = 0.0; rm.m[1][1] = cos(angle); rm.m[1][2] = -sin(angle); rm.m[1][3] = 0.0;
        // rm.m[2][0] = 0.0; rm.m[2][1] = sin(angle); rm.m[2][2] = cos(angle);  rm.m[2][3] = 0.0;
        // rm.m[3][0] = 0.0; rm.m[3][1] = 0.0;        rm.m[3][2] = 0.0;         rm.m[3][3] = 1.0;
        return rm;
    }
/*
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
*/
};

} // namespace math

#endif // MATRIX4_H_
