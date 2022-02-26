#pragma once

#include "Matrix.hpp"

namespace sdf {

	class Camera2D {

	public:
		Camera2D(const float left, const float right, const float bottom, const float top);

		void setProjection(const float left, const float right, const float bottom, const float top);

		void setRotation(const float rotation) { this->rotation = rotation; recalculateMatrix(); }
		void setPosition(const Vec3f& position) { this->position = position; recalculateMatrix(); }
		void setProjectionMatrix(const Mat4f& projection) { this->projectionMatrix = projection; recalculateMatrix(); }

		float getRotation() const { return rotation; }
		Vec3f getPosition() const { return position; }

		const Mat4f& getViewMatrix() const { return viewMatrix; }
		const Mat4f& getProjectionMatrix() const { return projectionMatrix; }
		const Mat4f& getViewProjectionMatrix() const { return viewProjectionMatrix; }

	private:
		void recalculateMatrix();

	private:
		float rotation;
		Vec3f position;
		Mat4f viewMatrix;
		Mat4f projectionMatrix;
		Mat4f viewProjectionMatrix;

	};

}
