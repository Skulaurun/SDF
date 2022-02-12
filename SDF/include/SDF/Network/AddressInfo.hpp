#pragma once

#include <cstdint>
#include <string>
#include <vector>

typedef struct addrinfo addrinfo;
typedef struct sockaddr sockaddr;
typedef struct sockaddr_storage sockaddr_storage;

namespace sdf {

	enum class AddressFamily {
		None, IPv4, IPv6
	};

	struct AddressNode {

		AddressFamily family;
		std::string address;

		AddressNode(const AddressFamily family, const std::string& address, sockaddr* storage)
			: family(family), address(address), storage(storage) {}

	private:
		friend class Socket;
		sockaddr* storage;

	};

	class AddressInfo {

	public:
		AddressInfo(const std::string& address, const uint16_t port);
		AddressInfo(const std::string& address, const std::string& port);
		virtual ~AddressInfo();

		const uint16_t getPort() const { return port; }
		const AddressNode& getAddress() const { return addressList.front(); }

		const std::vector<AddressNode>& getAddressList() const { return addressList; }

	private:
		uint16_t port;
		std::vector<AddressNode> addressList;

		addrinfo* addressInfo;

	};

}
