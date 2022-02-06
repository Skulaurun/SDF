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

	Texture::Texture(const Image& image, const TextureProperties& properties) : channels(0), width(0), height(0) {

        width = image.getWidth();
        height = image.getHeight();
        channels = image.getBytesPerPixel();

		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D, id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, getOpenGLEnum(properties.wrapS));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, getOpenGLEnum(properties.wrapT));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, getOpenGLEnum(properties.minFilter));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, getOpenGLEnum(properties.magFilter));

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, image.getData());
		glBindTexture(GL_TEXTURE_2D, 0);

	}
	Texture::~Texture() {
		glDeleteTextures(1, &id);
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
