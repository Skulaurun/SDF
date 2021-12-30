#include <SDF/SDF.hpp>

#include <iostream>

void onWindowResize(const sdf::WindowResizeEvent& e) {
    std::cout << "Window resized: (" << e.getWidth() << ", " << e.getHeight() << ")\n";
}

void onWindowMove(const sdf::WindowMoveEvent& e) {
    std::cout << "Window moved: (" << e.getX() << ", " << e.getY() << ")\n";
}

void onWindowEvent(const sdf::WindowEvent& e) {

    // Dispatch events we want to handle,
    // the dispatch method takes care of the event type checking
    e.dispatch<sdf::WindowMoveEvent>(onWindowMove);
    e.dispatch<sdf::WindowResizeEvent>(onWindowResize);

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
