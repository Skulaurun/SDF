/*
* Copyright (c) 2021 Adam Charvát <https://www.skulaurun.eu>
* Licensed under the MIT License,
* for details see accompanying LICENSE file or a copy at
* <https://github.com/Skulaurun/SDF/blob/v1.0.0/LICENSE>.
* SPDX-License-Identifier: MIT
*/

#include <PCH.hpp>
#include <SDF/Graphics/RendererObject.hpp>

#include "Core/WGLContext.hpp"

namespace sdf {

    RendererObject::RendererObject(uint32_t id)
        : id(id), context(WGLContext::getCurrentContext()) {}

    RendererObject::RendererObject() : RendererObject(0) {}

    bool RendererObject::isSameContext() {
        return context == WGLContext::getCurrentContext();
    }

    uint32_t* RendererObject::contextId() {

        static uint32_t _dummy = {};
        _dummy = 0xffffffff;

        if (isSameContext()) {
            return &id;
        }

        return &_dummy;

    }

}
