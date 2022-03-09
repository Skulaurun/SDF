/*
* Copyright (c) 2021 Adam Charvát <https://www.skulaurun.eu>
* Licensed under the MIT License,
* for details see accompanying LICENSE file or a copy at
* <https://github.com/Skulaurun/SDF/blob/v1.0.0/LICENSE>.
* SPDX-License-Identifier: MIT
*/

#include <PCH.hpp>

#include <SDF/Graphics/Renderer.hpp>

#include <SDF/Graphics/Math.hpp>

#include <SDF/Graphics/OpenGL/IndexBuffer.hpp>
#include <SDF/Graphics/OpenGL/VertexBuffer.hpp>
#include <SDF/Graphics/OpenGL/VertexArray.hpp>

#include <SDF/Graphics/OpenGL/Shader.hpp>
#include <SDF/Graphics/OpenGL/Texture.hpp>

#include "OpenGL/OpenGL.hpp"

constexpr static uint32_t MAX_QUAD_COUNT = 10000;
constexpr static uint32_t MAX_TEXTURE_COUNT = 32;

constexpr static uint32_t VERTICES_PER_QUAD = 4;
constexpr static uint32_t INDICES_PER_QUAD = 6;

constexpr static uint32_t MAX_VERTEX_COUNT = MAX_QUAD_COUNT * VERTICES_PER_QUAD;
constexpr static uint32_t MAX_INDEX_COUNT = MAX_QUAD_COUNT * INDICES_PER_QUAD;

constexpr static const char* DEFAULT_VERTEX_SHADER = "#version 430 core\n"
    "layout (location = 0) in vec4 aPosition;\n"
    "layout (location = 1) in vec3 aColor;\n"
    "layout (location = 2) in vec2 aTextureCoordinate;\n"
    "layout (location = 3) in float aSamplerIndex;\n"
    "uniform mat4 uProjection;\n"
    "out vec3 vertexColor;\n"
    "out vec2 textureCoordinate;\n"
    "out float samplerIndex;\n"
    "void main() {\n"
    "   gl_Position = uProjection * aPosition;\n"
    "   vertexColor = aColor;\n"
    "   textureCoordinate = aTextureCoordinate;\n"
    "   samplerIndex = aSamplerIndex;\n"
    "}\n";

constexpr static const char* DEFAULT_FRAGMENT_SHADER = "#version 430 core\n"
    "layout (binding = 0) uniform sampler2D uSampler[32];\n"
    "out vec4 fragmentColor;\n"
    "in vec3 vertexColor;\n"
    "in vec2 textureCoordinate;\n"
    "in float samplerIndex;\n"
    "void main() {\n"
    "	fragmentColor = vec4(vertexColor, 1.0) * texture(uSampler[int(samplerIndex)], textureCoordinate);\n"
    "}\n";

namespace sdf {

    RendererStatistics Renderer::statistics = { 0, 0 };

    static uint32_t indexCount = 0;

    static Vertex* vertexPtr = nullptr;
    static std::unique_ptr<Vertex[]> vertices = nullptr;

    static uint32_t textureIndex = 1;
    static std::shared_ptr<Texture> defaultTexture = nullptr;
    static std::array<std::shared_ptr<Texture>, MAX_TEXTURE_COUNT> textures = {};

    std::stack<std::shared_ptr<Shader>> Renderer::shaders = {};
    std::stack<std::shared_ptr<Camera2D>> Renderer::cameras = {};

    static std::unique_ptr<VertexArray> vertexArray = nullptr;
    static std::shared_ptr<VertexBuffer> vertexBuffer = nullptr;
    static std::shared_ptr<IndexBuffer> indexBuffer = nullptr;

    bool Renderer::init() {

        if (!loadGLFunctions()) {
            //std::cerr << "Failed to initialize OpenGL!" << std::endl;
            return false;
        }

        if (vertexArray) {
            // ERROR: Renderer already initialized!
            return false;
        }

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        std::shared_ptr<Shader> shader = std::make_shared<Shader>(std::vector<ShaderSource>{
            { ShaderType::VertexShader, DEFAULT_VERTEX_SHADER },
            { ShaderType::FragmentShader, DEFAULT_FRAGMENT_SHADER }
        });

        uint32_t textureData = 0xffffffff;
        defaultTexture = std::make_shared<Texture>((uint8_t*)&textureData, 1, 1);
        textures[0] = defaultTexture;

        shaders.push(shader);
        shader->bind();

        // Not ideal solution
        std::shared_ptr<Camera2D> camera = std::make_shared<Camera2D>(0.0f, 1.0f, 1.0f, 0.0f);
        camera->setProjectionMatrix(Mat4f(1.0f));
        cameras.push(camera);

        vertices = std::make_unique<Vertex[]>(MAX_VERTEX_COUNT);

        vertexPtr = vertices.get();

        uint32_t* indices = new uint32_t[MAX_INDEX_COUNT];
        for (uint32_t i = 0, j = 0; i < MAX_INDEX_COUNT; i += 6, j += 4) {

            indices[i + 0] = j + 0;
            indices[i + 1] = j + 1;
            indices[i + 2] = j + 2;

            indices[i + 3] = j + 2;
            indices[i + 4] = j + 3;
            indices[i + 5] = j + 0;

        }

        indexBuffer = std::make_shared<IndexBuffer>(
            indices,
            MAX_INDEX_COUNT * (uint32_t)sizeof(uint32_t)
        );

        vertexBuffer = std::make_shared<VertexBuffer>(
            MAX_VERTEX_COUNT * (uint32_t)sizeof(Vertex)
        );

        vertexBuffer->setLayout({
            { VertexAttributeType::Float, 2 },
            { VertexAttributeType::Float, 4 },
            { VertexAttributeType::Float, 2 },
            { VertexAttributeType::Float, 1 }
        });

        vertexArray = std::make_unique<VertexArray>();
        vertexArray->setIndexBuffer(indexBuffer);
        vertexArray->addVertexBuffer(vertexBuffer);

        delete[] indices;

        return true;

    }

