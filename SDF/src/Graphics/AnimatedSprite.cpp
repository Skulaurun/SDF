/*
* Copyright (c) 2021 Adam Charvát <https://www.skulaurun.eu>
* Licensed under the MIT License,
* for details see accompanying LICENSE file or a copy at
* <https://github.com/Skulaurun/SDF/blob/v1.0.0/LICENSE>.
* SPDX-License-Identifier: MIT
*/

#include <PCH.hpp>
#include <SDF/Core/Clock.hpp>
#include <SDF/Graphics/AnimatedSprite.hpp>

namespace sdf {

    AnimatedSprite::AnimatedSprite(const Sprite& sprite, const Vec2f& frameSize)
        : Sprite(sprite), frameSize(frameSize), rowCount(0), columnCount(0), animations({}) {
        updateProperties();
    }
    AnimatedSprite::AnimatedSprite(const std::shared_ptr<Texture>& texture, const Vec2f& frameSize)
        : AnimatedSprite(Sprite(texture), frameSize) {}

    void AnimatedSprite::updateProperties() {

        rowCount = std::floorf(getTexture()->getHeight() / frameSize.y);
        columnCount = std::floorf(getTexture()->getWidth() / frameSize.x);

        getTransform().setSize(frameSize);

    }

    void AnimatedSprite::setAnimation(const std::string& name, const std::size_t rowIndex, const std::size_t frameCount, const float speed) {

        if (rowIndex >= rowCount) {
            throw std::invalid_argument("Row count is outside of the texture's bounds.");
        }
        if (frameCount > columnCount) {
            throw std::invalid_argument("Frame count is outside of the texture's bounds.");
        }

        animations[name] = { rowIndex, frameCount, speed };

    }

    float deltaCounter = 0.0f;

    void AnimatedSprite::update(const float deltaTime) {

        deltaCounter += deltaTime;

        if (currentAnimation == "") {
            return;
        }

        SpriteAnimation& animation = animations[currentAnimation];
        std::size_t rowIndex = animation.rowIndex;
        float currentFrame = ((std::size_t)std::floorf(animation.speed * deltaCounter)) % animation.frameCount;

        sdf::Vec4f region = {
            currentFrame * frameSize.x,
            rowIndex * frameSize.y,
            currentFrame * frameSize.x + frameSize.x,
            rowIndex * frameSize.y + frameSize.y
        };

        setRegion(region);

    }

    float lastTime = 0.0f;

    void AnimatedSprite::update() {

        float currentTime = Clock::getNow().asMilliseconds();
        float deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        update(deltaTime);

    }

}
