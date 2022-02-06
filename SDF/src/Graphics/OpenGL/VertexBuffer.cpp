#include <PCH.hpp>

#include <SDF/Graphics/OpenGL/VertexBuffer.hpp>

#include "OpenGL.hpp"
#include "OpenGLEnum.hpp"

namespace sdf {

    using SDFVertexAttribPointer = void (__stdcall*)(GLuint, GLint, GLenum, GLboolean, GLsizei, uintptr_t);

    void VertexBuffer::setLayout(const std::vector<VertexBufferAttribute>& layout) {

        attributeLayout = layout;
        attributeStride = 0;

        uint32_t offset = 0;
        for (auto& attribute : attributeLayout) {

            attribute.offset = offset;
            attribute.size = attribute.count * TYPE_SIZE(attribute.type);

            offset += attribute.size;
            attributeStride += attribute.size;

        }

    }

    void VertexBuffer::enableLayout(uint32_t& attributeOffset) const {

        bind();

        for (const auto& attribute : attributeLayout) {

            ((SDFVertexAttribPointer)glVertexAttribPointer)(
                attributeOffset,
                attribute.count,
                TO_NATIVE_ENUM(attribute.type),
                attribute.normalized ? GL_TRUE : GL_FALSE,
                attributeStride,
                attribute.offset
            );
            
            glEnableVertexAttribArray(attributeOffset++);

        }

    }

}
