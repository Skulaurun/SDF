# Simple Dedicated Framework (SDF)

[![build](https://github.com/Skulaurun/SDF/actions/workflows/msbuild.yml/badge.svg?branch=main)](https://github.com/Skulaurun/SDF/actions/workflows/msbuild.yml)
[![release](https://img.shields.io/github/v/release/Skulaurun/SDF)](https://github.com/Skulaurun/SDF/releases/latest)
[![license](https://img.shields.io/github/license/Skulaurun/SDF?color=blue)](https://github.com/Skulaurun/SDF/blob/main/LICENSE)

A framework **dedicated** to operating system Windows, **simple** easy to use API. Including the abstraction of Windowing, OpenGL 3.0+ graphics and a bit of networking.

I am 18 y/o (born 2003) developer, I made this framework as a graduation project (for "Maturita exam"). It was a great experience and I learned A LOT. I hope that someone, somewhere, someday might find this and create something nice with it.

❗ Note that SDF is meant to be used as a static library, no dll support planned.

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

### Overriding the default event handler
```cpp
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
```

## Using pre-compiled binaries

To support wider range of MSVC compiler versions, the pre-compiled binaries are built without **Whole Program Optimization**. The `/GL` and `/LTGC` compiler switches are omitted for deploy builds (`DebugDeploy` and `ReleaseDeploy`) in SDF project configuration.

If you don't want to build SDF yourself, which is strongly recommended and encouraged, then follow these steps after downloading the precompiled binaries for one or both platform architectures. The binaries are distributed with `lib` and `include` folders inside the `.zip`. Extract the archive somewhere (where you keep libraries, etc.) and make references to these folders from your app's VS project configuration.

📢 Before configuring Visual Studio project, make sure that you have the right `Configuration` and `Platform` selected at the top of the project properties window.

1. Link statically to the C++ runtime library via `/MT` (for release) or `/MTd` (for debug) switches.
```
Project > Properties > C/C++ > Code Generation > Runtime Library
```
2. Add path to SDF `include` folder (public interface headers) into `Additional Include Directories`.
```
Project > Properties > C/C++ > General > Additional Include Directories
```
3. Use correct `.lib` for each architecture (`x86` or `x64`) by specifying appropriate SDF `lib` folder path.
```
Project > Properties > Linker > General > Additional Library Directories
```
4. Add `SDF.lib` to MSVC Linker input.
```
Project > Properties > Linker > Input > Additional Dependencies
```
5. Run SDF!

## How to build

The preferred (and only tested) compiler is MSVC. Download the source from GitHub and build either from command line (`msbuild`) or use Visual Studio's GUI.
You probably want to use the configurations `Debug` or `Release`, not the `...Deploy` ones. As noted above, deploy builds have disabled whole program optimization.

### Build Requiremenets
⚠️ Warning: SDF is Windows only!
- C++ 17 or 20
- Visual Studio 2022 (v17)

### From GUI

- Open the solution file `SDF.sln` (or `SDF.vcxproj` directly).
- At the top of the IDE's window ```Build > Build Solution```.

The output files are written to `$(SolutionDir)/build` folder.

## License

The project is licensed under the MIT License. See [LICENSE](https://github.com/Skulaurun/SDF/blob/v1.0.0/LICENSE) for details.
