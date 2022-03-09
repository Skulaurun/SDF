/*
* Copyright (c) 2021 Adam Charvát <https://www.skulaurun.eu>
* Licensed under the MIT License,
* for details see accompanying LICENSE file or a copy at
* <https://github.com/Skulaurun/SDF/blob/v1.0.0/LICENSE>.
* SPDX-License-Identifier: MIT
*/

#include <PCH.hpp>

#include <SDF/Graphics/OpenGL/VertexArray.hpp>

#include "OpenGL.hpp"

namespace sdf {

	VertexArray::VertexArray() : vertexBufferIndex(0) {
		glGenVertexArrays(1, &id);
	}

	VertexArray::~VertexArray() {
		glDeleteVertexArrays(1, &id);
	}

	void VertexArray::bind() const {
		glBindVertexArray(id);
	}

	void VertexArray::unbind() const {
		glBindVertexArray(0);
	}

	void VertexArray::setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) {

		bind();
		indexBuffer->bind();

		this->indexBuffer = indexBuffer;

	}

	void VertexArray::addVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) {

		bind();
		vertexBuffer->enableLayout(vertexBufferIndex);

		vertexBuffers.push_back(vertexBuffer);

	}

}
