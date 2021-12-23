#pragma once

#include "Input.hpp"

#include <cstdint>
#include <typeindex>
#include <functional>
#include <cassert>

namespace sdf {

	enum class EventType {
		WindowClose, WindowMove, WindowResize
	};

	class Event {

	public:
		virtual ~Event() = default;

		virtual EventType getType() const = 0;

	};

	// TODO: Add template<typename T, ...> void callIf(...)?
	// TODO: Add get method for safe casting (runtime check)

}
