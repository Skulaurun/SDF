/*
* Copyright (c) 2021 Adam Charvát <https://www.skulaurun.eu>
* Licensed under the MIT License,
* for details see accompanying LICENSE file or a copy at
* <https://github.com/Skulaurun/SDF/blob/v1.0.0/LICENSE>.
* SPDX-License-Identifier: MIT
*/

#pragma once

#include <SDF/Core/WinTypes.hpp>

#define WGL_CONTEXT_MAJOR_VERSION_ARB 0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB 0x2092
#define WGL_CONTEXT_FLAGS_ARB 0x2094

using WGLGetExtensionsStringARBPtr = const char* (__stdcall*)(HDC hDC);
using WGLCreateContextAttribsARBPtr = HGLRC(__stdcall*)(HDC hDC, HGLRC hShareContext, const int* attribList);

extern WGLGetExtensionsStringARBPtr wglGetExtensionsStringARB;
extern WGLCreateContextAttribsARBPtr wglCreateContextAttribsARB;

namespace sdf {

    bool loadWGLFunctions();

}
