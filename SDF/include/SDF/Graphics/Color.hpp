/*
* Copyright (c) 2021 Adam Charvát <https://www.skulaurun.eu>
* Licensed under the MIT License,
* for details see accompanying LICENSE file or a copy at
* <https://github.com/Skulaurun/SDF/blob/v1.0.0/LICENSE>.
* SPDX-License-Identifier: MIT
*/

#pragma once

#include "Vector.hpp"

namespace sdf {

    class Color {

    public:
        Color(const Vec4f& color)
            : nColor(color) {}

        explicit Color(const int color)
            : Color(
                (color >> 24) & 0xff,
                (color >> 16) & 0xff,
                (color >> 8)  & 0xff,
                (color)       & 0xff
            ) {}

        explicit Color(const int r, const int g, const int b, const int a = 255)
            : Color(
                r / 255.0f,
                g / 255.0f,
                b / 255.0f,
                a / 255.0f
            ) {}

        explicit Color(const float r, const float g, const float b, const float a = 1.0f)
            : nColor(r, g, b, a) {}

        int getRed() const { return int(nColor.x * 255); }
        int getGreen() const { return int(nColor.y * 255); }
        int getBlue() const { return int(nColor.z * 255); }
        int getAlpha() const { return int(nColor.w * 255); }

        int getRGBA() const {
            int color = 0x00000000;
            color |= (getRed() << 24);
            color |= (getGreen() << 16);
            color |= (getBlue() << 8);
            color |= (getAlpha());
            return color;
        }

        operator Vec4f() const { return nColor; }

    private:
        Vec4f nColor;

    };

}
