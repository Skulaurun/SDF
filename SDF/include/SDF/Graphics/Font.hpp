/*
* Copyright (c) 2021 Adam Charvát <https://www.skulaurun.eu>
* Licensed under the MIT License,
* for details see accompanying LICENSE file or a copy at
* <https://github.com/Skulaurun/SDF/blob/v1.0.0/LICENSE>.
* SPDX-License-Identifier: MIT
*/

#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "Vector.hpp"
#include "OpenGL/Texture.hpp"

#include "Sprite.hpp"

namespace sdf {

    class Font {

    public:
        Font(const std::wstring& characters, const Vec2f& size, const std::shared_ptr<Texture>& texture);

        Sprite getSprite(const std::wstring::value_type c) const;
        Vec4f getRegion(const std::wstring::value_type c) const { return regions.at(c); }

        Vec2f getSize() const { return size; }

    private:
        Vec2f size;
        std::wstring characters;
        std::shared_ptr<Texture> texture;
        std::unordered_map<std::wstring::value_type, Vec4f> regions;

    };

}
