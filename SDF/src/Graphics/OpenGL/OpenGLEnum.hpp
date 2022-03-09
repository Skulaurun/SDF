/*
* Copyright (c) 2021 Adam Charvát <https://www.skulaurun.eu>
* Licensed under the MIT License,
* for details see accompanying LICENSE file or a copy at
* <https://github.com/Skulaurun/SDF/blob/v1.0.0/LICENSE>.
* SPDX-License-Identifier: MIT
*/

#pragma once

#include "OpenGL.hpp"

#include <SDF/Graphics/OpenGL/Buffer.hpp>
#include <SDF/Graphics/OpenGL/Shader.hpp>

#include <SDF/Graphics/OpenGL/VertexBuffer.hpp>

// rename this header file
// put definistions to .cpp file

namespace sdf {

	constexpr GLenum TO_NATIVE_ENUM(const BufferType& type) {
		switch (type) {
			case BufferType::VertexBuffer: return GL_ARRAY_BUFFER;
			case BufferType::IndexBuffer: return GL_ELEMENT_ARRAY_BUFFER;
			default: throw "UNSUPPORTED TYPE";
		}
	}

	constexpr GLenum TO_NATIVE_ENUM(const ShaderType& type) {
		switch (type) {
			case ShaderType::VertexShader: return GL_VERTEX_SHADER;
			case ShaderType::FragmentShader: return GL_FRAGMENT_SHADER;
			default: throw "UNSUPPORTED TYPE";
		}
	}

	constexpr GLenum TO_NATIVE_ENUM(const VertexAttributeType& type) {
		switch (type) {
			//case VertexAttributeType::Bool: return GL_BOOL;
			case VertexAttributeType::Int: return GL_UNSIGNED_INT;
			case VertexAttributeType::Float: return GL_FLOAT;
			default: throw "UNSUPPORTED TYPE";
		}
	}

	constexpr GLsizei TYPE_SIZE(const VertexAttributeType& type) {
		switch (type) {
			case VertexAttributeType::Bool: return 1;
			case VertexAttributeType::Int: return 4;
			case VertexAttributeType::Float: return 4;
			default: throw "UNSUPPORTED TYPE";
		}
	}

}
