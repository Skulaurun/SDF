#pragma once

#include "../Core/Vector.hpp"

namespace sdf {

	template<typename T>
	struct Matrix2x2 {
		static_assert(std::is_arithmetic_v<T>);
		
	public:
		constexpr Matrix2x2(const T n)
			: data {
				{ n, 0 },
				{ 0, n }
			}
		{}

		constexpr Matrix2x2(const T x0, const T y0, const T x1, const T y1)
			: data {
				{ x0, y0 },
				{ x1, y1 }
			}
		{}

		constexpr Matrix2x2(const Vector2D<T>& c0, const Vector2D<T>& c1)
			: data { c0, c1 }
		{}

		template<typename O>
		Matrix2x2<T>& operator+=(const Matrix2x2<O>& other) {

			data[0] += other[0];
			data[1] += other[1];

			return *this;

		}

		template<typename O>
		Matrix2x2<T>& operator*=(const Matrix2x2<O>& other) {

			T x0 = data[0][0], y0 = data[0][1];
			T x1 = data[1][0], y1 = data[1][1];

			data[0][0] = x0 * other[0][0] + x1 * other[0][1];
			data[0][1] = y0 * other[0][0] + y1 * other[0][1];

			data[1][0] = x0 * other[1][0] + x1 * other[1][1];
			data[1][1] = y0 * other[1][0] + y1 * other[1][1];

			return *this;

		}

		template<typename O>
		friend Matrix2x2<T> operator+(Matrix2x2<T> left, const Matrix2x2<O>& right) {
			left += right;
			return left;
		}

		template<typename O>
		friend Matrix2x2<T> operator*(Matrix2x2<T> left, const Matrix2x2<O>& right) {
			left *= right;
			return left;
		}

		Vector2D<T>& operator[](const uint32_t index) const {
			return *((Vector2D<T>*)this + index);
		}

		explicit operator T*() const {
			return (T*)this;
		}

	private:
		Vector2D<T> data[2];

	};

	template<typename T>
	struct Matrix3x3 {

	public:
		constexpr Matrix3x3(const T n)
			: data {
				{ n, 0, 0 },
				{ 0, n, 0 },
				{ 0, 0, n }
			}
		{}

		constexpr Matrix3x3(
			const T x0, const T y0, const T z0,
			const T x1, const T y1, const T z1,
			const T x2, const T y2, const T z2
		)
			: data {
				{ x0, y0, z0 },
				{ x1, y1, z1 },
				{ x2, y2, z2 }
			}
		{}

		constexpr Matrix3x3(const Vector3D<T>& c1, const Vector3D<T>& c2, const Vector3D<T>& c3)
			: data { c1, c2, c3 }
		{}

		template<typename O>
		Matrix3x3<T>& operator+=(const Matrix3x3<O>& other) {

			data[0] += other[0];
			data[1] += other[1];
			data[2] += other[2];

			return *this;

		}

		template<typename O>
		Matrix3x3<T>& operator*=(const Matrix3x3<O>& other) {

			T x0 = data[0][0], y0 = data[0][1], z0 = data[0][2];
			T x1 = data[1][0], y1 = data[1][1], z1 = data[1][2];
			T x2 = data[2][0], y2 = data[2][1], z2 = data[2][2];

			data[0][0] = x0 * other[0][0] + x1 * other[0][1] + x2 * other[0][2];
			data[0][1] = y0 * other[0][0] + y1 * other[0][1] + y2 * other[0][2];
			data[0][2] = z0 * other[0][0] + z1 * other[0][1] + z2 * other[0][2];

			data[1][0] = x0 * other[1][0] + x1 * other[1][1] + x2 * other[1][2];
			data[1][1] = y0 * other[1][0] + y1 * other[1][1] + y2 * other[1][2];
			data[1][2] = z0 * other[1][0] + z1 * other[1][1] + z2 * other[1][2];

			data[2][0] = x0 * other[2][0] + x1 * other[2][1] + x2 * other[2][2];
			data[2][1] = y0 * other[2][0] + y1 * other[2][1] + y2 * other[2][2];
			data[2][2] = z0 * other[2][0] + z1 * other[2][1] + z2 * other[2][2];

			return *this;

		}

		template<typename O>
		friend Matrix3x3<T> operator+(Matrix3x3<T> left, const Matrix3x3<O>& right) {
			left += right;
			return left;
		}

		template<typename O>
		friend Matrix3x3<T> operator*(Matrix3x3<T> left, const Matrix3x3<O>& right) {
			left *= right;
			return left;
		}

		Vector3D<T>& operator[](const uint32_t index) const {
			return *((Vector3D<T>*)this + index);
		}

		explicit operator T*() const {
			return (T*)this;
		}

	private:
		Vector3D<T> data[3];

	};

	template<typename T>
	struct Matrix4x4 {

	public:
		constexpr Matrix4x4(const T n)
			: data {
				{ n, 0, 0, 0 },
				{ 0, n, 0, 0 },
				{ 0, 0, n, 0 },
				{ 0, 0, 0, n }
			}
		{}

