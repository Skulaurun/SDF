/*
* Copyright (c) 2021 Adam Charvát <https://www.skulaurun.eu>
* Licensed under the MIT License,
* for details see accompanying LICENSE file or a copy at
* <https://github.com/Skulaurun/SDF/blob/v1.0.0/LICENSE>.
* SPDX-License-Identifier: MIT
*/

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
