/*
* Copyright (c) 2021 Adam Charvát <https://www.skulaurun.eu>
* Licensed under the MIT License,
* for details see accompanying LICENSE file or a copy at
* <https://github.com/Skulaurun/SDF/blob/v1.0.0/LICENSE>.
* SPDX-License-Identifier: MIT
*/

#include <PCH.hpp>

#include <SDF/Core/Input.hpp>

namespace sdf {
    
    bool Input::isButtonPressed(const Button button) {
        return (GetAsyncKeyState(toNativeButton(button)) & 0x8000) != 0;
    }

    bool Input::isKeyPressed(const Key key) {
        return (GetAsyncKeyState(toNativeKey(key)) & 0x8000) != 0;
    }

    Input::Button Input::toButton(const int32_t code) {

        switch (code) {

            case VK_LBUTTON:    return GetSystemMetrics(SM_SWAPBUTTON) ? Button::B1 : Button::B0;
            case VK_RBUTTON:    return GetSystemMetrics(SM_SWAPBUTTON) ? Button::B0 : Button::B1;

            case VK_MBUTTON:    return Button::B2;
            case VK_XBUTTON1:   return Button::B3;
            case VK_XBUTTON2:   return Button::B4;

            default:            return Button::Unknown;

        }

    }

    int32_t Input::toNativeButton(const Button button) {

        switch (button) {

            case Button::B0:        return GetSystemMetrics(SM_SWAPBUTTON) ? VK_RBUTTON : VK_LBUTTON;
            case Button::B1:        return GetSystemMetrics(SM_SWAPBUTTON) ? VK_LBUTTON : VK_RBUTTON;

            case Button::B2:        return VK_MBUTTON;
            case Button::B3:        return VK_XBUTTON1;
            case Button::B4:        return VK_XBUTTON2;

            default:                return -1;

        }

    }

