/*
* Copyright (c) 2021 Adam Charvát <https://www.skulaurun.eu>
* Licensed under the MIT License,
* for details see accompanying LICENSE file or a copy at
* <https://github.com/Skulaurun/SDF/blob/v1.0.0/LICENSE>.
* SPDX-License-Identifier: MIT
*/

#include <PCH.hpp>
#include <SDF/Network/Network.hpp>
#include <SDF/Core/Exception.hpp>

#include <string>

constexpr auto NETWORK_VERSION = MAKEWORD(2, 2);

namespace sdf {

    /*
        Translation taken from: https://docs.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-wsastartup#return-value
    */

    static const char* translateError(const int code) {
        switch (code) {
            case WSASYSNOTREADY: return "The underlying network subsystem is not ready for network communication.";
            case WSAVERNOTSUPPORTED: return "The version of Windows Sockets support requested is not provided by this particular Windows Sockets implementation.";
            case WSAEINPROGRESS: return "A blocking Windows Sockets 1.1 operation is in progress.";
            case WSAEPROCLIM: return "A limit on the number of tasks supported by the Windows Sockets implementation has been reached.";
            case WSAEFAULT: return "The lpWSAData parameter is not a valid pointer.";
            default: return "Unknown WSAStartup error code.";
        }
    }

    void initNetwork() {

        struct Cleaner {
            ~Cleaner() {
                ::WSACleanup();
            }
        };

        static WSADATA wsaData = {};

        if (wsaData.wVersion == NULL) {

            int result = ::WSAStartup(NETWORK_VERSION, &wsaData);
            if (result != 0) {
                // TODO: Use FormatMessage instead?
                throw SystemException(translateError(result), result);
            }

            static Cleaner cleaner;

            if (LOBYTE(wsaData.wVersion) != LOBYTE(NETWORK_VERSION) || HIBYTE(wsaData.wVersion) != HIBYTE(NETWORK_VERSION)) {
                throw Exception("Could not find usable version of Winsock 2.");
            }

        }

    }

}
