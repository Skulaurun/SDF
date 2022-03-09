/*
* Copyright (c) 2021 Adam Charvát <https://www.skulaurun.eu>
* Licensed under the MIT License,
* for details see accompanying LICENSE file or a copy at
* <https://github.com/Skulaurun/SDF/blob/v1.0.0/LICENSE>.
* SPDX-License-Identifier: MIT
*/

#include <PCH.hpp>

#include "SDF/Graphics/Image.hpp"

namespace sdf {

    IWICImagingFactory* Image::factory = nullptr;

    Image::Image() : data(nullptr), width(0), height(0), bytesPerPixel(0) {

        class ImageFactory {

        public:
            ImageFactory(IWICImagingFactory** factory) {

                HRESULT hResult = S_OK;
                hResult = CoInitialize(0);

                hResult = CoCreateInstance(
                    CLSID_WICImagingFactory,
                    NULL,
                    CLSCTX_INPROC_SERVER,
                    IID_PPV_ARGS(factory)
                );

            }

            ~ImageFactory() {
                factory->Release();
                CoUninitialize();
            }

        };

        static ImageFactory staticFactory(&factory);

    }
    Image::~Image() {
        free(data);
    }

    Image::Image(uint8_t* buffer, const uint32_t size) : Image() {

        IWICStream* stream = NULL;
        HRESULT hResult = factory->CreateStream(&stream);

        stream->InitializeFromMemory(buffer, size);
        decodeImage(stream);
        stream->Release();

    }

    Image::Image(const std::filesystem::path& path) : Image() {

        IWICStream* stream = NULL;
        HRESULT hResult = factory->CreateStream(&stream);

        stream->InitializeFromFilename(path.c_str(), GENERIC_READ);
        decodeImage(stream);
        stream->Release();

    }

    // TODO: Check HRESULTs and throw exceptions (comdef.h?)
    void Image::decodeImage(IWICStream* stream) {

        HRESULT hResult = S_OK;

        IWICBitmapDecoder* decoder = NULL;
        hResult = factory->CreateDecoderFromStream(
            stream,
            NULL,
            WICDecodeMetadataCacheOnDemand,
            &decoder
        );

        UINT frameCount = 0;
        hResult = decoder->GetFrameCount(&frameCount);

        IWICBitmapFrameDecode* decoderFrame = NULL;
        hResult = decoder->GetFrame(0, &decoderFrame);

        hResult = decoderFrame->GetSize((UINT*)&width, (UINT*)&height);

        WICRect rect = { 0, 0, (INT)width, (INT)height };

        WICPixelFormatGUID pixelFormatGUID;
        hResult = decoderFrame->GetPixelFormat(&pixelFormatGUID);

        IWICComponentInfo* componentInfo = NULL;
        IWICPixelFormatInfo* pixelFormatInfo = NULL;
        hResult = factory->CreateComponentInfo(pixelFormatGUID, &componentInfo);
        hResult = componentInfo->QueryInterface(__uuidof(IWICPixelFormatInfo), (void**)&pixelFormatInfo);

        hResult = pixelFormatInfo->GetBitsPerPixel(&bytesPerPixel);
        bytesPerPixel /= 8;

        UINT stride = bytesPerPixel * width;
        UINT bufferSize = stride * height;

        BYTE* buffer = (BYTE*)malloc(bufferSize);
        if (buffer == nullptr) {
            throw std::bad_alloc();
        }

        hResult = decoderFrame->CopyPixels(&rect, stride, bufferSize, buffer);
        if (SUCCEEDED(hResult)) {
            data = (uint8_t*)buffer;
        } else {
            free(buffer);
        }

        decoderFrame->Release();
        pixelFormatInfo->Release();
        componentInfo->Release();

    }

}
