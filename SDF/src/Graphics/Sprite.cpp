/*
* Copyright (c) 2021 Adam Charvát <https://www.skulaurun.eu>
* Licensed under the MIT License,
* for details see accompanying LICENSE file or a copy at
* <https://github.com/Skulaurun/SDF/blob/v1.0.0/LICENSE>.
* SPDX-License-Identifier: MIT
*/

#include <PCH.hpp>

#include <SDF/Graphics/Sprite.hpp>

namespace sdf {

    Sprite::Sprite(const std::shared_ptr<Texture>& texture) {

        textureRegion = {
            0.0f, 0.0f,
            (float)texture->getWidth(),
            (float)texture->getHeight()
        };

        setTexture(texture);
        setColor(sdf::Vec4f(1.0f));

        setTransform(sdf::Transform(0.0f, {
            (float)texture->getWidth(),
            (float)texture->getHeight()
        }));

    }

    void Sprite::updateRegion() {

        normalizedRegion = {
            textureRegion.x / (float)texture->getWidth(),
            textureRegion.y / (float)texture->getHeight(),
            textureRegion.z / (float)texture->getWidth(),
            textureRegion.w / (float)texture->getHeight()
        };

    }

}
