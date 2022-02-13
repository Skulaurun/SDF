#pragma once

#include "../Core/WinTypes.hpp"
#include "AddressInfo.hpp"

#include <tuple>
#include <memory>

typedef struct sockaddr sockaddr;

namespace sdf {

    enum class NetworkProtocol {
        TCP, UDP
    };

    struct Endpoint {

        uint16_t port;
        std::string address;

        friend std::ostream& operator<<(std::ostream& o, const Endpoint& endpoint);

    };

    class Socket {

    public:
        Socket(const NetworkProtocol protocol);
        Socket(const SOCKET socket);
        virtual ~Socket();
        
        void bind(const uint16_t port);
        void bind(const sdf::AddressInfo& info);

        void connect(const sdf::AddressInfo& info);
        void listen();

        void send(const char* buffer, const std::size_t length) const;
        bool receive(char* buffer, const std::size_t length) const;

        Endpoint getLocalEndpoint() const;
        Endpoint getRemoteEndpoint() const;

        std::tuple<std::shared_ptr<Socket>, Endpoint> accept() const;

    private:
        void bind(sockaddr* address, int32_t length) const;
        Endpoint getNameInfo(sockaddr* info, int32_t length) const;

    private:
        SOCKET socket;

    };

}
