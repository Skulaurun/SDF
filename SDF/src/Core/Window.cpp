#include <SDF/Core/Window.hpp>
#include <SDF/Core/Exception.hpp>
#include <SDF/Core/Input.hpp>

#include "WinError.hpp"
#include "WGLContext.hpp"

#define UNICODE
#include <windows.h>
#include <windowsx.h>

namespace sdf {

    Window::Window(const std::wstring& title, const uint32_t width, const uint32_t height)
        : title(title), width(width), height(height), keyAutoRepeat(true), x(CW_USEDEFAULT), y(CW_USEDEFAULT) {
    
        struct WindowDescriptor {

            WindowDescriptor(const wchar_t* className) : windowClass({}) {
                windowClass.lpszClassName = (LPCWSTR)className;
                windowClass.lpfnWndProc = _windowProcedure;
                RegisterClass(&windowClass);
            }

            WNDCLASS windowClass;

        };
        
        static WindowDescriptor descriptor(L"Simple Dedicated Framework (SDF)");

        RECT rect = { 0, 0, (LONG)width, (LONG)height };
        AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, FALSE, NULL);

        hWindow = CreateWindowEx(
            0,
            descriptor.windowClass.lpszClassName,
            (LPCWSTR)title.c_str(),
            WS_OVERLAPPEDWINDOW,
            x, y,
            rect.right - rect.left, rect.bottom - rect.top,
            NULL,
            NULL,
            NULL,
            NULL
        );

        if (hWindow == NULL) {
            WinError error = WinError::getLastError();
            throw SystemException(error.message, error.code);
        }

        SetWindowLongPtr(hWindow, GWLP_USERDATA, (LONG_PTR)this);

        emitEvent = std::bind(&Window::defaultEventCallback, this, std::placeholders::_1);

