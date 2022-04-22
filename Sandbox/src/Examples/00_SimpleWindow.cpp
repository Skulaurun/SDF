/*
* Copyright (c) 2021 Adam Charvát <https://www.skulaurun.eu>
* Licensed under the MIT License,
* for details see accompanying LICENSE file or a copy at
* <https://github.com/Skulaurun/SDF/blob/v1.0.0/LICENSE>.
* SPDX-License-Identifier: MIT
*/

#include <SDF/SDF.hpp>

int doExample00() {

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
