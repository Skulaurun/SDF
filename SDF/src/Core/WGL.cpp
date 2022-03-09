/*
* Copyright (c) 2021 Adam Charvát <https://www.skulaurun.eu>
* Licensed under the MIT License,
* for details see accompanying LICENSE file or a copy at
* <https://github.com/Skulaurun/SDF/blob/v1.0.0/LICENSE>.
* SPDX-License-Identifier: MIT
*/

#include "WGL.hpp"

WGLGetExtensionsStringARBPtr wglGetExtensionsStringARB = nullptr;
WGLCreateContextAttribsARBPtr wglCreateContextAttribsARB = nullptr;

namespace sdf {

    bool loadWGLFunctions() {

        //wglGetExtensionsStringARB = (WGLGetExtensionsStringARBPtr)getGLFunction("wglGetExtensionsStringARB");
        //wglCreateContextAttribsARB = (WGLCreateContextAttribsARBPtr)getGLFunction("wglCreateContextAttribsARB");

        return true;

    }

}
