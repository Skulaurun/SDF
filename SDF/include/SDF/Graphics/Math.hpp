/*
* Copyright (c) 2021 Adam Charvát <https://www.skulaurun.eu>
* Licensed under the MIT License,
* for details see accompanying LICENSE file or a copy at
* <https://github.com/Skulaurun/SDF/blob/v1.0.0/LICENSE>.
* SPDX-License-Identifier: MIT
*/

#pragma once

#include "Matrix.hpp"

#include <cmath>

// General math for 2D and 3D

namespace sdf {

    template<typename T> inline T sin(const T& x) { return std::sin(x); }
    template<typename T> inline T cos(const T& x) { return std::cos(x); }
    template<typename T> inline T tan(const T& x) { return std::tan(x); }
    template<typename T> inline T cot(const T& x) { return 1.0 / std::tan(x); }
    template<typename T> inline T pow(const T& x, const T& y) { return std::pow(x, y); }
    template<typename T> inline T sqrt(const T& x) { return std::sqrt(x); }
    
    template<> inline float sin(const float& x) { return std::sinf(x); }
    template<> inline float cos(const float& x) { return std::cosf(x); }
    template<> inline float tan(const float& x) { return std::tanf(x); }
    template<> inline float cot(const float& x) { return 1.0f / std::tanf(x); }
    template<> inline float pow(const float& x, const float& y) { return std::powf(x, y); }
    template<> inline float sqrt(const float& x) { return std::sqrtf(x); }

    template<typename T>
    Matrix4x4<T> translate(const Vector3D<T>& v) {
        return Matrix4x4<T>(
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            v[0], v[1], v[2], 1
        );
    }

    template<typename T>
    Matrix4x4<T> scale(const Vector3D<T>& v) {
        return Matrix4x4<T>(
            v[0], 0, 0, 0,
            0, v[1], 0, 0,
            0, 0, v[2], 0,
            0, 0, 0, 1
        );
    }

    template<typename T>
    Matrix4x4<T> rotate(const T a, const Vector3D<T>& r) {
        return Matrix4x4<T>(

            cos(a) + pow(r.x, T(2)) * (T(1) - cos(a)),
            r.y * r.x * (T(1) - cos(a)) + r.z * sin(a),
            r.z * r.x * (T(1) - cos(a)) - r.y * sin(a),
            T(0),

            r.x * r.y * (T(1) - cos(a)) - r.z * sin(a),
            cos(a) + pow(r.y, T(2)) * (T(1) - cos(a)),
            r.z * r.y * (T(1) - cos(a)) + r.x * sin(a),
            T(0),

            r.x * r.z * (T(1) - cos(a)) + r.y * sin(a),
            r.y * r.z * (T(1) - cos(a)) - r.x * sin(a),
            cos(a) + pow(r.z, T(2)) * (T(1) - cos(a)),
            T(0),

            T(0), T(0), T(0), T(1)

        );
    }

    template<typename T>
    Matrix4x4<T> translate(const Matrix4x4<T>& m, const Vector3D<T>& v) {
        return m * translate(v);
    }

    template<typename T>
    Matrix4x4<T> scale(const Matrix4x4<T>& m, const Vector3D<T>& v) {
        return m * scale(v);
    }

    template<typename T>
    Matrix4x4<T> rotate(const Matrix4x4<T>& m, const T angle, const Vector3D<T>& axis) {
        return m * rotate(angle, axis);
    }

    template<typename T>
    Matrix4x4<T> ortho(const T left, const T right, const T bottom, const T top, const T near, const T far) {
        return Matrix4x4<T>(
            2 / (right - left), 0, 0, 0,
            0, 2 / (top - bottom), 0, 0,
            0, 0, -2 / (far - near), 0,
            -(right + left) / (right - left), -(top + bottom) / (top - bottom), -(far + near) / (far - near), 1
        );
    }

    template<typename T>
    Vector4D<T> operator*(const Matrix4x4<T>& matrix, const Vector4D<T> vector) {
        return Vector4D<T>(
            matrix[0][0] * vector.x + matrix[1][0] * vector.y + matrix[2][0] * vector.z + matrix[3][0] * vector.w,
            matrix[0][1] * vector.x + matrix[1][1] * vector.y + matrix[2][1] * vector.z + matrix[3][1] * vector.w,
            matrix[0][2] * vector.x + matrix[1][2] * vector.y + matrix[2][2] * vector.z + matrix[3][2] * vector.w,
            matrix[0][3] * vector.x + matrix[1][3] * vector.y + matrix[2][3] * vector.z + matrix[3][3] * vector.w
        );
    }

}
