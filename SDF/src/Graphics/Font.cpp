/*
* Copyright (c) 2021 Adam Charvát <https://www.skulaurun.eu>
* Licensed under the MIT License,
* for details see accompanying LICENSE file or a copy at
* <https://github.com/Skulaurun/SDF/blob/v1.0.0/LICENSE>.
* SPDX-License-Identifier: MIT
*/

#include <PCH.hpp>
#include <SDF/Graphics/Font.hpp>

namespace sdf {

    Font::Font(const std::wstring& characters, const Vec2f& size, const std::shared_ptr<Texture>& texture)
        : characters(characters), size(size), texture(texture) {
    
        for (std::size_t i = 0; i < characters.size(); i++) {

            std::size_t x = i % (texture->getWidth() / (std::size_t)size.x);
            std::size_t y = i / (texture->getWidth() / (std::size_t)size.x);

            regions[characters[i]] = {
                x * size.x,
                y * size.y,
                x * size.x + size.x,
                y * size.y + size.y
            };

        }

    }

    Sprite Font::getSprite(const std::wstring::value_type c) const {
        Sprite sprite(texture);
        sprite.setRegion(getRegion(c));
        auto& transform = sprite.getTransform();
        transform.setPosition({ 0.0f });
        transform.setSize(size);
        return sprite;
    }

}
