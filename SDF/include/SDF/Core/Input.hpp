/*
* Copyright (c) 2021 Adam Charv�t <https://www.skulaurun.eu>
* Licensed under the MIT License,
* for details see accompanying LICENSE file or a copy at
* <https://github.com/Skulaurun/SDF/blob/v1.0.0/LICENSE>.
* SPDX-License-Identifier: MIT
*/

#pragma once

#include <cstdint>

namespace sdf {

    class Window;

    struct MousePosition {

    public:
        MousePosition(const int32_t x, const int32_t y)
            : x(x), y(y) {}

        MousePosition& relativeTo(const Window& window);
        MousePosition& relativeAndClampTo(const Window& window);

    public:
        int32_t x;
        int32_t y;

    };

    class Input {

    public:
        enum class Key : int16_t {

            Unknown = -1,

            F1, F2, F3, F4, F5, F6,
            F7, F8, F9, F10, F11, F12,
            F13, F14, F15, F16, F17, F18,
            F19, F20, F21, F22, F23, F24,

            Num0, Num1, Num2, Num3, Num4,
            Num5, Num6, Num7, Num8, Num9,

            A, B, C, D, E, F, G, H, I, J,
            K, L, M, N, O, P, Q, R, S, T,
            U, V, W, X, Y, Z,
            
            Semicolon,      /* ; */
            Comma,          /* , */
            Period,         /* . */
            Quote,          /* ' */
            Slash,          /* / */
            Backslash,      /* \ */
            Tilde,          /* ~ */
            Equal,          /* = */
            Hyphen,         /* - */
            LeftBracket,    /* [ */
            RightBracket,   /* ] */

            LeftControl, LeftShift,  LeftAlt,  LeftSystem,
            RightControl, RightShift, RightAlt, RightSystem,

            Escape, PrintScreen, ScrollLock, Pause, Menu,
            Space, Enter, Backspace, Tab, CapsLock,

            Insert, Home, PageUp,
            Delete, End, PageDown,

            Left, Up, Right, Down,

            Numpad0, Numpad1, Numpad2, Numpad3, Numpad4,
            Numpad5, Numpad6, Numpad7, Numpad8, Numpad9,

            Add, Subtract, Multiply, Divide,
            Decimal, NumLock,

            Dash = Hyphen,
            Apostrophe = Quote,
            GraveAccent = Tilde

            /*
            * Missing keys:
            *   Numpad Enter
            *   Numpad Equal
            */

        };

        enum class Button : int16_t {

            Unknown = -1,

            B0, B1, B2,
            B3, B4,

            Left = B0,
            Right = B1,
            Middle = B2

        };

    public:
        static MousePosition getMousePosition();

        static bool isKeyPressed(const Key key);
        static bool isButtonPressed(const Button button);

        static Key toKey(const int32_t code);
        static Button toButton(const int32_t code);

        static int32_t toNativeKey(const Key key);
        static int32_t toNativeButton(const Button button);

    };

}