		constexpr Matrix4x4(
			const T x0, const T y0, const T z0, const T w0,
			const T x1, const T y1, const T z1, const T w1,
			const T x2, const T y2, const T z2, const T w2,
			const T x3, const T y3, const T z3, const T w3
		)
			: data {
				{ x0, y0, z0, w0 },
				{ x1, y1, z1, w1 },
				{ x2, y2, z2, w2 },
				{ x3, y3, z3, w3 }
			}
		{}

		constexpr Matrix4x4(const Vector4D<T>& c1, const Vector4D<T>& c2, const Vector4D<T>& c3, const Vector4D<T>& c4)
			: data{ c1, c2, c3, c4 }
		{}

		template<typename O>
		Matrix4x4<T>& operator+=(const Matrix4x4<O>& other) {

			data[0] += other[0];
			data[1] += other[1];
			data[2] += other[2];
			data[3] += other[3];

			return *this;

		}

		template<typename O>
		Matrix4x4<T>& operator*=(const Matrix4x4<O>& other) {

			T x0 = data[0][0], y0 = data[0][1], z0 = data[0][2], w0 = data[0][3];
			T x1 = data[1][0], y1 = data[1][1], z1 = data[1][2], w1 = data[1][3];
			T x2 = data[2][0], y2 = data[2][1], z2 = data[2][2], w2 = data[2][3];
			T x3 = data[3][0], y3 = data[3][1], z3 = data[3][2], w3 = data[3][3];

			data[0][0] = x0 * other[0][0] + x1 * other[0][1] + x2 * other[0][2] + x3 * other[0][3];
			data[0][1] = y0 * other[0][0] + y1 * other[0][1] + y2 * other[0][2] + y3 * other[0][3];
			data[0][2] = z0 * other[0][0] + z1 * other[0][1] + z2 * other[0][2] + z3 * other[0][3];
			data[0][3] = w0 * other[0][0] + w1 * other[0][1] + w2 * other[0][2] + w3 * other[0][3];

			data[1][0] = x0 * other[1][0] + x1 * other[1][1] + x2 * other[1][2] + x3 * other[1][3];
			data[1][1] = y0 * other[1][0] + y1 * other[1][1] + y2 * other[1][2] + y3 * other[1][3];
			data[1][2] = z0 * other[1][0] + z1 * other[1][1] + z2 * other[1][2] + z3 * other[1][3];
			data[1][3] = w0 * other[1][0] + w1 * other[1][1] + w2 * other[1][2] + w3 * other[1][3];

			data[2][0] = x0 * other[2][0] + x1 * other[2][1] + x2 * other[2][2] + x3 * other[2][3];
			data[2][1] = y0 * other[2][0] + y1 * other[2][1] + y2 * other[2][2] + y3 * other[2][3];
			data[2][2] = z0 * other[2][0] + z1 * other[2][1] + z2 * other[2][2] + z3 * other[2][3];
			data[2][3] = w0 * other[2][0] + w1 * other[2][1] + w2 * other[2][2] + w3 * other[2][3];

			data[3][0] = x0 * other[3][0] + x1 * other[3][1] + x2 * other[3][2] + x3 * other[3][3];
			data[3][1] = y0 * other[3][0] + y1 * other[3][1] + y2 * other[3][2] + y3 * other[3][3];
			data[3][2] = z0 * other[3][0] + z1 * other[3][1] + z2 * other[3][2] + z3 * other[3][3];
			data[3][3] = w0 * other[3][0] + w1 * other[3][1] + w2 * other[3][2] + w3 * other[3][3];

			return *this;

		}

		template<typename O>
		friend Matrix4x4<T> operator+(Matrix4x4<T> left, const Matrix4x4<O>& right) {
			left += right;
			return left;
		}

		template<typename O>
		friend Matrix4x4<T> operator*(Matrix4x4<T> left, const Matrix4x4<O>& right) {
			left *= right;
			return left;
		}

		Vector4D<T>& operator[](const uint32_t index) const {
			return *((Vector4D<T>*)this + index);
		}

		explicit operator T*() const {
			return (T*)this;
		}

	private:
		Vector4D<T> data[4];

	};

	/* 2 Dimensional Matrices */

	using Mat2i = Matrix2x2<int>;
	using Mat2u = Matrix2x2<unsigned int>;

	using Mat2f = Matrix2x2<float>;
	using Mat2d = Matrix2x2<double>;

	/* 3 Dimensional Matrices */

	using Mat3i = Matrix3x3<int>;
	using Mat3u = Matrix3x3<unsigned int>;

	using Mat3f = Matrix3x3<float>;
	using Mat3d = Matrix3x3<double>;

	/* 4 Dimension Matrices */

	using Mat4i = Matrix4x4<int>;
	using Mat4u = Matrix4x4<unsigned int>;

	using Mat4f = Matrix4x4<float>;
	using Mat4d = Matrix4x4<double>;

}
