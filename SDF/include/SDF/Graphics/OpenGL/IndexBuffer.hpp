#pragma once

#include "Buffer.hpp"

#include <cstdint>

namespace sdf {

	using IndexBufferTemplate = Buffer<uint32_t, BufferType::IndexBuffer>;

	class IndexBuffer : public IndexBufferTemplate {

	public:
		using IndexBufferTemplate::Buffer;

	};

}
