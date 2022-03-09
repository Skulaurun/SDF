/*
* Copyright (c) 2021 Adam Charvát <https://www.skulaurun.eu>
* Licensed under the MIT License,
* for details see accompanying LICENSE file or a copy at
* <https://github.com/Skulaurun/SDF/blob/v1.0.0/LICENSE>.
* SPDX-License-Identifier: MIT
*/

#include <PCH.hpp>

#include <SDF/Graphics/OpenGL/Buffer.hpp>

#include "OpenGL.hpp"
#include "OpenGLEnum.hpp"

namespace sdf {

	template<typename TData, BufferType TBuffer>
	Buffer<TData, TBuffer>::Buffer(const uint32_t size) : Buffer<TData, TBuffer>(0, size) {}

	template<typename TData, BufferType TBuffer>
	Buffer<TData, TBuffer>::Buffer(const TData* data, const uint32_t size) {

		glGenBuffers(1, &id);
		glBindBuffer(TO_NATIVE_ENUM(TBuffer), id);
		glBufferData(TO_NATIVE_ENUM(TBuffer), size, data, data == 0 ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);

		glBindBuffer(TO_NATIVE_ENUM(TBuffer), 0);

	}

	template<typename TData, BufferType TBuffer>
	Buffer<TData, TBuffer>::~Buffer() {
		glDeleteBuffers(1, &id);
	}

	template<typename TData, BufferType TBuffer>
	void Buffer<TData, TBuffer>::bind() const {
		glBindBuffer(TO_NATIVE_ENUM(TBuffer), id);
	}

	template<typename TData, BufferType TBuffer>
	void Buffer<TData, TBuffer>::unbind() const {
		glBindBuffer(TO_NATIVE_ENUM(TBuffer), 0);
	}

	template<typename TData, BufferType TBuffer>
	void Buffer<TData, TBuffer>::update(const TData* data, const uint32_t offset, const uint32_t size) const {
		glBufferSubData(TO_NATIVE_ENUM(TBuffer), offset, size, data);
	}

	template class Buffer<float, BufferType::VertexBuffer>;
	template class Buffer<uint32_t, BufferType::IndexBuffer>;

}
