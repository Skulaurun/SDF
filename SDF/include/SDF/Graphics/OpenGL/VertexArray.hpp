#pragma once

#include "../RendererObject.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"

#include <cstdint>
#include <memory>

namespace sdf {

	class VertexArray : public RendererObject {

	public:
		VertexArray();
		virtual ~VertexArray();

		void bind() const override;
		void unbind() const override;

		void setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer);
		void addVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer);

		const std::shared_ptr<IndexBuffer>& getIndexBuffer() const { return indexBuffer; }
		const std::vector<std::shared_ptr<VertexBuffer>>& getVertexBuffers() const { return vertexBuffers; }

	private:
		uint32_t vertexBufferIndex;

		std::shared_ptr<IndexBuffer> indexBuffer;
		std::vector<std::shared_ptr<VertexBuffer>> vertexBuffers;

	};

}
