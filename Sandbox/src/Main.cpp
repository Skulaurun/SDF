#include <SDF/SDF.hpp>

#include <iostream>

void onWindowResize(const sdf::WindowResizeEvent& e) {
    std::cout << "Window resized: (" << e.getWidth() << ", " << e.getHeight() << ")\n";
}

void onWindowMove(const sdf::WindowMoveEvent& e) {
    std::cout << "Window moved: (" << e.getX() << ", " << e.getY() << ")\n";
}

void onWindowKeyboardEvent(const sdf::WindowKeyboardEvent& e) {

    // If the key that triggered this event is pressed
    if (e.isKeyPressed()) {

        // Shift, Ctrl and Alt are commonly combined with other keys
        // that is when these quality of life functions come in handy
        if (e.isShiftPressed() && e.getKey() == sdf::Input::Key::F) {
            std::cout << "Key combination! (Shift + F)" << std::endl;
        }

        std::cout << ((int32_t)e.getKey()) << " key was pressed" << std::endl;

    } else {
        std::cout << ((int32_t)e.getKey()) << " key was released" << std::endl;
    }

}

void onWindowEvent(const sdf::WindowEvent& e) {

    // Dispatch events we want to handle,
    // the dispatch method takes care of the event type checking
    e.dispatch<sdf::WindowMoveEvent>(onWindowMove);
    e.dispatch<sdf::WindowResizeEvent>(onWindowResize);
    e.dispatch<sdf::WindowKeyboardEvent>(onWindowKeyboardEvent);

    // Invokes the default behavior for certain events
    e.defaultDispatch();

}

int main() {
    
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