    int32_t Input::toNativeKey(const Key key) {
        
        switch (key) {

            case Key::F1:           return VK_F1;
            case Key::F2:           return VK_F2;
            case Key::F3:           return VK_F3;
            case Key::F4:           return VK_F4;
            case Key::F5:           return VK_F5;
            case Key::F6:           return VK_F6;
            case Key::F7:           return VK_F7;
            case Key::F8:           return VK_F8;
            case Key::F9:           return VK_F9;
            case Key::F10:          return VK_F10;
            case Key::F11:          return VK_F11;
            case Key::F12:          return VK_F12;
            case Key::F13:          return VK_F13;
            case Key::F14:          return VK_F14;
            case Key::F15:          return VK_F15;
            case Key::F16:          return VK_F16;
            case Key::F17:          return VK_F17;
            case Key::F18:          return VK_F18;
            case Key::F19:          return VK_F19;
            case Key::F20:          return VK_F20;
            case Key::F21:          return VK_F21;
            case Key::F22:          return VK_F22;
            case Key::F23:          return VK_F23;
            case Key::F24:          return VK_F24;

            case Key::Num0:         return '0';
            case Key::Num1:         return '1';
            case Key::Num2:         return '2';
            case Key::Num3:         return '3';
            case Key::Num4:         return '4';
            case Key::Num5:         return '5';
            case Key::Num6:         return '6';
            case Key::Num7:         return '7';
            case Key::Num8:         return '8';
            case Key::Num9:         return '9';
            case Key::A:            return 'A';
            case Key::B:            return 'B';
            case Key::C:            return 'C';
            case Key::D:            return 'D';
            case Key::E:            return 'E';
            case Key::F:            return 'F';
            case Key::G:            return 'G';
            case Key::H:            return 'H';
            case Key::I:            return 'I';
            case Key::J:            return 'J';
            case Key::K:            return 'K';
            case Key::L:            return 'L';
            case Key::M:            return 'M';
            case Key::N:            return 'N';
            case Key::O:            return 'O';
            case Key::P:            return 'P';
            case Key::Q:            return 'Q';
            case Key::R:            return 'R';
            case Key::S:            return 'S';
            case Key::T:            return 'T';
            case Key::U:            return 'U';
            case Key::V:            return 'V';
            case Key::W:            return 'W';
            case Key::X:            return 'X';
            case Key::Y:            return 'Y';
            case Key::Z:            return 'Z';

            case Key::Semicolon:    return VK_OEM_1;
            case Key::Slash:        return VK_OEM_2;
            case Key::Tilde:        return VK_OEM_3;
            case Key::LeftBracket:  return VK_OEM_4;
            case Key::Backslash:    return VK_OEM_5;
            case Key::RightBracket: return VK_OEM_6;
            case Key::Quote:        return VK_OEM_7;
            case Key::Comma:        return VK_OEM_COMMA;
            case Key::Equal:        return VK_OEM_PLUS;
            case Key::Hyphen:       return VK_OEM_MINUS;
            case Key::Period:       return VK_OEM_PERIOD;

            case Key::LeftControl:  return VK_LCONTROL;
            case Key::RightControl: return VK_RCONTROL;
            case Key::LeftShift:    return VK_LSHIFT;
            case Key::RightShift:   return VK_RSHIFT;
            case Key::LeftAlt:      return VK_LMENU;
            case Key::RightAlt:     return VK_RMENU;
            case Key::LeftSystem:   return VK_LWIN;
            case Key::RightSystem:  return VK_RWIN;

            case Key::Escape:       return VK_ESCAPE;
            case Key::PrintScreen:  return VK_SNAPSHOT;
            case Key::ScrollLock:   return VK_SCROLL;
            case Key::Pause:        return VK_PAUSE;
            case Key::Menu:         return VK_APPS;
            case Key::Space:        return VK_SPACE;
            case Key::Enter:        return VK_RETURN;
            case Key::Backspace:    return VK_BACK;
            case Key::Tab:          return VK_TAB;
            case Key::CapsLock:     return VK_CAPITAL;

            case Key::Insert:       return VK_INSERT;
            case Key::Home:         return VK_HOME;
            case Key::PageUp:       return VK_PRIOR;
            case Key::Delete:       return VK_DELETE;

            case Key::Left:         return VK_LEFT;
            case Key::Right:        return VK_RIGHT;
            case Key::Up:           return VK_UP;
            case Key::Down:         return VK_DOWN;
            case Key::End:          return VK_END;
            case Key::PageDown:     return VK_NEXT;

            case Key::Numpad0:      return VK_NUMPAD0;
            case Key::Numpad1:      return VK_NUMPAD1;
            case Key::Numpad2:      return VK_NUMPAD2;
            case Key::Numpad3:      return VK_NUMPAD3;
            case Key::Numpad4:      return VK_NUMPAD4;
            case Key::Numpad5:      return VK_NUMPAD5;
            case Key::Numpad6:      return VK_NUMPAD6;
            case Key::Numpad7:      return VK_NUMPAD7;
            case Key::Numpad8:      return VK_NUMPAD8;
            case Key::Numpad9:      return VK_NUMPAD9;

            case Key::Add:          return VK_ADD;
            case Key::Subtract:     return VK_SUBTRACT;
            case Key::Multiply:     return VK_MULTIPLY;
            case Key::Divide:       return VK_DIVIDE;
            case Key::Decimal:      return VK_DECIMAL;
            case Key::NumLock:      return VK_NUMLOCK;

            default:                return -1;

        }

    }

