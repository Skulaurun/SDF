#include <SDF/Graphics/Renderer.hpp>

#include <SDF/Graphics/Math.hpp>

#include <SDF/Graphics/OpenGL/IndexBuffer.hpp>
#include <SDF/Graphics/OpenGL/VertexBuffer.hpp>
#include <SDF/Graphics/OpenGL/VertexArray.hpp>

#include <SDF/Graphics/OpenGL/Shader.hpp>

#include "OpenGL/OpenGL.hpp"

#include <memory>

constexpr static uint32_t MAX_QUAD_COUNT = 10000;
constexpr static uint32_t MAX_TEXTURE_COUNT = 32;

constexpr static uint32_t VERTICES_PER_QUAD = 4;
constexpr static uint32_t INDICES_PER_QUAD = 6;

constexpr static uint32_t MAX_VERTEX_COUNT = MAX_QUAD_COUNT * VERTICES_PER_QUAD;
constexpr static uint32_t MAX_INDEX_COUNT = MAX_QUAD_COUNT * INDICES_PER_QUAD;

constexpr static const char* DEFAULT_VERTEX_SHADER = "#version 430 core\n"
    "layout (location = 0) in vec4 aPosition;\n"
    "layout (location = 1) in vec3 aColor;\n"
    "uniform mat4 uProjection;\n"
    "out vec3 vertexColor;\n"
    "void main() {\n"
    "   gl_Position = uProjection * aPosition;\n"
    "   vertexColor = aColor;\n"
    "}\n";

constexpr static const char* DEFAULT_FRAGMENT_SHADER = "#version 430 core\n"
    "out vec4 fragmentColor;\n"
    "in vec3 vertexColor;\n"
    "void main() {\n"
    "	fragmentColor = vec4(vertexColor, 1.0);\n"
    "}\n";


namespace sdf {

    RendererStatistics Renderer::statistics = { 0, 0 };
    
    static uint32_t indexCount = 0;
    
    static Vertex* vertexPtr = nullptr;
    static std::unique_ptr<Vertex[]> vertices = nullptr;
    
    static uint32_t textureIndex = 0;
    //static UPtr<SPtr<Texture>[]> textures = nullptr;

    static std::unique_ptr<Shader> shader = nullptr;
    
    static std::unique_ptr<VertexArray> vertexArray = nullptr;
    static std::shared_ptr<VertexBuffer> vertexBuffer = nullptr;
    static std::shared_ptr<IndexBuffer> indexBuffer = nullptr;

    bool Renderer::init() {

        if (!initGL()) {
            //std::cerr << "Failed to initialize OpenGL!" << std::endl;
            return false;
        }

        if (vertexArray) {
            // ERROR: Renderer already initialized!
            return false;
        }

        shader = std::make_unique<Shader>(std::vector<ShaderSource>{
            { ShaderType::VertexShader, DEFAULT_VERTEX_SHADER },
            { ShaderType::FragmentShader, DEFAULT_FRAGMENT_SHADER }
        });

        shader->bind();

        sdf::Mat4f projection = sdf::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);
        shader->setUniform("uProjection", projection);

        vertices = std::make_unique<Vertex[]>(MAX_VERTEX_COUNT);
        //textures = UPtr<SPtr<Texture>[]>::create(MAX_TEXTURE_COUNT);
        
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
            { VertexAttributeType::Float, 4 }
        });

        vertexArray = std::make_unique<VertexArray>();
        vertexArray->setIndexBuffer(indexBuffer);
        vertexArray->addVertexBuffer(vertexBuffer);

        delete[] indices;

    }
    
    void Renderer::clear(const Vec4f& color) {
        glClearColor(color.x, color.y, color.z, color.w);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    template<typename T>
    Vector4D<T> operator*(const Matrix4x4<T>& matrix, const Vector4D<T> vector) {
        return Vector4D<T>(
            matrix[0][0] * vector.x + matrix[3][0],
            matrix[1][1] * vector.y + matrix[3][1],
            matrix[2][2] * vector.z + matrix[3][2],
            matrix[3][3] * vector.w + matrix[3][3]
        );
    }
    
    void Renderer::drawQuad(const Mat4f& transform, const Vec4f& color) {
    
        if (indexCount == MAX_INDEX_COUNT) {
            //endBatch();
            //beginBatch();
            flush();
        }
    
        /*if (std::find(std::begin(textures), std::end(textures), texture) != std::end(textures)) {
    
        }*/
    
        constexpr static Vec4f quad[] = {
            { 0.0f, 0.0f, 0.0f, 1.0f },
            { 0.0f, 1.0f, 0.0f, 1.0f },
            { 1.0f, 1.0f, 0.0f, 1.0f },
            { 1.0f, 0.0f, 0.0f, 1.0f }
        };
    
        for (uint32_t i = 0; i < 4; i++) {
            vertexPtr->position = transform * quad[i];
            vertexPtr->color = color;
            //vertexPtr->textureCoordinate = quad[i];
            //vertexPtr->samplerID = 0.0f;
            vertexPtr++;
        }
    
        indexCount += 6;
        statistics.quadCount += 1;
    
    }
    void Renderer::flush() {
    
        Vertex* dataPtr = vertices.get();
        uint32_t dataSize = (uint32_t)vertexPtr - (uint32_t)dataPtr;

        vertexArray->bind();
        indexBuffer->bind();

        vertexBuffer->bind();
        vertexBuffer->update((float*)dataPtr, 0, dataSize);

        shader->bind();

        glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, (const void*)0);

        statistics.batchCount += 1;

        vertexPtr = vertices.get();
        indexCount = 0;
    
    }

    void Renderer::setViewport(const Vec2f& position, const Vec2f& size) {
        glViewport(position.x, position.y, size.x, size.y);
    }

}
