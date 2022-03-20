/*
* Copyright (c) 2021 Adam Charvát <https://www.skulaurun.eu>
* Licensed under the MIT License,
* for details see accompanying LICENSE file or a copy at
* <https://github.com/Skulaurun/SDF/blob/v1.0.0/LICENSE>.
* SPDX-License-Identifier: MIT
*/

#include <PCH.hpp>
#include "WGL.hpp"

#define LOAD_WGL_FUNCTION(type, function) function = (type)getWGLFunction(#function)

WGLGetExtensionsStringARBPtr wglGetExtensionsStringARB = nullptr;
WGLCreateContextAttribsARBPtr wglCreateContextAttribsARB = nullptr;
WGLChoosePixelFormatARBPtr wglChoosePixelFormatARB = nullptr;

namespace sdf {

    bool isWGLExtensionSupported(HDC hDC, const char* name) {
        static const char* extensions = wglGetExtensionsStringARB(hDC);
        return strstr(extensions, name) != NULL;
    }

    void loadWGLFunctions(void* (*getWGLFunction)(const char* name)) {

        LOAD_WGL_FUNCTION(WGLGetExtensionsStringARBPtr, wglGetExtensionsStringARB);
        LOAD_WGL_FUNCTION(WGLCreateContextAttribsARBPtr, wglCreateContextAttribsARB);
        LOAD_WGL_FUNCTION(WGLChoosePixelFormatARBPtr, wglChoosePixelFormatARB);

    }

}
