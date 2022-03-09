/*
* Copyright (c) 2021 Adam Charvát <https://www.skulaurun.eu>
* Licensed under the MIT License,
* for details see accompanying LICENSE file or a copy at
* <https://github.com/Skulaurun/SDF/blob/v1.0.0/LICENSE>.
* SPDX-License-Identifier: MIT
*/

#include <PCH.hpp>
#include <SDF/Network/Network.hpp>

namespace sdf::net {

    bool init() {

        struct Cleaner {
            ~Cleaner() {
                ::WSACleanup();
            }
        };

        static WSADATA wsaData = {};

        if (wsaData.wVersion == NULL) {

            static constexpr uint32_t version[2] = { 2, 2 }; // Consider removing static

            int32_t result = ::WSAStartup(MAKEWORD(version[0], version[1]), &wsaData);
            if (result != 0 || LOBYTE(wsaData.wVersion) != version[0] || HIBYTE(wsaData.wVersion) != version[1]) { // Memory leak, if success but wrong version
                return false;
            }

            static Cleaner cleaner;

        }
        
        return true;

    }

}
