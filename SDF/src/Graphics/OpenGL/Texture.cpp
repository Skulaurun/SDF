/*
* Copyright (c) 2021 Adam Charvát <https://www.skulaurun.eu>
* Licensed under the MIT License,
* for details see accompanying LICENSE file or a copy at
* <https://github.com/Skulaurun/SDF/blob/v1.0.0/LICENSE>.
* SPDX-License-Identifier: MIT
*/

#include <PCH.hpp>

#include <SDF/Graphics/OpenGL/Texture.hpp>

#include "OpenGL.hpp"

namespace sdf {

    static constexpr GLenum getOpenGLEnum(const TextureWrap wrap) {
        switch (wrap) {
            case TextureWrap::Repeat: return GL_REPEAT;
            case TextureWrap::MirroredRepeat: return GL_MIRRORED_REPEAT;
            case TextureWrap::ClampToEdge: return GL_CLAMP_TO_EDGE;
            case TextureWrap::ClampToBorder: return GL_CLAMP_TO_BORDER;
            default: throw "UNSUPPORTED TYPE";
        }
    }

    static constexpr GLenum getOpenGLEnum(const TextureFilter filter) {
        switch (filter) {
            case TextureFilter::Linear: return GL_LINEAR;
            case TextureFilter::Nearest: return GL_NEAREST;
            default: throw "UNSUPPORTED TYPE";
        }
    }

    Texture::Texture(const uint8_t* data, const uint32_t width, const uint32_t height, const uint32_t channels, const TextureProperties& properties)
        : width(width), height(height), channels(channels) {

        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);

        setProperties(properties);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, data);
        glBindTexture(GL_TEXTURE_2D, 0);

    }
	Texture::Texture(const Image& image, const TextureProperties& properties)
        : Texture(
            image.getData(),
            image.getWidth(),
            image.getHeight(),
            image.getBytesPerPixel(),
            properties
        ) {}
	Texture::~Texture() {
        glDeleteTextures(1, contextId());
	}

    void Texture::setProperties(const TextureProperties& properties) {

        bind();

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, getOpenGLEnum(properties.wrapS));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, getOpenGLEnum(properties.wrapT));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, getOpenGLEnum(properties.minFilter));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, getOpenGLEnum(properties.magFilter));

    }

    void Texture::bind() const {
        glBindTexture(GL_TEXTURE_2D, id);
    }
	void Texture::unbind() const {
		glBindTexture(GL_TEXTURE_2D, 0);
	}

    void Texture::bind(const uint32_t slot) const {
        glActiveTexture(GL_TEXTURE0 + slot);
        bind();
    }

}
