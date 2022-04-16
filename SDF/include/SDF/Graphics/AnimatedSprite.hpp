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
            float fps;
        };

    public:
        AnimatedSprite(const Sprite& sprite, const Vec2f& frameSize);
        AnimatedSprite(const std::shared_ptr<Texture>& texture, const Vec2f& frameSize);

        void setFrameSize(const Vec2f& frameSize) { this->frameSize = frameSize; updateProperties(); }
        void setAnimation(const std::size_t rowIndex, const std::string& name, const float fps = 4.0f, std::size_t frameCount = 0);

        void play(const std::string& name);
        void playOnce(const std::string& name);

        void stop() { currentAnimation = ""; isPlaying = false; }

        std::string getCurrentAnimation() const { return currentAnimation; }

        void update(const float deltaTime);
        void update();

    private:
        void updateProperties();

    private:
        Vec2f frameSize;
        std::size_t rowCount;
        std::size_t columnCount;

        bool isOnce;
        bool isPlaying;
        float lastFrame;
        float deltaCounter;
        std::size_t frameCounter;

        std::string currentAnimation;
        std::unordered_map<std::string, SpriteAnimation> animations;

    };

}
