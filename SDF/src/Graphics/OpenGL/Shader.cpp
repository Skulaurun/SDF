/*
* Copyright (c) 2021 Adam Charvát <https://www.skulaurun.eu>
* Licensed under the MIT License,
* for details see accompanying LICENSE file or a copy at
* <https://github.com/Skulaurun/SDF/blob/v1.0.0/LICENSE>.
* SPDX-License-Identifier: MIT
*/

#include <PCH.hpp>
#include <SDF/Graphics/OpenGL/Shader.hpp>

#include "OpenGL.hpp"

namespace sdf {

	constexpr GLenum getEnum(const ShaderType& type) {
		switch (type) {
			case ShaderType::VertexShader: return GL_VERTEX_SHADER;
			case ShaderType::FragmentShader: return GL_FRAGMENT_SHADER;
			default: throw "UNSUPPORTED TYPE";
		}
	}

	Shader::Shader(const std::vector<ShaderSource>& sources) {

		id = glCreateProgram();

		std::vector<uint32_t> shaders;
		for (const auto& source : sources) {

			uint32_t shader = glCreateShader(getEnum(source.type));
			shaders.push_back(shader);

			const char* data = source.data.c_str();
			glShaderSource(shader, 1, &data, NULL);

			compileShader(shader, source.type);
			glAttachShader(id, shader);

		}

		glLinkProgram(id); // Check link status?
		for (const auto& shader : shaders) glDeleteShader(shader);

	}
	Shader::~Shader() {
		glDeleteProgram(*contextId());
	}

	void Shader::compileShader(const uint32_t shader, const ShaderType type) const {

		int32_t result;
		glCompileShader(shader);
		glGetShaderiv(shader, GL_COMPILE_STATUS, &result);

		if (result == GL_FALSE) {

			int32_t length;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

			std::string info(static_cast<std::string::size_type>(length - 1), '\0');
			glGetShaderInfoLog(shader, length, NULL, info.data());
			info.erase(info.find_last_not_of(" \r\n\t\v") + 1);

			throw ShaderException(info, type);

		}

	}
	int32_t Shader::getUniformLocation(const std::string& name) {

		const auto& iterator = uniformLocationCache.find(name);
		if (iterator != uniformLocationCache.end()) {
			return iterator->second;
		}

		int32_t location = glGetUniformLocation(id, name.data());
		uniformLocationCache[name] = location;
		return location;

	}

	void Shader::bind() const {
		glUseProgram(id);
	}
	void Shader::unbind() const {
		glUseProgram(0);
	}

	void Shader::setUniform(const std::string& name, const int value) {
		glUniform1i(getUniformLocation(name), value);
	}
	void Shader::setUniform(const std::string& name, const float value) {
		glUniform1f(getUniformLocation(name), value);
	}

	void Shader::setUniform(const std::string& name, const Vec2f& value) {
		glUniform2fv(getUniformLocation(name), 1, (float*)value);
	}
	void Shader::setUniform(const std::string& name, const Vec3f& value) {
		glUniform3fv(getUniformLocation(name), 1, (float*)value);
	}
	void Shader::setUniform(const std::string& name, const Vec4f& value) {
		glUniform4fv(getUniformLocation(name), 1, (float*)value);
	}

	void Shader::setUniform(const std::string& name, const Mat2f& value) {
		glUniformMatrix2fv(getUniformLocation(name), 1, GL_FALSE, (float*)value);
	}
	void Shader::setUniform(const std::string& name, const Mat3f& value) {
		glUniformMatrix3fv(getUniformLocation(name), 1, GL_FALSE, (float*)value);
	}
	void Shader::setUniform(const std::string& name, const Mat4f& value) {
		glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, (float*)value);
	}

}
