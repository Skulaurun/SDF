/*
* Copyright (c) 2021 Adam Charvát <https://www.skulaurun.eu>
* Licensed under the MIT License,
* for details see accompanying LICENSE file or a copy at
* <https://github.com/Skulaurun/SDF/blob/v1.0.0/LICENSE>.
* SPDX-License-Identifier: MIT
*/

#include <PCH.hpp>
#include <SDF/Network/AddressInfo.hpp>

namespace sdf {

    static constexpr AddressFamily toAddressFamily(const int32_t type) {
        switch (type) {
            case 0: return AddressFamily::None;
            case AF_INET: return AddressFamily::IPv4;
            case AF_INET6: return AddressFamily::IPv6;
            default: throw "UNSUPPORTED TYPE";
        }
    }

    AddressInfo::AddressInfo(const std::string& address, const std::string& port) {

        const char* nodeName = address.c_str();
        const char* serviceName = port.c_str();
        
        if (::getaddrinfo(nodeName, serviceName, NULL, &addressInfo) != 0) {
            // Error
        }

        this->port = ntohs(SS_PORT(addressInfo->ai_addr));
        for (addrinfo* ptr = addressInfo; ptr != NULL; ptr = ptr->ai_next) {
        
            AddressFamily family = toAddressFamily(ptr->ai_family);
        
            std::string address(NI_MAXHOST, '\0');
            if (getnameinfo(ptr->ai_addr, ptr->ai_addrlen, address.data(), address.size(), NULL, 0, NI_NUMERICHOST) == 0) {
                // error
            }

            addressList.push_back({ family, address, ptr->ai_addr });
        
        }

    }

    AddressInfo::AddressInfo(const std::string& address, const uint16_t port)
        : AddressInfo(address, std::to_string(port)) {}

    AddressInfo::~AddressInfo() {
        ::freeaddrinfo(addressInfo);
    }

}
