/*
* Copyright (c) 2021 Adam Charvát <https://www.skulaurun.eu>
* Licensed under the MIT License,
* for details see accompanying LICENSE file or a copy at
* <https://github.com/Skulaurun/SDF/blob/v1.0.0/LICENSE>.
* SPDX-License-Identifier: MIT
*/

#include <PCH.hpp>

#include <SDF/Core/Exception.hpp>
#include <SDF/Core/Window.hpp>
#include <SDF/Graphics/Renderer.hpp>

#include "WinError.hpp"
#include "Graphics/OpenGL/OpenGL.hpp"

#include "WGL.hpp"
#include "WGLContext.hpp"

#pragma comment (lib, "opengl32.lib")

#define SYS_THROW() { \
    WinError error = WinError::getLastError(); \
    throw SystemException(error.message, error.code); \
}

#define SYS_ASSERT(x) \
    if (!(x)) { \
        SYS_THROW(); \
    }

namespace sdf {

    const WGLContext* WGLContext::currentContext = nullptr;

    WGLContext::WGLContext(const Window& window) {

        hWindow = window.getNativeWindow();
        hDeviceContext = GetDC(hWindow);

        PIXELFORMATDESCRIPTOR pfd = {};
        pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
        pfd.nVersion = 1;
        pfd.iLayerType = PFD_MAIN_PLANE;
        pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
        pfd.iPixelType = PFD_TYPE_RGBA;
        pfd.cColorBits = 32;
        pfd.cDepthBits = 24;
        pfd.cStencilBits = 8;
        
        int pixelFormat = ChoosePixelFormat(hDeviceContext, &pfd);
        SYS_ASSERT(SetPixelFormat(hDeviceContext, pixelFormat, &pfd) == TRUE);

        hGLContext = wglCreateContext(hDeviceContext);
        SYS_ASSERT(hGLContext != NULL);

        SYS_ASSERT(makeCurrent());
        SYS_ASSERT(loadGLFunctions());

        Renderer::init();

        /* TODO: Create modern OpenGL context */

        /*
            From Microsoft documentation: https://docs.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-setpixelformat
            Setting the pixel format of a window more than once can lead to significant complications for the Window Manager and for multithread applications,
            so it is not allowed. An application can only set the pixel format of a window one time. Once a window's pixel format is set, it cannot be changed.
        */

        /*if (!isWGLExtensionSupported(hDeviceContext, "WGL_ARB_create_context")) {
            throw Exception("An OpenGL extension 'WGL_ARB_create_context' is not supported on this system!");
        }

        if (!isWGLExtensionSupported(hDeviceContext, "WGL_ARB_pixel_format")) {
            throw Exception("An OpenGL extension 'WGL_ARB_pixel_format' is not supported on this system!");
        }

        int pixelFormatAttributes[] = {
            WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
            WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
            WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
            WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
            WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
            WGL_COLOR_BITS_ARB, 32,
            WGL_DEPTH_BITS_ARB, 24,
            WGL_STENCIL_BITS_ARB, 8
        };

        UINT formats;
        SYS_ASSERT(wglChoosePixelFormatARB(hDeviceContext, pixelFormatAttributes, 0, 1, &pixelFormat, &formats) == TRUE);

        DescribePixelFormat(hDeviceContext, pixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pfd);
        SYS_ASSERT(SetPixelFormat(hDeviceContext, pixelFormat, &pfd) == TRUE);
        
        int contextAttributes[] = {
            WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
            WGL_CONTEXT_MINOR_VERSION_ARB, 1,
            WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
            0
        };
        HGLRC hNewContext = wglCreateContextAttribsARB(hDeviceContext, 0, contextAttributes);
        SYS_ASSERT(hNewContext != NULL);

        wglMakeCurrent(NULL, NULL);
        wglDeleteContext(hGLContext);

        hGLContext = hNewContext;
        SYS_ASSERT(wglMakeCurrent(hDeviceContext, hGLContext));*/

    }

    bool WGLContext::makeCurrent() const {

        if (wglMakeCurrent(hDeviceContext, hGLContext) == TRUE) {
            currentContext = this;
            return true;
        }

        return false;

    }

    bool WGLContext::swapBuffers() const {
        return SwapBuffers(hDeviceContext) == TRUE;
    }

    WGLContext::~WGLContext() {

        if (currentContext == this) {
            if (wglMakeCurrent(hDeviceContext, NULL) == TRUE) {
                currentContext = nullptr;
            }
        }

        ReleaseDC(hWindow, hDeviceContext);
        wglDeleteContext(hGLContext);

    }

}
