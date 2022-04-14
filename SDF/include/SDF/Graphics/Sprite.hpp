/*
* Copyright (c) 2021 Adam Charvát <https://www.skulaurun.eu>
* Licensed under the MIT License,
* for details see accompanying LICENSE file or a copy at
* <https://github.com/Skulaurun/SDF/blob/v1.0.0/LICENSE>.
* SPDX-License-Identifier: MIT
*/

#pragma once

#include "Vector.hpp"
#include "OpenGL/Texture.hpp"
#include "Transform.hpp"

#include <memory>

namespace sdf {

    class Sprite {

    public:
        Sprite(const std::shared_ptr<Texture>& texture);

        void setColor(const Vec4f& color) { this->color = color; }
        void setTransform(const Transform& transform) { this->transform = transform; }

        void setRegion(const Vec4f& region) { this->textureRegion = region; updateRegion(); }
        void setTexture(const std::shared_ptr<Texture>& texture) { this->texture = texture; updateRegion(); }

        Vec4f getColor() const { return color; }
        Transform& getTransform() { return transform; }
        const Transform& getTransform() const { return transform; }

        Vec4f getRegion() const { return textureRegion; }
        std::shared_ptr<Texture> getTexture() const { return texture; }

        Vec4f getNormalizedRegion() const { return normalizedRegion; }


    private:
        void updateRegion();

    private:
        Vec4f color;
        Transform transform;
        Vec4f textureRegion;
        Vec4f normalizedRegion;
        std::shared_ptr<Texture> texture;

    };

}
