/*
* Copyright (c) 2021 Adam Charvát <https://www.skulaurun.eu>
* Licensed under the MIT License,
* for details see accompanying LICENSE file or a copy at
* <https://github.com/Skulaurun/SDF/blob/v1.0.0/LICENSE>.
* SPDX-License-Identifier: MIT
*/

#pragma once

#include <cstdint>
#include <type_traits>

namespace sdf {

    template<typename T>
    struct Vector3D;

    template<typename T>
    struct Vector4D;

    template<typename T>
    struct Vector2D {
        static_assert(std::is_arithmetic_v<T>);

    public:
        constexpr Vector2D() : x(0), y(0) {}
        constexpr Vector2D(const T& n) : x(n), y(n) {}
        constexpr Vector2D(const T& x, const T& y) : x(x), y(y) {}

        constexpr Vector2D(const Vector3D<T>& v) : x(v.x), y(v.y) {}
        constexpr Vector2D(const Vector4D<T>& v) : x(v.x), y(v.y) {}

        Vector2D<T>& operator+=(const Vector2D<T>& other) {
            x += other.x; y += other.y;
            return *this;
        }

        Vector2D<T>& operator-=(const Vector2D<T>& other) {
            x -= other.x; y -= other.y;
            return *this;
        }

        friend Vector2D<T> operator+(Vector2D<T> left, const Vector2D<T>& right) {
            left += right;
            return left;
        }

        friend Vector2D<T> operator-(Vector2D<T> left, const Vector2D<T>& right) {
            left -= right;
            return left;
        }

        Vector2D<T> operator-() const {
            return { -x, -y };
        }

        T& operator[](const uint32_t index) const { // TODO: Assert size > index?
            return *((T*)this + index);
        }

        explicit operator T*() const {
            return (T*)this;
        }

    public:
        T x, y;

    };

    template<typename T>
    struct Vector3D {
        static_assert(std::is_arithmetic_v<T>);

    public:
        constexpr Vector3D() : x(0), y(0) {}
        constexpr Vector3D(const T& n) : x(n), y(n) {}
        constexpr Vector3D(const T& x, const T& y, const T& z) : x(x), y(y), z(z) {}

        constexpr Vector3D(const Vector4D<T>& v) : x(v.x), y(v.y), z(v.z) {}
        constexpr Vector3D(const Vector2D<T>& v, const T& z) : x(v.x), y(v.y), z(z) {}

        Vector3D<T>& operator+=(const Vector3D<T>& other) {
            x += other.x; y += other.y; z += other.z;
            return *this;
        }

        Vector3D<T>& operator-=(const Vector3D<T>& other) {
            x -= other.x; y -= other.y; z -= other.z;
            return *this;
        }

        friend Vector3D<T> operator+(Vector3D<T> left, const Vector3D<T>& right) {
            left += right;
            return left;
        }

        friend Vector3D<T> operator-(Vector3D<T> left, const Vector3D<T>& right) {
            left -= right;
            return left;
        }

        Vector3D<T> operator-() const {
            return { -x, -y, -z };
        }

        T& operator[](const uint32_t index) const { // TODO: Assert size > index?
            return *((T*)this + index);
        }

        explicit operator T*() const {
            return (T*)this;
        }

    public:
        T x, y, z;

    };

    template<typename T>
    struct Vector4D {
        static_assert(std::is_arithmetic_v<T>);

    public:
        constexpr Vector4D() : x(0), y(0), z(0), w(0) {}
        constexpr Vector4D(const T& n) : x(n), y(n), z(n), w(n) {}
        constexpr Vector4D(const T& x, const T& y, const T& z, const T& w) : x(x), y(y), z(z), w(w) {}

        constexpr Vector4D(const Vector2D<T>& v1, const Vector2D<T>& v2) : x(v1.x), y(v1.y), z(v2.x), w(v2.y) {}
        constexpr Vector4D(const Vector2D<T>& v, const T z, const T w) : x(v.x), y(v.y), z(z), w(w) {}
        constexpr Vector4D(const Vector3D<T>& v, const T w) : x(v.x), y(v.y), z(v.z), w(w) {}

        Vector4D<T>& operator+=(const Vector4D<T>& other) {
            x += other.x; y += other.y;
            z += other.z; w += other.w;
            return *this;
        }

        Vector4D<T>& operator-=(const Vector4D<T>& other) {
            x -= other.x; y -= other.y;
            z -= other.z; w -= other.w;
            return *this;
        }

        friend Vector4D<T> operator+(Vector4D<T> left, const Vector4D<T>& right) {
            left += right;
            return left;
        }

        friend Vector4D<T> operator-(Vector4D<T> left, const Vector4D<T>& right) {
            left -= right;
            return left;
        }

        Vector4D<T> operator-() const {
            return { -x, -y, -z, -w };
        }

        T& operator[](const uint32_t index) const { // TODO: Assert size > index?
            return *((T*)this + index);
        }

        explicit operator T*() const {
            return (T*)this;
        }

    public:
        T x, y, z, w;

    };

    /* 2 Dimensional Vectors */

    using Vec2i = Vector2D<int>;
    using Vec2u = Vector2D<unsigned int>;

    using Vec2f = Vector2D<float>;
    using Vec2d = Vector2D<double>;

    /* 3 Dimensional Vectors */

    using Vec3i = Vector3D<int>;
    using Vec3u = Vector3D<unsigned int>;

    using Vec3f = Vector3D<float>;
    using Vec3d = Vector3D<double>;

    /* 4 Dimension Vectors */

    using Vec4i = Vector4D<int>;
    using Vec4u = Vector4D<unsigned int>;

    using Vec4f = Vector4D<float>;
    using Vec4d = Vector4D<double>;

}
