/*
* Copyright (c) 2021 Adam Charv�t <https://www.skulaurun.eu>
* Licensed under the MIT License,
* for details see accompanying LICENSE file or a copy at
* <https://github.com/Skulaurun/SDF/blob/v1.0.0/LICENSE>.
* SPDX-License-Identifier: MIT
*/

#pragma once

#include <SDF/Core/Exception.hpp>

#include <SDF/Graphics/RendererObject.hpp>
#include <SDF/Graphics/Vector.hpp>
#include <SDF/Graphics/Matrix.hpp>

#include <cstdint>
#include <vector>
#include <string>
#include <unordered_map>

namespace sdf {

	enum class ShaderType : uint8_t {
		VertexShader, FragmentShader
	};

	struct ShaderSource {
		ShaderType type;
		std::string data;
	};

	class Shader : public RendererObject {

	public:
		Shader(const std::vector<ShaderSource>& sources);
		virtual ~Shader();

		void bind() const override;
		void unbind() const override;

		void setUniform(const std::string& name, const int value);
		void setUniform(const std::string& name, const float value);

		void setUniform(const std::string& name, const Vec2f& value);
		void setUniform(const std::string& name, const Vec3f& value);
		void setUniform(const std::string& name, const Vec4f& value);
		
		void setUniform(const std::string& name, const Mat2f& value);
		void setUniform(const std::string& name, const Mat3f& value);
		void setUniform(const std::string& name, const Mat4f& value);

	private:
		int32_t getUniformLocation(const std::string& name);
		void compileShader(const uint32_t shader, const ShaderType type) const;

	private:
		std::unordered_map<std::string, int32_t> uniformLocationCache;

	};

	class ShaderException : public Exception {

    public:
        explicit ShaderException(const std::string& message, const ShaderType type) noexcept
            : Exception(message.c_str()), type(type) {}

		virtual ShaderType shader() const { return type; }

	private:
		ShaderType type;

    };

}
