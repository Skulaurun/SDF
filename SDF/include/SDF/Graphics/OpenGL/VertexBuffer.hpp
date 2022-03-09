/*
* Copyright (c) 2021 Adam Charvát <https://www.skulaurun.eu>
* Licensed under the MIT License,
* for details see accompanying LICENSE file or a copy at
* <https://github.com/Skulaurun/SDF/blob/v1.0.0/LICENSE>.
* SPDX-License-Identifier: MIT
*/

#pragma once

#include "Buffer.hpp"

#include <vector>

namespace sdf {

	enum class VertexAttributeType : uint8_t {
		Int, Float, Bool
	};

	struct VertexBufferAttribute {

		VertexAttributeType type;
		uint32_t count;
		bool normalized;

		uint32_t size;
		uint32_t stride;
		uint32_t offset;

		VertexBufferAttribute(const VertexAttributeType type, const uint32_t count, const bool normalized = false)
			: type(type), count(count), normalized(normalized), size(0), stride(0), offset(0) {}

	};

	using VertexBufferTemplate = Buffer<float, BufferType::VertexBuffer>;

	class VertexBuffer : public VertexBufferTemplate {

	public:
		using VertexBufferTemplate::Buffer;

		void setLayout(const std::vector<VertexBufferAttribute>& layout);
		const std::vector<VertexBufferAttribute>& getLayout() const { return attributeLayout; }

		void enableLayout(uint32_t& attributeOffset) const;
		//static uint32_t enableLayouts(const std::vector<const VertexBuffer&>& vertexBuffers, const uint32_t attributeOffset = 0);

	private:
		uint32_t attributeStride;
		std::vector<VertexBufferAttribute> attributeLayout;

	};

}
