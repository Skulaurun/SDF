#pragma once

#include <cstdint>
#include <string>

#include "../Image.hpp"
#include "../RendererObject.hpp"

namespace sdf {

	enum class TextureWrap : uint16_t {
		Repeat, MirroredRepeat,
		ClampToEdge, ClampToBorder
	};

	enum class TextureFilter : uint16_t {
		Nearest, Linear
	};

	constexpr TextureWrap defaultWrapS = TextureWrap::Repeat;
	constexpr TextureWrap defaultWrapT = TextureWrap::Repeat;

	constexpr TextureFilter defaultMinFilter = TextureFilter::Nearest;
	constexpr TextureFilter defaultMagFilter = TextureFilter::Nearest;

	struct TextureProperties {

		TextureWrap wrapS;
		TextureWrap wrapT;

		TextureFilter minFilter;
		TextureFilter magFilter;

		TextureProperties()
			: wrapS(defaultWrapS), wrapT(defaultWrapT), minFilter(defaultMinFilter), magFilter(defaultMagFilter) {}

		TextureProperties(const TextureWrap wrapS, const TextureWrap wrapT)
			: wrapS(wrapS), wrapT(wrapT), minFilter(defaultMinFilter), magFilter(defaultMagFilter) {}

		TextureProperties(const TextureFilter minFilter, const TextureFilter magFilter)
			: minFilter(minFilter), magFilter(magFilter), wrapS(defaultWrapS), wrapT(defaultWrapT) {}

		TextureProperties(const TextureWrap wrapS, const TextureWrap wrapT, const TextureFilter minFilter, const TextureFilter magFilter)
			: wrapS(wrapS), wrapT(wrapT), minFilter(minFilter), magFilter(magFilter) {}

	};

	class Texture : public RendererObject {

	public:
		Texture(const uint8_t* data, const uint32_t width, const uint32_t height, const uint32_t channels = 4, const TextureProperties& = TextureProperties());
		Texture(const Image& image, const TextureProperties& properties = TextureProperties());
		~Texture();

		void setProperties(const TextureProperties& properties);

		void bind() const override;
		void unbind() const override;

		uint32_t getWidth() const { return width; }
		uint32_t getHeight() const { return height; }
		uint32_t getChannels() const { return channels; }

		void bind(const uint32_t slot) const;

	private:
		uint32_t channels, width, height;

	};

}
