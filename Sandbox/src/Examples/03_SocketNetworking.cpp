/*
* Copyright (c) 2021 Adam Charvát <https://www.skulaurun.eu>
* Licensed under the MIT License,
* for details see accompanying LICENSE file or a copy at
* <https://github.com/Skulaurun/SDF/blob/v1.0.0/LICENSE>.
* SPDX-License-Identifier: MIT
*/

#include <SDF/SDF.hpp>

#include <iostream>

int doExample03() {

    // Select mode (client or server)
    std::string mode = "";
    do {
        std::cout << "Enter mode [client;server]: ";
        std::getline(std::cin, mode);
    } while (mode != "client" && mode != "server");

    std::cout << std::endl;

    if (mode == "client") {

        // Create TCP socket
        sdf::Socket socket(sdf::NetworkProtocol::TCP);

        // Connect to server at localhost:5000
        socket.connect(sdf::AddressInfo("localhost", 5000));

        // Get server's remote address
        std::cout << "Connected to the server at '" << socket.getRemoteEndpoint() << "'.\n\n";

        // Send message to the server
        const char* message = "Hello from client.";
        socket.send(message, strlen(message));

        // Receive message from the server
        char buffer[256] = {};
        socket.receive(buffer, sizeof(buffer));

        std::cout << "Message from server: " << buffer << std::endl;

    } else if (mode == "server") {

        // Create TCP socket
        sdf::Socket socket(sdf::NetworkProtocol::TCP);

        // Bind the server to port 5000
        socket.bind(5000);

        // Start listening for incoming connections
        socket.listen();

        // Get local server address
        std::cout << "Server listening on '" << socket.getLocalEndpoint() << "'.\n\n";

        // Accept client (note that this call is blocking)
        auto [client, endpoint] = socket.accept();
        std::cout << endpoint << " connected to the server.\n" << std::endl;

        // Receive message from client
        char buffer[256] = {};
        client->receive(buffer, sizeof(buffer));

        std::cout << "Message from client: " << buffer << std::endl;

        // Send message to client
        const char* message = "Hello from server.";
        client->send(message, strlen(message));

    }

    return 0;

}
