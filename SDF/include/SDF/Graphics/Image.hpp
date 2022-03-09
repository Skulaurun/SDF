/*
* Copyright (c) 2021 Adam Charvát <https://www.skulaurun.eu>
* Licensed under the MIT License,
* for details see accompanying LICENSE file or a copy at
* <https://github.com/Skulaurun/SDF/blob/v1.0.0/LICENSE>.
* SPDX-License-Identifier: MIT
*/

#pragma once

#include <cstdint>
#include <string>
#include <memory>
#include <filesystem>

// SDF Image Decoder
// Currently works with BMP & PNG (JPG support planned)
// There are some issues with specific PNGs tho
// TODO: Fix this later

// This is probably issue with the sdf::Texture class,
// since we tell OpenGL that our pixel data is 32-bit in color depth (BGRA)

typedef struct IWICStream IWICStream;
typedef struct IWICImagingFactory IWICImagingFactory;

namespace sdf {

    class Image {

    public:
        Image(const std::filesystem::path& path);
        Image(uint8_t* buffer, const uint32_t size);

        ~Image();

        uint8_t* getData() const { return data; }

        uint32_t getWidth() const { return width; }
        uint32_t getHeight() const { return height; }
        uint32_t getBytesPerPixel() const { return bytesPerPixel; }

    private:
        Image();

        void decodeImage(IWICStream* stream);

    private:
        uint8_t* data;

        uint32_t width;
        uint32_t height;
        uint32_t bytesPerPixel;

        static IWICImagingFactory* factory;

    };

}
