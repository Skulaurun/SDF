/*
* Copyright (c) 2021 Adam Charvát <https://www.skulaurun.eu>
* Licensed under the MIT License,
* for details see accompanying LICENSE file or a copy at
* <https://github.com/Skulaurun/SDF/blob/v1.0.0/LICENSE>.
* SPDX-License-Identifier: MIT
*/

#include <PCH.hpp>
#include <SDF/Core/Exception.hpp>
#include <SDF/Network/Socket.hpp>

#include "Core/WinError.hpp"

#pragma comment (lib, "Ws2_32.lib")

#define WSA_THROW() { \
    WinError error = WinError::getLastWSAError(); \
    throw NetworkException(error.message, error.code); \
}

#define WSA_ASSERT(x) \
    if (!(x)) { \
        WSA_THROW(); \
    }

namespace sdf {

    static constexpr int32_t toNativeProtocol(const NetworkProtocol type) {
        switch (type) {
            case NetworkProtocol::TCP: return IPPROTO_TCP;
            case NetworkProtocol::UDP: return IPPROTO_UDP;
            default: throw "UNSUPPORTED TYPE";
        }
    }

    Socket::Socket(SOCKET socket)
        : socket(socket) {}

    Socket::Socket(const NetworkProtocol protocol) {

        int32_t socketType = -1;
        switch (protocol) {
            case NetworkProtocol::UDP: socketType = SOCK_DGRAM; break;
            case NetworkProtocol::TCP: socketType = SOCK_STREAM; break;
        }

        socket = ::socket(AF_UNSPEC, socketType, toNativeProtocol(protocol));
        WSA_ASSERT(socket != INVALID_SOCKET);

    }

    Socket::~Socket() {
        close();
    }

    void Socket::bind(const uint16_t port) {

        sockaddr_in address = {};
        address.sin_family = AF_INET;
        address.sin_port = htons(port);

        bind((sockaddr*)&address, sizeof(sockaddr_in));

    }

    void Socket::bind(const sdf::AddressInfo& info) {

        const AddressNode& address = info.getAddress();

        bind(address.storage, sizeof(sockaddr_storage));

    }
    
    void Socket::bind(sockaddr* address, int32_t length) const {
        WSA_ASSERT(::bind(socket, address, length) != SOCKET_ERROR);
    }

    void Socket::connect(const sdf::AddressInfo& info) {

        for (const auto& address : info.getAddressList()) {
            if (::connect(socket, address.storage, sizeof(sockaddr_storage)) != SOCKET_ERROR) {
                return;
            }
        }

        WSA_THROW();

    }

    void Socket::listen() {
        WSA_ASSERT(::listen(socket, SOMAXCONN) != SOCKET_ERROR);
    }

    void Socket::send(const char* buffer, const std::size_t length) const {
        WSA_ASSERT(::send(socket, buffer, length, 0) != SOCKET_ERROR);
    }

    bool Socket::receive(char* buffer, const std::size_t length) const {

        int32_t result = ::recv(socket, buffer, length, 0);
        if (result == 0) {
            return false;
        } else if (result < 0) {
            WSA_THROW();
            return false;
        }

        return true;

    }

    void Socket::close() {
        ::closesocket(socket);
    }

    Endpoint Socket::getLocalEndpoint() const {

        sockaddr_storage storage = {};
        int32_t length = sizeof(sockaddr_storage);
        WSA_ASSERT(getsockname(socket, (sockaddr*)&storage, &length) != SOCKET_ERROR);

        return getNameInfo((sockaddr*)&storage, length);

    }

    Endpoint Socket::getRemoteEndpoint() const {

        sockaddr_storage storage = {};
        int32_t length = sizeof(sockaddr_storage);
        WSA_ASSERT(getpeername(socket, (sockaddr*)&storage, &length) != SOCKET_ERROR);

        return getNameInfo((sockaddr*)&storage, length);

    }

    Endpoint Socket::getNameInfo(sockaddr* info, int32_t length) const {

        uint16_t port = ntohs(SS_PORT(info));
        std::string address(NI_MAXHOST, '\0');
        WSA_ASSERT(getnameinfo(info, length, address.data(), (DWORD)address.size(), NULL, 0, NI_NUMERICHOST) == 0);

        return { port, address };

    }

    std::tuple<std::shared_ptr<Socket>, Endpoint> Socket::accept() const {

        sockaddr_storage storage = {};
        int32_t length = sizeof(sockaddr_storage);

        SOCKET client = ::accept(socket, (sockaddr*)&storage, &length);
        WSA_ASSERT(client != INVALID_SOCKET);

        return {
            std::make_shared<Socket>(client),
            getNameInfo((sockaddr*)&storage, length)
        };

    }

    std::ostream& operator<<(std::ostream& o, const Endpoint& endpoint) {
        return o << endpoint.address << ":" << endpoint.port;
    }

}
