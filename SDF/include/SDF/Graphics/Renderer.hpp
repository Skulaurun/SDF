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
#include "Matrix.hpp"

#include <cstdint>
#include <stack>

namespace sdf {

	// APIInfo

	struct Vertex {
		Vec2f position;
		Vec4f color;
		Vec2f textureCoordinate;
		float samplerID;
	};

	struct RendererStatistics {

		uint32_t batchCount;
		uint32_t quadCount;

		uint32_t getVertexCount() const { return quadCount * 4; }
		uint32_t getIndexCount() const { return quadCount * 6; }

	};

	class Renderer {

	public:
		static bool init();

		static void clear(const Vec4f& color = Vec4f(0.0f));

		static void drawQuad(const Mat4f& transform, const Vec4f& color);
		static void drawQuad(const Mat4f& transform, const std::shared_ptr<Texture>& texture, const Vec4f& color = Vec4f(1.0f));

		static void flush();

		static void beginShader(const std::shared_ptr<Shader>& shader);
		static void endShader();

		static void beginCamera(const std::shared_ptr<Camera2D>& camera);
		static void endCamera();

		static void setViewport(const Vec2i& position, const Vec2u& size);

		static const void resetStatistics() { statistics = { 0, 0 }; }
		static const RendererStatistics getStatistics() { return statistics; }

	private:
		static void drawQuad(const Mat4f& transform, const Vec4f& color, const float samplerID);

	private:
		static std::stack<std::shared_ptr<Shader>> shaders;
		static std::stack<std::shared_ptr<Camera2D>> cameras;
		
		static RendererStatistics statistics;

	};

}
