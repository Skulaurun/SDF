#include "WGLContext.hpp"
#include "Window.hpp"

#include <windows.h>

#pragma comment (lib, "opengl32.lib")

namespace sdf {

    const WGLContext* WGLContext::currentContext = nullptr;

    WGLContext::WGLContext(const Window& window) {

        // Check if handle valid?
        hWindow = window.getNativeWindow();
        hDeviceContext = GetDC(hWindow);

        // From OpenGL wiki
        PIXELFORMATDESCRIPTOR descriptor = {
            sizeof(PIXELFORMATDESCRIPTOR),
            1,
            PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    // Flags
            PFD_TYPE_RGBA,        // The kind of framebuffer. RGBA or palette.
            32,                   // Colordepth of the framebuffer.
            0, 0, 0, 0, 0, 0,
            0,
            0,
            0,
            0, 0, 0, 0,
            24,                   // Number of bits for the depthbuffer
            8,                    // Number of bits for the stencilbuffer
            0,                    // Number of Aux buffers in the framebuffer.
            PFD_MAIN_PLANE,
            0,
            0, 0, 0
        };

        int pixelFormat = ChoosePixelFormat(hDeviceContext, &descriptor);
        SetPixelFormat(hDeviceContext, pixelFormat, &descriptor);

        hGLContext = wglCreateContext(hDeviceContext);
        if (hGLContext == NULL) { // Context creation failed
            // Error
        }

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
