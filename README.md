# Simple Dedicated Framework (SDF)

A framework **dedicated** to operating system Windows, **simple** easy to use API.

### Example of Window creation
```cpp
#include <SDF/SDF.hpp>

int main() {

    // Create the window
    sdf::Window window(L"Sandbox App", 800, 600);

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
```
