/*
* Copyright (c) 2021 Adam Charvát <https://www.skulaurun.eu>
* Licensed under the MIT License,
* for details see accompanying LICENSE file or a copy at
* <https://github.com/Skulaurun/SDF/blob/v1.0.0/LICENSE>.
* SPDX-License-Identifier: MIT
*/

#pragma once

#include <SDF/Graphics/RendererObject.hpp>

#include <cstdint>

namespace sdf {

    enum class BufferType : uint8_t {
        IndexBuffer, VertexBuffer
    };

    template<typename TData, BufferType TBuffer>
    class Buffer : public RendererObject {

    public:
        Buffer(const uint32_t size);
        Buffer(const TData* data, const uint32_t size);
        virtual ~Buffer();

        void bind() const override;
        void unbind() const override;

        void update(const TData* data, const uint32_t offset, const uint32_t size) const;

    };

}
