#pragma once

#include "../Core/Vector.hpp"
#include "Matrix.hpp"

#include <cstdint>

namespace sdf {

	// APIInfo

	struct Vertex {
		Vec2f position;
		Vec4f color;
		//math::Vec2f textureCoordinate;
		//float samplerID;
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

		//static void beginScene(const scene::Camera& camera);

		static void drawQuad(const Mat4f& transform, const Vec4f& color);
		static void flush();

		static void setViewport(const Vec2f& position, const Vec2f& size);

		static const void resetStatistics() { statistics = { 0, 0 }; }
		static const RendererStatistics getStatistics() { return statistics; }

	private:
		static RendererStatistics statistics;

	};

}