    void Renderer::clear(const Vec4f& color) {
        glClearColor(color.x, color.y, color.z, color.w);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    template<typename T>
    Vector4D<T> operator*(const Matrix4x4<T>& matrix, const Vector4D<T> vector) {
        return Vector4D<T>(
            matrix[0][0] * vector.x + matrix[1][0] * vector.y + matrix[2][0] * vector.z + matrix[3][0] * vector.w,
            matrix[0][1] * vector.x + matrix[1][1] * vector.y + matrix[2][1] * vector.z + matrix[3][1] * vector.w,
            matrix[0][2] * vector.x + matrix[1][2] * vector.y + matrix[2][2] * vector.z + matrix[3][2] * vector.w,
            matrix[0][3] * vector.x + matrix[1][3] * vector.y + matrix[2][3] * vector.z + matrix[3][3] * vector.w
        );
    }

    void Renderer::drawQuad(const Mat4f& transform, const Vec4f& color, const float samplerID) {

        constexpr static Vec4f quad[] = {
            { 0.0f, 0.0f, 0.0f, 1.0f },
            { 0.0f, 1.0f, 0.0f, 1.0f },
            { 1.0f, 1.0f, 0.0f, 1.0f },
            { 1.0f, 0.0f, 0.0f, 1.0f }
        };

        for (uint32_t i = 0; i < 4; i++) {
            vertexPtr->position = transform * quad[i];
            vertexPtr->color = color;
            vertexPtr->textureCoordinate = quad[i];
            vertexPtr->samplerID = samplerID;
            vertexPtr++;
        }

        indexCount += 6;
        statistics.quadCount += 1;

    }

    void Renderer::drawQuad(const Mat4f& transform, const std::shared_ptr<Texture>& texture, const Vec4f& color) {

        if (indexCount == MAX_INDEX_COUNT || textureIndex == MAX_TEXTURE_COUNT) {
            flush();
        }

        float samplerId = 0.0f;
        for (std::size_t i = 0; i < textures.size(); i++) {
            if (texture == textures[i]) {
                samplerId = i;
            }
        }

        if (samplerId == 0.0f) {
            samplerId = textureIndex;
            textures[textureIndex++] = texture;
        }

        drawQuad(transform, color, samplerId);

    }
    void Renderer::drawQuad(const Mat4f& transform, const Vec4f& color) {

        if (indexCount == MAX_INDEX_COUNT) {
            flush();
        }

        drawQuad(transform, color, 0.0f);

    }

    void Renderer::flush() {

        Vertex* dataPtr = vertices.get();
        uintptr_t dataSize = (uintptr_t)vertexPtr - (uintptr_t)dataPtr;

        vertexArray->bind();
        indexBuffer->bind();

        vertexBuffer->bind();
        vertexBuffer->update((float*)dataPtr, 0, (uint32_t)dataSize);

        auto& shader = shaders.top();
        shader->bind();

        auto& camera = cameras.top();
        shader->setUniform("uProjection", camera->getViewProjectionMatrix());

        for (std::size_t i = 0; i < textureIndex; i++) {
            textures[i]->bind(i);
        }

        glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, (const void*)0);

        statistics.batchCount += 1;
        vertexPtr = vertices.get();
        indexCount = 0;
        textureIndex = 1;

    }

    void Renderer::beginShader(const std::shared_ptr<Shader>& shader) {
        shaders.push(shader);
    }

    void Renderer::endShader() {
        shaders.pop();
    }

    void Renderer::beginCamera(const std::shared_ptr<Camera2D>& camera) {
        cameras.push(camera);
    }

    void Renderer::endCamera() {
        cameras.pop();
    }

    void Renderer::setViewport(const Vec2i& position, const Vec2u& size) {
        glViewport(position.x, position.y, size.x, size.y);
    }

}
