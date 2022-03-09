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

namespace sdf {

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
            std::cos(a) + std::pow(r.x, 2) * (1 - std::cos(a)), r.y * r.x * (1 - std::cos(a)) + r.z * std::sin(a), r.z * r.x * (1 - std::cos(a)) - r.y * std::sin(a), 0,
            r.x * r.y * (1 - std::cos(a)) - r.z * std::sin(a), std::cos(a) + std::pow(r.y, 2) * (1 - std::cos(a)), r.z * r.y * (1 - std::cos(a)) + r.x * std::sin(a), 0,
            r.x * r.z * (1 - std::cos(a)) + r.y * std::sin(a), r.y * r.z * (1 - std::cos(a)) - r.x * std::sin(a), std::cos(a) + std::pow(r.z, 2) * (1 - std::cos(a)), 0,
            0, 0, 0, 1
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

}
