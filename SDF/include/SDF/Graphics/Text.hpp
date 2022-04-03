/*
* Copyright (c) 2021 Adam Charvát <https://www.skulaurun.eu>
* Licensed under the MIT License,
* for details see accompanying LICENSE file or a copy at
* <https://github.com/Skulaurun/SDF/blob/v1.0.0/LICENSE>.
* SPDX-License-Identifier: MIT
*/

#pragma once

#include "Font.hpp"

// TODO: Add size and rotation?

namespace sdf {

    class Text {

    public:
        Text(const std::wstring& text, const std::shared_ptr<Font>& font = nullptr);

        void setPosition(const sdf::Vec2f& position) { this->position = position; updateTransform(); }
        void setFontSize(const float size) { this->fontSize = size; updateTransform(); }
        void setFontColor(const Vec4f& color) { this->fontColor = color; updateColor(); }

        Vec4f getColor() const { return fontColor; }

        const std::vector<Sprite>& getSprites() const { return sprites; }

    private:
        void updateColor();
        void updateTransform();

    private:
        float fontSize;
        Vec4f fontColor;
        sdf::Vec2f position;
        std::wstring text;
        std::shared_ptr<Font> font;
        std::vector<Sprite> sprites;

    };

}
