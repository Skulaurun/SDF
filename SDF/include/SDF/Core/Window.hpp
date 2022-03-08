#pragma once

#include "WinTypes.hpp"

#include <cstdint>
#include <string>
#include <functional>

namespace sdf {

    class WGLContext;
    class WindowEvent;

    class Window {

    public:
        Window(const std::wstring& title = L"Simple Dedicated Framework (SDF) Application", const uint32_t width = 800, const uint32_t height = 600);
        ~Window();

        bool makeContextCurrent(); // Call from Renderer::bindTarget(const Window& window)

        void show();
        void hide();
        void focus();
        void maximize();
        void minimize();
        void restore();
        void close();

        void display();
        void pollEvents();

        bool isOpen() const;
        bool isVisible() const;
        bool hasFocus() const;

        void setKeyAutoRepeat(bool repeat) { keyAutoRepeat = repeat; }
        void setEventCallback(const std::function<void(const WindowEvent&)> callback) { emitEvent = callback; }

        void setTitle(const std::wstring& title);

        void defaultEventCallback(const WindowEvent& e);

        std::wstring getTitle() const { return title; }

        int32_t getX() const { return x; }
        int32_t getY() const { return y; }
        uint32_t getWidth() const { return width; }
        uint32_t getHeight() const { return height; }

        HWND getNativeWindow() const { return hWindow; }

    private:
        static LRESULT __stdcall _windowProcedure(HWND hWindow, UINT message, WPARAM wParam, LPARAM lParam);
        LRESULT __stdcall windowProcedure(UINT message, WPARAM wParam, LPARAM lParam);

        void onMove(LPARAM lParam);
        void onSize(LPARAM lParam);
        
        void onMouseMove(WPARAM wParam, LPARAM lParam);
        void onMouseScroll(WPARAM wParam, LPARAM lParam, uint8_t isVertical);
        void onMouseButtonInteract(WPARAM wParam, LPARAM lParam, uint8_t isPressed);

        void onKeyboardInteract(WPARAM wParam, LPARAM lParam);

        static uint8_t getCommonInputMask();

    private:
        std::wstring title;
        int32_t x, y;
        uint32_t width, height;

        bool keyAutoRepeat;
        std::function<void(const WindowEvent&)> emitEvent;

        HWND hWindow;
        std::unique_ptr<WGLContext> wglContext;

    };

}

#include "WindowEvent.hpp"
