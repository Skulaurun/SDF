#pragma once

#include <SDF/Core/WinTypes.hpp>

namespace sdf {

    class Window;

    class WGLContext {

    public:
        WGLContext(const Window& window);
        ~WGLContext();

        bool makeCurrent() const;
        bool swapBuffers() const;

        static const WGLContext* getCurrentContext() { return currentContext; }

    private:
        HWND hWindow;
        HDC hDeviceContext;
        HGLRC hGLContext;

        static const WGLContext* currentContext;

    };

}