        wglContext = std::make_unique<WGLContext>(*this);
        wglContext->makeCurrent();
    
    }
    Window::~Window() {
        close();
    }

    LRESULT CALLBACK Window::_windowProcedure(HWND hWindow, UINT message, WPARAM wParam, LPARAM lParam) {

        Window* me = (Window*)GetWindowLongPtr(hWindow, GWLP_USERDATA);
        if (me) {
            return me->windowProcedure(message, wParam, lParam);
        }

        return DefWindowProc(hWindow, message, wParam, lParam);

    }
    LRESULT CALLBACK Window::windowProcedure(UINT message, WPARAM wParam, LPARAM lParam) {

        switch (message) {

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        case WM_CLOSE:
            emitEvent(WindowCloseEvent(*this));
            return 0;

        case WM_MOVE:
            onMove(lParam);
            return 0;

        case WM_SIZE:
            onSize(lParam);
            return 0;

        case WM_MOUSEMOVE:
            onMouseInteract(wParam, lParam);
            return 0;

        case WM_LBUTTONDOWN:
        case WM_RBUTTONDOWN:
        case WM_MBUTTONDOWN:
        case WM_XBUTTONDOWN:
            onMouseInteract(wParam, lParam);
            return 0;

        case WM_LBUTTONUP:
        case WM_RBUTTONUP:
        case WM_MBUTTONUP:
        case WM_XBUTTONUP:
            onMouseInteract(wParam, lParam);
            return 0;

        case WM_KEYDOWN:
        case WM_SYSKEYDOWN:
            onKeyboardInteract(wParam, lParam);
            return 0;

        case WM_KEYUP:
        case WM_SYSKEYUP:
            onKeyboardInteract(wParam, lParam);
            return 0;

        default:
            return DefWindowProc(hWindow, message, wParam, lParam);

        }

    }

    void Window::onMove(LPARAM lParam) {

        x = LOWORD(lParam);
        y = HIWORD(lParam);

        emitEvent(WindowMoveEvent(*this, x, y));

    }
    void Window::onSize(LPARAM lParam) {

        width = GET_X_LPARAM(lParam);
        height = GET_Y_LPARAM(lParam);

        emitEvent(WindowResizeEvent(*this, width, height));

    }
    void Window::onMouseInteract(WPARAM wParam, LPARAM lParam) {

        // From MSDN: https://docs.microsoft.com/en-us/windows/win32/inputdev/wm-lbuttondown#remarks
        // To detect that the ALT key was pressed, check whether GetKeyState with VK_MENU < 0.
        // Note, this must not be GetAsyncKeyState.

        uint32_t posX = GET_X_LPARAM(lParam);
        uint32_t posY = GET_Y_LPARAM(lParam);

        if (wParam != 0) {

            // emit buttonup or buttondown event

            bool isAltDown = GetKeyState(VK_MENU) < 0;

            //emitEvent(WindowMouseButtonEvent(
            //	*this,
            //	wParam & MK_CONTROL,
            //	wParam & MK_SHIFT,
            //	posX, posY,
            //
            //));

        } else {
            // emit mouse move event
        }

        //bool isLeftButton = wParam & MK_LBUTTON;

        // TODO: Add support for Ctrl, Shift, Alt, etc.
        
        //lastEvent.mouse.button = Input::getButton(wParam);

    }
    void Window::onKeyboardInteract(WPARAM wParam, LPARAM lParam) {

        UINT scanCode = (lParam & 0x00ff0000) >> 16; // Access 16th - 23th bit

        bool isExtendedKey = (lParam >> 0x18) & 1; // Check 24th bit
        int previousState = (lParam >> 0x1E) & 1; // Check 30th bit
        int currentState = (lParam >> 0x1F) & 1; // Check 31th bit

        switch (wParam) {

            case VK_MENU: wParam = isExtendedKey ? VK_RMENU : VK_LMENU; break;
            case VK_CONTROL: wParam = isExtendedKey ? VK_RCONTROL : VK_LCONTROL; break;

            case VK_SHIFT: wParam = MapVirtualKey(scanCode, MAPVK_VSC_TO_VK_EX); break;

        }

        Input::Key key = Input::toKey(wParam);
        uint8_t mask = ((uint8_t)(GetKeyState(VK_CONTROL) < 0) << 0) |
                       ((uint8_t)(GetKeyState(VK_SHIFT) < 0)   << 1) |
                       ((uint8_t)(GetKeyState(VK_MENU) < 0)    << 2);

        if (currentState == 0) {
            if (previousState == 0 || keyAutoRepeat == true) {
                emitEvent(WindowKeyboardEvent(
                    *this, mask | (1u << 3), key
                ));
            }
        }
        else {
            emitEvent(WindowKeyboardEvent(
                *this, mask, key
            ));
        }

    }

    void Window::defaultEventCallback(const WindowEvent& e) {
        if (e.is<WindowCloseEvent>()) {
            close();
        }
    }

    bool Window::makeContextCurrent() {
        return wglContext->makeCurrent();
    }

    void Window::show() {
        ShowWindow(hWindow, SW_SHOW);
    }
    void Window::hide() {
        ShowWindow(hWindow, SW_HIDE);
    }
    void Window::focus() {
        SetFocus(hWindow);
    }
    void Window::maximize() {
        ShowWindow(hWindow, SW_MAXIMIZE);
    }
    void Window::minimize() {
        ShowWindow(hWindow, SW_MINIMIZE);
    }
    void Window::restore() {
        ShowWindow(hWindow, SW_RESTORE);
    }

    void Window::display() {
        wglContext->swapBuffers();
    }

    void Window::pollEvents() {

        MSG message;
        if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE) != 0) {

            TranslateMessage(&message);
            DispatchMessage(&message);

        }

    }

    void Window::close() {
        DestroyWindow(hWindow);
    }

    bool Window::isOpen() const {
        return IsWindow(hWindow);
    }

    bool Window::isVisible() const {
        return IsWindowVisible(hWindow);
    }

    bool Window::hasFocus() const {
        return GetFocus() == hWindow;
    }

}
