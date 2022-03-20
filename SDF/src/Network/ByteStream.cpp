/*
* Copyright (c) 2021 Adam Charvát <https://www.skulaurun.eu>
* Licensed under the MIT License,
* for details see accompanying LICENSE file or a copy at
* <https://github.com/Skulaurun/SDF/blob/v1.0.0/LICENSE>.
* SPDX-License-Identifier: MIT
*/

#include <PCH.hpp>
#include <SDF/Network/ByteStream.hpp>

// Note that this implementation is not ideal,
// too many allocations, performance impact.

// TODO:
// Do not reallocate on each write and
// replace the erase (another reallocation) in read
// with handle and seeking?

namespace sdf {

    ByteStream::ByteStream(const std::size_t size) {
        resize(size);
    }

    ByteStream::ByteStream(const void* data, const std::size_t size) {
        resize(size);
        std::memcpy(buffer.data(), data, size);
    }

    void ByteStream::write(Serializable& object) {
        object.write(*this);
    }

    void ByteStream::read(Serializable& object) {
        object.read(*this);
    }

    void ByteStream::write(const char* data, const std::size_t size) {
        std::size_t offset = buffer.size();
        buffer.resize(offset + size); // Is this too performance heavy?
        std::memcpy(buffer.data() + offset, data, size);
    }

    void ByteStream::read(char* data, const std::size_t size) {
        std::memcpy(data, buffer.data(), size);
        erase(size);
    }

    void ByteStream::clear() {
        buffer.clear();
    }

    void ByteStream::erase(const std::size_t size) {
        buffer.erase(buffer.begin(), buffer.begin() + size);
    }

    void ByteStream::resize(const std::size_t size) {
        buffer.resize(size);
    }

    void ByteStream::shift(const std::size_t offset) {
        std::memmove(buffer.data() + offset, buffer.data(), buffer.size() - offset);
        std::memset(buffer.data(), 0, offset);
    }

}
