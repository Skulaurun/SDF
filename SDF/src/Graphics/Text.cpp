/*
* Copyright (c) 2021 Adam Charvát <https://www.skulaurun.eu>
* Licensed under the MIT License,
* for details see accompanying LICENSE file or a copy at
* <https://github.com/Skulaurun/SDF/blob/v1.0.0/LICENSE>.
* SPDX-License-Identifier: MIT
*/

#include <PCH.hpp>
#include <SDF/Graphics/Text.hpp>

// TODO: Space doesn't have to be a sdf::Sprite

namespace sdf {

    Text::Text(const std::wstring& text, const std::shared_ptr<Font>& font)
        : text(text), font(font), fontColor(1.0f) {

        for (std::size_t i = 0; i < text.size(); i++) {
            sprites.push_back(font->getSprite(text[i]));
        }

        updateTransform();

    }

    void Text::updateColor() {
        for (std::size_t i = 0; i < sprites.size(); i++) {
            sprites[i].setColor(fontColor);
        }
    }

    void Text::updateTransform() {

        for (std::size_t i = 0; i < sprites.size(); i++) {

            auto& sprite = sprites[i].getTransform();
            sprite.setSize({
                { fontSize }
            });

            sprite.setPosition({
                i * sprite.getSize().x + position.x,
                position.y // TODO: Implement word wrap?
            });

        }

    }

}
