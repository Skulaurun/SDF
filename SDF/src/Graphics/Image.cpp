/*
* Copyright (c) 2021 Adam Charvát <https://www.skulaurun.eu>
* Licensed under the MIT License,
* for details see accompanying LICENSE file or a copy at
* <https://github.com/Skulaurun/SDF/blob/v1.0.0/LICENSE>.
* SPDX-License-Identifier: MIT
*/

#include <PCH.hpp>
#include <SDF/Graphics/Image.hpp>

#include "Core/WinError.hpp"

namespace sdf {

    IWICImagingFactory* Image::factory = nullptr;

    Image::Image() : data(nullptr), width(0), height(0), bytesPerPixel(0) {

        class ImageFactory {

        public:
            ImageFactory(IWICImagingFactory** factory) {

                COM_CALL(CoInitialize(0));

                COM_CALL(CoCreateInstance(
                    CLSID_WICImagingFactory,
                    NULL,
                    CLSCTX_INPROC_SERVER,
                    IID_PPV_ARGS(factory)
                ));

            }

            ~ImageFactory() {
                factory->Release();
                CoUninitialize();
            }

        };

        // THIS IS OK, IT WILL GET INITIALIZED
        // ON THE FIRST CONSTRUCTOR CALL
        static ImageFactory staticFactory(&factory);

    }
    Image::~Image() {
        free(data);
    }

    Image::Image(uint8_t* buffer, const uint32_t size) : Image() {

        IWICStream* stream = NULL;
        COM_CALL(factory->CreateStream(&stream));

        COM_CALL(stream->InitializeFromMemory(buffer, size));
        decodeImage(stream);
        stream->Release();

    }

    Image::Image(const std::filesystem::path& path) : Image() {

        IWICStream* stream = NULL;
        COM_CALL(factory->CreateStream(&stream));

        COM_CALL(stream->InitializeFromFilename(path.c_str(), GENERIC_READ));
        decodeImage(stream);
        stream->Release();

    }

    void Image::decodeImage(IWICStream* stream) {

        IWICBitmapDecoder* decoder = NULL;
        COM_CALL(factory->CreateDecoderFromStream(
            stream,
            NULL,
            WICDecodeMetadataCacheOnDemand,
            &decoder
        ));

        UINT frameCount = 0;
        COM_CALL(decoder->GetFrameCount(&frameCount));

        IWICBitmapFrameDecode* decoderFrame = NULL;
        COM_CALL(decoder->GetFrame(0, &decoderFrame));

        COM_CALL(decoderFrame->GetSize((UINT*)&width, (UINT*)&height));

        WICRect rect = { 0, 0, (INT)width, (INT)height };

        WICPixelFormatGUID pixelFormatGUID;
        COM_CALL(decoderFrame->GetPixelFormat(&pixelFormatGUID));

        IWICComponentInfo* componentInfo = NULL;
        IWICPixelFormatInfo* pixelFormatInfo = NULL;
        COM_CALL(factory->CreateComponentInfo(pixelFormatGUID, &componentInfo));
        COM_CALL(componentInfo->QueryInterface(__uuidof(IWICPixelFormatInfo), (void**)&pixelFormatInfo));

        COM_CALL(pixelFormatInfo->GetBitsPerPixel(&bytesPerPixel));
        bytesPerPixel /= 8;

        UINT stride = bytesPerPixel * width;
        UINT bufferSize = stride * height;

        BYTE* buffer = (BYTE*)malloc(bufferSize);
        if (buffer == nullptr) {
            throw std::bad_alloc();
        }

        HRESULT hResult = decoderFrame->CopyPixels(&rect, stride, bufferSize, buffer);
        if (SUCCEEDED(hResult)) {
            data = (uint8_t*)buffer;
        } else {
            free(buffer);
            COM_CALL(hResult);
        }

        decoderFrame->Release();
        pixelFormatInfo->Release();
        componentInfo->Release();

    }

}
