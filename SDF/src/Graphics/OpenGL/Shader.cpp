#include <SDF/Graphics/OpenGL/Shader.hpp>

#include <sstream>
#include <fstream>

// temp
#include <iostream>

#include "OpenGL.hpp"

// TEMPORARY
namespace sdf::gl {

	GLenum getEnum(const ShaderType& type) {
		switch (type) {
			case ShaderType::VertexShader: return gl::GL_VERTEX_SHADER;
			case ShaderType::FragmentShader: return gl::GL_FRAGMENT_SHADER;
		}
		throw "UNSUPPORTED TYPE"; // TODO: Replace with assert
	}

}

namespace sdf {

	Shader::Shader(const std::vector<ShaderSource>& sources) {

		id = gl::glCreateProgram();

		std::vector<uint32_t> shaders;
		for (const auto& source : sources) {

			uint32_t shader = gl::glCreateShader(gl::getEnum(source.type));
			shaders.push_back(shader);

			const char* data = source.data.c_str();
			gl::glShaderSource(shader, 1, &data, NULL);

			if (compileShader(shader)) {
				gl::glAttachShader(id, shader);
			}

		}

		gl::glLinkProgram(id); // Check link status?
		for (const auto& shader : shaders) gl::glDeleteShader(shader);

	}
	Shader::~Shader() {
		gl::glDeleteProgram(id);
	}

	bool Shader::compileShader(const uint32_t shader) const {

		int32_t result;
		gl::glCompileShader(shader);
		gl::glGetShaderiv(shader, gl::GL_COMPILE_STATUS, &result);

		if (result == gl::GL_FALSE) {

			int32_t length;
			gl::glGetShaderiv(shader, gl::GL_INFO_LOG_LENGTH, &length);

			std::string info;
			info.resize(static_cast<std::string::size_type>(length - 1));
			gl::glGetShaderInfoLog(shader, length, NULL, info.data());

			//LOG_ERROR("OpenGL Shader Compiler: Failed to compile a shader:");

			std::istringstream iss(info);
			for (std::string line; std::getline(iss, line);) {
				//LOG_ERROR("  {0}", line);
				std::cerr << line << std::endl;
			}

		}

		return result == gl::GL_TRUE;

	}
	int32_t Shader::getUniformLocation(const std::string& name) {

		const auto& iterator = uniformLocationCache.find(name);
		if (iterator != uniformLocationCache.end()) {
			return iterator->second;
		}

		int32_t location = gl::glGetUniformLocation(id, name.data());
		uniformLocationCache[name] = location;
		return location;

	}

	void Shader::bind() const {
		gl::glUseProgram(id);
	}
	void Shader::unbind() const {
		gl::glUseProgram(0);
	}

	void Shader::setUniform(const std::string& name, const int value) {
		gl::glUniform1i(getUniformLocation(name), value);
	}
	void Shader::setUniform(const std::string& name, const float value) {
		gl::glUniform1f(getUniformLocation(name), value);
	}

	void Shader::setUniform(const std::string& name, const Vec2f& value) {
		gl::glUniform2fv(getUniformLocation(name), 1, (float*)value);
	}
	void Shader::setUniform(const std::string& name, const Vec3f& value) {
		gl::glUniform3fv(getUniformLocation(name), 1, (float*)value);
	}
	void Shader::setUniform(const std::string& name, const Vec4f& value) {
		gl::glUniform4fv(getUniformLocation(name), 1, (float*)value);
	}

	void Shader::setUniform(const std::string& name, const Mat2f& value) {
		gl::glUniformMatrix2fv(getUniformLocation(name), 1, gl::GL_FALSE, (float*)value);
	}
	void Shader::setUniform(const std::string& name, const Mat3f& value) {
		gl::glUniformMatrix3fv(getUniformLocation(name), 1, gl::GL_FALSE, (float*)value);
	}
	void Shader::setUniform(const std::string& name, const Mat4f& value) {
		gl::glUniformMatrix4fv(getUniformLocation(name), 1, gl::GL_FALSE, (float*)value);
	}

}
