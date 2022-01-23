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
