/*
* Copyright (c) 2021 Adam Charvát <https://www.skulaurun.eu>
* Licensed under the MIT License,
* for details see accompanying LICENSE file or a copy at
* <https://github.com/Skulaurun/SDF/blob/v1.0.0/LICENSE>.
* SPDX-License-Identifier: MIT
*/

#include <SDF/SDF.hpp>

#include <iostream>

void onWindowResize(const sdf::WindowResizeEvent& e) {
    // Width and height are the new dimensions of the window
    std::cout << "Window resized: (" << e.getWidth() << ", " << e.getHeight() << ")\n";
}
void onWindowMove(const sdf::WindowMoveEvent& e) {
    // [X;Y] are the coordinates where the top left window corner was
    // when this event got processed
    std::cout << "Window moved: (" << e.getX() << ", " << e.getY() << ")\n";
}

void onMouseMoveEvent(const sdf::WindowMouseMoveEvent& e) {
    // [X;Y] are the coordinates where mouse pointer was
    // when this event got processed
    std::cout << "Mouse moved: (" << e.getX() << ", " << e.getY() << ")\n";
}
void onMouseScrollEvent(const sdf::WindowMouseScrollEvent& e) {
    // If vertical wheel was used, scrollX is zero
    // If horizontal wheel was used, scrollY is zero
    std::cout << "Mouse scrolled: (" << e.getScrollX() << ", " << e.getScrollY() << ")\n";
}
void onMouseButtonEvent(const sdf::WindowMouseButtonEvent& e) {

    // If the button that triggered this event is pressed
    if (e.isButtonPressed()) {

        // Shift, Ctrl and Alt are commonly combined with buttons
        // that is when these quality of life functions come in handy
        if (e.isCtrlPressed() && e.getButton() == sdf::Input::Button::Left) {
            std::cout << "Button-key combination! (Ctrl + Left mouse)" << std::endl;
        }

        // Decide which button was pressed
        // and get click position in window coordinates
        switch (e.getButton()) {

        case sdf::Input::Button::Left:
            std::cout << "Left-clicked at (" << e.getX() << ", " << e.getY() << ")" << std::endl;
            break;

        case sdf::Input::Button::Right:
            std::cout << "Right-clicked at (" << e.getX() << ", " << e.getY() << ")" << std::endl;
            break;

        case sdf::Input::Button::Middle:
            std::cout << "Middle-clicked at (" << e.getX() << ", " << e.getY() << ")"
                << std::endl;
            break;

        default:
            std::cout << ((int32_t)e.getButton()) << " button was pressed" << std::endl;
            break;

        }

    } else {
        std::cout << ((int32_t)e.getButton()) << " button was released" << std::endl;
    }

}

void onKeyboardEvent(const sdf::WindowKeyboardEvent& e) {

    // If the key that triggered this event is pressed
    if (e.isKeyPressed()) {

        // Shift, Ctrl and Alt are commonly combined with other keys
        // that is when these quality of life functions come in handy
        if (e.isShiftPressed() && e.getKey() == sdf::Input::Key::F) {
            std::cout << "Key combination! (Shift + F)" << std::endl;
        }

        std::cout << ((int32_t)e.getKey()) << " key was pressed" << std::endl;

    }
    else {
        std::cout << ((int32_t)e.getKey()) << " key was released" << std::endl;
    }

}

void onWindowEvent(const sdf::WindowEvent& e) {

    // Dispatch events we want to handle,
    // the dispatch method takes care of the event type checking

    e.dispatch<sdf::WindowMoveEvent>(onWindowMove);
    e.dispatch<sdf::WindowResizeEvent>(onWindowResize);

    e.dispatch<sdf::WindowMouseMoveEvent>(onMouseMoveEvent);
    e.dispatch<sdf::WindowMouseScrollEvent>(onMouseScrollEvent);
    e.dispatch<sdf::WindowMouseButtonEvent>(onMouseButtonEvent);

    e.dispatch<sdf::WindowKeyboardEvent>(onKeyboardEvent);

    // Invoke default behavior for certain events
    e.defaultDispatch();

}

int doExample01() {

    // Create the window
    sdf::Window window(L"Sandbox App", 800, 600);

    // Use custom callback for event handling
    window.setEventCallback(onWindowEvent);

    // Make the window visible
    window.show();

    // Loop until the window is closed
    while (window.isOpen()) {

        // Swap window buffers
        window.display();

        // Process user input and call event callbacks
        window.pollEvents();

    }

    return 0;

}
