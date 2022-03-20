/*
* Copyright (c) 2021 Adam Charvát <https://www.skulaurun.eu>
* Licensed under the MIT License,
* for details see accompanying LICENSE file or a copy at
* <https://github.com/Skulaurun/SDF/blob/v1.0.0/LICENSE>.
* SPDX-License-Identifier: MIT
*/

#pragma once

#include <vector>

namespace sdf {

    class ByteStream;

    class Serializable {

    public:
        virtual ~Serializable() = default;

        virtual ByteStream& write(ByteStream& stream) = 0;
        virtual ByteStream& read(ByteStream& stream) = 0;

    };

    // TODO: Implement void serialize() for primitives and STL types

    class ByteStream {

    public:
        ByteStream() = default;
        ByteStream(const std::size_t size);
        ByteStream(const void* data, const std::size_t size);

        void write(Serializable& object);
        void read(Serializable& object);

        void write(const char* data, const std::size_t size);
        void read(char* data, const std::size_t size);

        void clear();
        void erase(const std::size_t size);
        void resize(const std::size_t size);
        void shift(const std::size_t offset);
    
        // Function names consistent with STL
        bool empty() const { return buffer.empty(); }
        const char* data() const { return buffer.data(); }
        std::size_t size() const { return buffer.size(); }

    private:
        std::vector<char> buffer;

    };

}
