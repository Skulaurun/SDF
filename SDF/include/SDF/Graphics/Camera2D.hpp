/*
* Copyright (c) 2021 Adam Charvát <https://www.skulaurun.eu>
* Licensed under the MIT License,
* for details see accompanying LICENSE file or a copy at
* <https://github.com/Skulaurun/SDF/blob/v1.0.0/LICENSE>.
* SPDX-License-Identifier: MIT
*/

#pragma once

#include "Matrix.hpp"

namespace sdf {

	class Camera2D {

	public:
		Camera2D(const float left, const float right, const float bottom, const float top);

		void setProjection(const float left, const float right, const float bottom, const float top);

		void setZoom(const float zoom) { this->zoom = zoom; recalculateMatrix(); }
		void setRotation(const float rotation) { this->rotation = rotation; recalculateMatrix(); }
		void setPosition(const Vec3f& position) { this->position = position; recalculateMatrix(); }
		void setProjectionMatrix(const Mat4f& projection) { this->projectionMatrix = projection; recalculateMatrix(); }

		float getZoom() const { return zoom; }
		float getRotation() const { return rotation; }
		Vec3f getPosition() const { return position; }

		const Mat4f& getViewMatrix() const { return viewMatrix; }
		const Mat4f& getProjectionMatrix() const { return projectionMatrix; }
		const Mat4f& getViewProjectionMatrix() const { return viewProjectionMatrix; }

	private:
		void recalculateMatrix();

	private:
		float zoom;
		float rotation;
		Vec3f position;
		Mat4f viewMatrix;
		Mat4f projectionMatrix;
		Mat4f viewProjectionMatrix;

	};

}
