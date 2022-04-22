/*
* Copyright (c) 2021 Adam Charvát <https://www.skulaurun.eu>
* Licensed under the MIT License,
* for details see accompanying LICENSE file or a copy at
* <https://github.com/Skulaurun/SDF/blob/v1.0.0/LICENSE>.
* SPDX-License-Identifier: MIT
*/

#include "Examples/Examples.hpp"

#include <string>
#include <iostream>

#include <windows.h>

#pragma execution_character_set("utf-8")

int main() {

    SetConsoleOutputCP(65001);

    std::cout << ">>> [ SDF EXAMPLES ] <<<\n" << std::endl;
    std::cout << "> Made with SDF (https://github.com/Skulaurun/SDF)" << std::endl;
    std::cout << "> Copyright (c) 2022 Adam Charvát" << std::endl;
    std::cout << std::endl;

    std::cout << "[0]: Simple Window" << std::endl;
    std::cout << "[1]: Window Events" << std::endl;
    std::cout << "[2]: Graphics Rendering" << std::endl;
    std::cout << "[3]: Socket Networking" << std::endl;
    std::cout << std::endl;

    std::cout << "Type 'q' to exit." << std::endl;
    std::cout << std::endl;

    std::string line = "";
    while (line != "q") {

        int example = 0;
        std::cout << "Run an example [0 - 3]: ";
        std::getline(std::cin, line);

        try {
            example = std::stoi(line);
        } catch (const std::exception&) { continue; }

        try {

            int exit = 0;
            switch (example) {
                case 0: exit = doExample00(); break;
                case 1: exit = doExample01(); break;
                case 2: exit = doExample02(); break;
                case 3: exit = doExample03(); break;
                default: continue;
            }

            std::cout << std::endl << "Example (#" << example << ") exited with code " << exit << "." << std::endl;

        } catch (const std::exception& e) {
            std::cout << std::endl << "An exception occurred while running an example (#" << example << "): " << e.what() << std::endl;
        }

        std::cout << std::endl;

    }

    return 0;

}
