/*
* Copyright (c) 2021 Adam Charv�t <https://www.skulaurun.eu>
* Licensed under the MIT License,
* for details see accompanying LICENSE file or a copy at
* <https://github.com/Skulaurun/SDF/blob/v1.0.0/LICENSE>.
* SPDX-License-Identifier: MIT
*/

#include <PCH.hpp>
#include <SDF/Graphics/Camera.hpp>
#include <SDF/Graphics/Math.hpp>

namespace sdf {

    Camera::Camera(const float left, const float right, const float bottom, const float top)
        : position(0.0f, 0.0f), rotation(0.0f), zoom(1.0f),
          viewMatrix(1.0f),
          viewProjectionMatrix(1.0f),
          projectionMatrix(ortho(left, right, bottom, top, -1.0f, 1.0f)) {

        recalculateMatrix();

    }

    void Camera::setProjection(const float left, const float right, const float bottom, const float top) {
        projectionMatrix = ortho(left, right, bottom, top, -1.0f, 1.0f);
        recalculateMatrix();
    }

    void Camera::recalculateMatrix() {

        viewMatrix = Mat4f(1.0f);
        viewMatrix = translate(viewMatrix, sdf::Vec3f(position, 0.0f));
        viewMatrix = rotate(viewMatrix, rotation, Vec3f(0.0f, 0.0f, 1.0f));
        viewMatrix = scale(viewMatrix, Vec3f(zoom));

        viewProjectionMatrix = projectionMatrix * viewMatrix;

    }

}
