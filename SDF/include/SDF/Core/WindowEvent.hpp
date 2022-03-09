/*
* Copyright (c) 2021 Adam Charvát <https://www.skulaurun.eu>
* Licensed under the MIT License,
* for details see accompanying LICENSE file or a copy at
* <https://github.com/Skulaurun/SDF/blob/v1.0.0/LICENSE>.
* SPDX-License-Identifier: MIT
*/

#pragma once

#include "Event.hpp"
#include "Window.hpp"
#include "Input.hpp"

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
        WindowMoveEvent(Window& window, const int32_t x, const int32_t y)
            : WindowEvent(window), x(x), y(y) {}

        int32_t getX() const { return x; }
        int32_t getY() const { return y; }

        virtual const std::type_info& getType() const override { return typeid(WindowMoveEvent); }

    private:
        int32_t x, y;

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

    class WindowInputEvent : public WindowEvent {

    public:
        WindowInputEvent(
            Window& window,
            const uint8_t mask
        ) :
            WindowEvent(window),
            ctrlPressed((mask >> 0) & 1u),
            shiftPressed((mask >> 1) & 1u),
            altPressed((mask >> 2) & 1u)
        {}

        bool isCtrlPressed() const { return ctrlPressed; }
        bool isShiftPressed() const { return shiftPressed; }
        bool isAltPressed() const { return altPressed; }

        virtual const std::type_info& getType() const override { return typeid(WindowInputEvent); }

    private:
        bool ctrlPressed;
        bool shiftPressed;
        bool altPressed;

    };

    class WindowKeyboardEvent : public WindowInputEvent {

    public:
        WindowKeyboardEvent(
            Window& window,
            const uint8_t mask,
            const Input::Key key
        ) :
            WindowInputEvent(window, mask),
            keyPressed((mask >> 3) & 1u),
            key(key)
        {}

        Input::Key getKey() const { return key; }
        bool isKeyPressed() const { return keyPressed; }

        virtual const std::type_info& getType() const override { return typeid(WindowKeyboardEvent); }

    private:
        Input::Key key;
        bool keyPressed;

    };

    class WindowMouseEvent : public WindowInputEvent {

    public:
        WindowMouseEvent(
            Window& window,
            const uint8_t mask,
            const int32_t x,
            const int32_t y
        ) :
            WindowInputEvent(window, mask),
            x(x),
            y(y)
        {}

        int32_t getX() const { return x; }
        int32_t getY() const { return y; }

        virtual const std::type_info& getType() const override { return typeid(WindowMouseEvent); }

    private:
        int32_t x, y;

    };

    class WindowMouseMoveEvent : public WindowMouseEvent {

    public:
        WindowMouseMoveEvent(
            Window& window,
            const uint8_t mask,
            const int32_t mouseX,
            const int32_t mouseY
        ) :
            WindowMouseEvent(
                window,
                mask,
                mouseX,
                mouseY
            )
        {}

        virtual const std::type_info& getType() const override { return typeid(WindowMouseMoveEvent); }

    };

    class WindowMouseScrollEvent : public WindowMouseEvent {

    public:
        WindowMouseScrollEvent(
            Window& window,
            const uint8_t mask,
            const int32_t mouseX,
            const int32_t mouseY,
            const float scrollX,
            const float scrollY
        ) :
            WindowMouseEvent(
                window,
                mask,
                mouseX,
                mouseY
            ),
            scrollX(scrollX),
            scrollY(scrollY)
        {}

        float getScrollX() const { return scrollX; }
        float getScrollY() const { return scrollY; }

        virtual const std::type_info& getType() const override { return typeid(WindowMouseScrollEvent); }

    private:
        float scrollX, scrollY;

    };

    class WindowMouseButtonEvent : public WindowMouseEvent {

    public:
        WindowMouseButtonEvent(
            Window& window,
            const uint8_t mask,
            const uint32_t mouseX,
            const uint32_t mouseY,
            const Input::Button button
        ) :
            WindowMouseEvent(
                window,
                mask,
                mouseX,
                mouseY
            ),
            buttonPressed((mask >> 3) & 1u),
            button(button)
        {}

        bool isButtonPressed() const { return buttonPressed; }
        Input::Button getButton() const { return button; }

        virtual const std::type_info& getType() const override { return typeid(WindowMouseButtonEvent); }

    private:
        bool buttonPressed;
        Input::Button button;

    };

}
