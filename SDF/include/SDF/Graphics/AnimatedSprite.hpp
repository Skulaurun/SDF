/*
* Copyright (c) 2021 Adam Charvát <https://www.skulaurun.eu>
* Licensed under the MIT License,
* for details see accompanying LICENSE file or a copy at
* <https://github.com/Skulaurun/SDF/blob/v1.0.0/LICENSE>.
* SPDX-License-Identifier: MIT
*/

#pragma once

#include "Sprite.hpp"

namespace sdf {

    class AnimatedSprite : public Sprite {

    private:
        struct SpriteAnimation {
            std::size_t rowIndex;
            std::size_t frameCount;
            float speed;
        };

    public:
        AnimatedSprite(const Sprite& sprite, const Vec2f& frameSize);
        AnimatedSprite(const std::shared_ptr<Texture>& texture, const Vec2f& frameSize);

        void setFrameSize(const Vec2f& frameSize) { this->frameSize = frameSize; updateProperties(); }
        void setAnimation(const std::string& name, const std::size_t rowIndex, const std::size_t frameCount, const float speed = 1.0f);

        void play(const std::string& name) { currentAnimation = name; }
        void stop() { currentAnimation = ""; }

        std::string getPlaying() const { return currentAnimation; }
        bool isPlaying() const { return playing; }

        void update(const float deltaTime);
        void update();

    private:
        void updateProperties();

    private:
        bool playing;
        Vec2f frameSize;
        std::size_t rowCount;
        std::size_t columnCount;
        std::string currentAnimation;
        std::unordered_map<std::string, SpriteAnimation> animations;

    };

}
