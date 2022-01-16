#pragma once

#include "../Core/Vector.hpp"
#include "Matrix.hpp"

namespace sdf::math {

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
	Matrix4x4<T> rotate(const T angle, const Vector3D<T>& v) {

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
	Matrix4x4<T> rotate(const Matrix4x4<T>& m) {

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
