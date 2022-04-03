/*
* Copyright (c) 2021 Adam Charvát <https://www.skulaurun.eu>
* Licensed under the MIT License,
* for details see accompanying LICENSE file or a copy at
* <https://github.com/Skulaurun/SDF/blob/v1.0.0/LICENSE>.
* SPDX-License-Identifier: MIT
*/

#pragma once

#include "../Core/Vector.hpp"
#include "OpenGL/Shader.hpp"
#include "OpenGL/Texture.hpp"
#include "Camera2D.hpp"
#include "Sprite.hpp"
#include "Text.hpp"
#include "Matrix.hpp"

#include <cstdint>
#include <string>
#include <stack>

namespace sdf {

    /*
        TODO: Add API info utility functions,
        e.g. OpenGL version (GL_VERSION), renderer (GL_RENDERER), vendor (GL_VENDOR)
        and GLSL version (GL_SHADING_LANGUAGE_VERSION)
    */

    class Renderer {

    public:
        static void init();

        static void clear(const Vec4f& color = Vec4f(0.0f));

        static void drawQuad(const Mat4f& transform, const Vec4f& color);
        static void drawQuad(
            const Mat4f& transform,
            const std::shared_ptr<Texture>& texture,
            const Vec4f& color = Vec4f(1.0f),
            const sdf::Vec4f* textureCoordinates = nullptr
        );

        static void drawSprite(const Sprite& sprite);
        static void drawText(const Text& text);

        static void flush();

        static void beginShader(const std::shared_ptr<Shader>& shader);
        static void endShader();

        static void beginCamera(const std::shared_ptr<Camera2D>& camera);
        static void endCamera();

        static void setViewport(const Vec2i& position, const Vec2u& size);

        struct Statistics {

            uint32_t quadCount;
            uint32_t batchCount;

            uint32_t getVertexCount() const { return quadCount * 4; }
            uint32_t getIndexCount() const { return quadCount * 6; }

            std::string asString() const {
                return "Batches: "  + std::to_string(batchCount)        + ", "
                       "Quads: "    + std::to_string(quadCount)         + ", "
                       "Vertices: " + std::to_string(getVertexCount())  + ", "
                       "Indices: "  + std::to_string(getIndexCount());
            }

        };

        /*
            The statistics are cleared automatically
            during a call to sdf::Renderer:clear()
        */
        static void resetStatistics() { statistics = { 0, 0 }; }
        static const Statistics getStatistics() { return statistics; }

    private:
        static void drawQuad(const Mat4f& transform, const Vec4f& color, const float samplerID, const sdf::Vec4f* textureCoordinates = nullptr);

    private:
        static std::stack<std::shared_ptr<Shader>> shaders;
        static std::stack<std::shared_ptr<Camera2D>> cameras;
        
        static Statistics statistics;

    };

}
