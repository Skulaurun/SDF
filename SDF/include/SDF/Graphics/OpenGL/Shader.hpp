#pragma once

#include <SDF/Graphics/RendererObject.hpp>

#include <SDF/Core/Vector.hpp>
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
		bool compileShader(const uint32_t shader) const;
		int32_t getUniformLocation(const std::string& name);

	private:
		std::unordered_map<std::string, int32_t> uniformLocationCache;

	};

}
