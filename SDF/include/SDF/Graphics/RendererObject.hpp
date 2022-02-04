#pragma once

#include <cstdint>

namespace sdf {

	class RendererObject {

	public:
		RendererObject() : id(0) {}
		RendererObject(uint32_t id) : id(id) {}

		virtual ~RendererObject() = default;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		bool operator==(const RendererObject& other) { return id == other.id; }

	protected:
		uint32_t id;

	};

}