    Input::Key Input::toKey(const int32_t code) {

        switch (code) {

            case VK_F1:             return Key::F1;
            case VK_F2:             return Key::F2;
            case VK_F3:             return Key::F3;
            case VK_F4:             return Key::F4;
            case VK_F5:             return Key::F5;
            case VK_F6:             return Key::F6;
            case VK_F7:             return Key::F7;
            case VK_F8:             return Key::F8;
            case VK_F9:             return Key::F9;
            case VK_F10:            return Key::F10;
            case VK_F11:            return Key::F11;
            case VK_F12:            return Key::F12;
            case VK_F13:            return Key::F13;
            case VK_F14:            return Key::F14;
            case VK_F15:            return Key::F15;
            case VK_F16:            return Key::F16;
            case VK_F17:            return Key::F17;
            case VK_F18:            return Key::F18;
            case VK_F19:            return Key::F19;
            case VK_F20:            return Key::F20;
            case VK_F21:            return Key::F21;
            case VK_F22:            return Key::F22;
            case VK_F23:            return Key::F23;
            case VK_F24:            return Key::F24;

            case '0':               return Key::Num0;
            case '1':               return Key::Num1;
            case '2':               return Key::Num2;
            case '3':               return Key::Num3;
            case '4':               return Key::Num4;
            case '5':               return Key::Num5;
            case '6':               return Key::Num6;
            case '7':               return Key::Num7;
            case '8':               return Key::Num8;
            case '9':               return Key::Num9;

            case 'A':               return Key::A;
            case 'B':               return Key::B;
            case 'C':               return Key::C;
            case 'D':               return Key::D;
            case 'E':               return Key::E;
            case 'F':               return Key::F;
            case 'G':               return Key::G;
            case 'H':               return Key::H;
            case 'I':               return Key::I;
            case 'J':               return Key::J;
            case 'K':               return Key::K;
            case 'L':               return Key::L;
            case 'M':               return Key::M;
            case 'N':               return Key::N;
            case 'O':               return Key::O;
            case 'P':               return Key::P;
            case 'Q':               return Key::Q;
            case 'R':               return Key::R;
            case 'S':               return Key::S;
            case 'T':               return Key::T;
            case 'U':               return Key::U;
            case 'V':               return Key::V;
            case 'W':               return Key::W;
            case 'X':               return Key::X;
            case 'Y':               return Key::Y;
            case 'Z':               return Key::Z;

            case VK_OEM_1:          return Key::Semicolon;
            case VK_OEM_2:          return Key::Slash;
            case VK_OEM_3:          return Key::Tilde;
            case VK_OEM_4:          return Key::LeftBracket;
            case VK_OEM_5:          return Key::Backslash;
            case VK_OEM_6:          return Key::RightBracket;
            case VK_OEM_7:          return Key::Quote;
            case VK_OEM_COMMA:      return Key::Comma;
            case VK_OEM_PLUS:       return Key::Equal;
            case VK_OEM_MINUS:      return Key::Hyphen;
            case VK_OEM_PERIOD:     return Key::Period;

            case VK_LCONTROL:       return Key::LeftControl;
            case VK_RCONTROL:       return Key::RightControl;
            case VK_LSHIFT:         return Key::LeftShift;
            case VK_RSHIFT:         return Key::RightShift;
            case VK_LMENU:          return Key::LeftAlt;
            case VK_RMENU:          return Key::RightAlt;
            case VK_LWIN:           return Key::LeftSystem;
            case VK_RWIN:           return Key::RightSystem;

            case VK_ESCAPE:         return Key::Escape;
            case VK_SNAPSHOT:       return Key::PrintScreen;
            case VK_SCROLL:         return Key::ScrollLock;
            case VK_PAUSE:          return Key::Pause;
            case VK_APPS:           return Key::Menu;
            case VK_SPACE:          return Key::Space;
            case VK_RETURN:         return Key::Enter;
            case VK_BACK:           return Key::Backspace;
            case VK_TAB:            return Key::Tab;
            case VK_CAPITAL:        return Key::CapsLock;

            case VK_INSERT:         return Key::Insert;
            case VK_HOME:           return Key::Home;
            case VK_PRIOR:          return Key::PageUp;
            case VK_DELETE:         return Key::Delete;
            case VK_END:            return Key::End;
            case VK_NEXT:           return Key::PageDown;

            case VK_LEFT:           return Key::Left;
            case VK_RIGHT:          return Key::Right;
            case VK_UP:             return Key::Up;
            case VK_DOWN:           return Key::Down;

            case VK_NUMPAD0:        return Key::Numpad0;
            case VK_NUMPAD1:        return Key::Numpad1;
            case VK_NUMPAD2:        return Key::Numpad2;
            case VK_NUMPAD3:        return Key::Numpad3;
            case VK_NUMPAD4:        return Key::Numpad4;
            case VK_NUMPAD5:        return Key::Numpad5;
            case VK_NUMPAD6:        return Key::Numpad6;
            case VK_NUMPAD7:        return Key::Numpad7;
            case VK_NUMPAD8:        return Key::Numpad8;
            case VK_NUMPAD9:        return Key::Numpad9;

            case VK_ADD:            return Key::Add;
            case VK_SUBTRACT:       return Key::Subtract;
            case VK_MULTIPLY:       return Key::Multiply;
            case VK_DIVIDE:         return Key::Divide;
            case VK_DECIMAL:        return Key::Decimal;
            case VK_NUMLOCK:        return Key::NumLock;

            default:                return Key::Unknown;

        }

    }

}
