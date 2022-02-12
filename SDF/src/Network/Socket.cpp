#include <PCH.hpp>
#include <SDF/Network/Socket.hpp>

#pragma comment (lib, "Ws2_32.lib")

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
		if (socket == INVALID_SOCKET) {
			// error
		}

	}

	Socket::~Socket() {
		::closesocket(socket);
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

		if (::bind(socket, address, length) == SOCKET_ERROR) {
			// error
		}

	}

	void Socket::connect(const sdf::AddressInfo& info) {

		for (const auto& address : info.getAddressList()) {

			if (::connect(socket, address.storage, sizeof(sockaddr_storage)) != SOCKET_ERROR) {
				return;
			}

		}

		// throw an error

	}

	void Socket::listen() {

		if (::listen(socket, SOMAXCONN) == SOCKET_ERROR) {
			// error
		}

	}

	Endpoint Socket::getLocalEndpoint() const {

		sockaddr_storage storage = {};
		int32_t length = sizeof(sockaddr_storage);
		
		if (getsockname(socket, (sockaddr*)&storage, &length) == SOCKET_ERROR) {
			// error
		}

		return getNameInfo((sockaddr*)&storage, length);

	}

	Endpoint Socket::getRemoteEndpoint() const {

		sockaddr_storage storage = {};
		int32_t length = sizeof(sockaddr_storage);

		if (getpeername(socket, (sockaddr*)&storage, &length) == SOCKET_ERROR) {
			// error
		}

		return getNameInfo((sockaddr*)&storage, length);

	}

	Endpoint Socket::getNameInfo(sockaddr* info, int32_t length) const {

		uint16_t port = ntohs(SS_PORT(info));
		std::string address(NI_MAXHOST, '\0');
		if (getnameinfo(info, length, address.data(), address.size(), NULL, 0, NI_NUMERICHOST) == 0) {
			// error
		}

		return { port, address };

	}

	std::tuple<std::shared_ptr<Socket>, Endpoint> Socket::accept() const {

		sockaddr_storage storage = {};
		int32_t length = sizeof(sockaddr_storage);

		SOCKET client = ::accept(socket, (sockaddr*)&storage, &length);
		if (client == INVALID_SOCKET) {
			// error
		}

		return {
			std::make_shared<Socket>(client),
			getNameInfo((sockaddr*)&storage, length)
		};

	}

	std::ostream& operator<<(std::ostream& o, const Endpoint& endpoint) {
		return o << endpoint.address << ":" << endpoint.port;
	}

}
