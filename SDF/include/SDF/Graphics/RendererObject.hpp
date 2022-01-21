#pragma once

#include <cstdint>

namespace sdf {

	class RendererObject {

	public:
		RendererObject() = default;
		virtual ~RendererObject() = default;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

	protected:
		uint32_t id;

	};

}
