/*
* Copyright (c) 2021 Adam Charvát <https://www.skulaurun.eu>
* Licensed under the MIT License,
* for details see accompanying LICENSE file or a copy at
* <https://github.com/Skulaurun/SDF/blob/v1.0.0/LICENSE>.
* SPDX-License-Identifier: MIT
*/

#pragma once

#include <SDF/Core/WinTypes.hpp>

constexpr auto WGL_CONTEXT_MAJOR_VERSION_ARB = 0x2091;
constexpr auto WGL_CONTEXT_MINOR_VERSION_ARB = 0x2092;

constexpr auto WGL_CONTEXT_PROFILE_MASK_ARB = 0x9126;
constexpr auto WGL_CONTEXT_CORE_PROFILE_BIT_ARB = 0x00000001;
constexpr auto WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB = 0x00000002;

constexpr auto WGL_CONTEXT_FLAGS_ARB = 0x2094;
constexpr auto WGL_CONTEXT_DEBUG_BIT_ARB = 0x0001;
constexpr auto WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB = 0x0002;

constexpr auto WGL_DRAW_TO_WINDOW_ARB = 0x2001;
constexpr auto WGL_SUPPORT_OPENGL_ARB = 0x2010;
constexpr auto WGL_DOUBLE_BUFFER_ARB = 0x2011;

constexpr auto WGL_ACCELERATION_ARB = 0x2003;
constexpr auto WGL_NO_ACCELERATION_ARB = 0x2025;
constexpr auto WGL_GENERIC_ACCELERATION_ARB = 0x2026;
constexpr auto WGL_FULL_ACCELERATION_ARB = 0x2027;

constexpr auto WGL_PIXEL_TYPE_ARB = 0x2013;
constexpr auto WGL_TYPE_RGBA_ARB = 0x202B;
constexpr auto WGL_TYPE_COLORINDEX_ARB = 0x202C;

constexpr auto WGL_COLOR_BITS_ARB = 0x2014;
constexpr auto WGL_DEPTH_BITS_ARB = 0x2022;
constexpr auto WGL_STENCIL_BITS_ARB = 0x2023;

using WGLGetExtensionsStringARBPtr = const char* (__stdcall*)(HDC hDC);
using WGLCreateContextAttribsARBPtr = HGLRC (__stdcall*)(HDC hDC, HGLRC hShareContext, const int* attribList);
using WGLChoosePixelFormatARBPtr = BOOL (__stdcall*)(HDC hDC, const int* piAttribIList, const FLOAT* pfAttribFList, UINT nMaxFormats, int* piFormats, UINT* nNumFormats);

extern WGLGetExtensionsStringARBPtr wglGetExtensionsStringARB;
extern WGLCreateContextAttribsARBPtr wglCreateContextAttribsARB;
extern WGLChoosePixelFormatARBPtr wglChoosePixelFormatARB;

namespace sdf {

    bool isWGLExtensionSupported(HDC hDC, const char* name);
    void loadWGLFunctions(void* (*getWGLFunction)(const char* name));

}
