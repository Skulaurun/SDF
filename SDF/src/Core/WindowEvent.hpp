#pragma once

#include "Event.hpp"
#include "Window.hpp"

namespace sdf {

	class WindowEvent : public Event {

	public:
		WindowEvent(Window& window) : window(window) {}

		Window& getWindow() const { return window; }

		virtual const std::type_info& getType() const override { return typeid(WindowEvent); }

		virtual void defaultDispatch() const override { window.defaultEventCallback(*this); }

	private:
		Window& window;

	};

	class WindowCloseEvent : public WindowEvent {

	public:
		WindowCloseEvent(Window& window) : WindowEvent(window) {}

		virtual const std::type_info& getType() const override { return typeid(WindowCloseEvent); }

	};

	class WindowMoveEvent : public WindowEvent {

	public:
		WindowMoveEvent(Window& window, const uint32_t x, const uint32_t y)
			: WindowEvent(window), x(x), y(y) {}

		uint32_t getX() const { return x; }
		uint32_t getY() const { return y; }

		virtual const std::type_info& getType() const override { return typeid(WindowMoveEvent); }

	private:
		uint32_t x, y;

	};

	class WindowResizeEvent : public WindowEvent {

	public:
		WindowResizeEvent(Window& window, const uint32_t width, const uint32_t height)
			: WindowEvent(window), width(width), height(height) {}

		uint32_t getWidth() const { return width; }
		uint32_t getHeight() const { return height; }

		virtual const std::type_info& getType() const override { return typeid(WindowResizeEvent); }

	private:
		uint32_t width, height;

	};

}
