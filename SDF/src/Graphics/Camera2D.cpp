#include <PCH.hpp>
#include <SDF/Graphics/Camera2D.hpp>
#include <SDF/Graphics/Math.hpp>

namespace sdf {

	Camera2D::Camera2D(const float left, const float right, const float bottom, const float top)
		: projectionMatrix(ortho(left, right, bottom, top, -1.0f, 1.0f)), viewMatrix(1.0f), viewProjectionMatrix(1.0f), position(0.0f, 0.0f, 0.0f), rotation(0.0f) {
		recalculateMatrix();
	}

	void Camera2D::setProjection(const float left, const float right, const float bottom, const float top) {
		projectionMatrix = ortho(left, right, bottom, top, -1.0f, 1.0f);
	}

	void Camera2D::recalculateMatrix() {

		viewMatrix = Mat4f(1.0f);
		viewMatrix = translate(viewMatrix, position);
		viewMatrix = rotate(viewMatrix, rotation, Vec3f(0.0f, 0.0f, 1.0f));

		viewProjectionMatrix = projectionMatrix * viewMatrix;

	}

}
