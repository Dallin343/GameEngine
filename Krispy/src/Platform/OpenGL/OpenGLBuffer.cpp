//
// Created by dallin on 8/20/20.
//

#include "OpenGLBuffer.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Krispy {
#pragma mark --Uniform Buffer Utilities--
    static std::tuple<uint32_t, uint32_t> UniformBaseAlignment(ShaderDataType type) {
        const uint32_t std140N = 4;
        switch (type) {
            case ShaderDataType::Bool:
            case ShaderDataType::Int:
            case ShaderDataType::Float: return {1 * std140N, 1};

            case ShaderDataType::Int2:
            case ShaderDataType::Float2: return {2 * std140N, 1};

            case ShaderDataType::Int3:
            case ShaderDataType::Float3:
            case ShaderDataType::Int4:
            case ShaderDataType::Float4: return {4 * std140N, 1};

            case ShaderDataType::Mat3:  return {4 * std140N, 3};
            case ShaderDataType::Mat4:  return {4 * std140N, 4};

            default:
                return {0, 0};
        }
    }

#pragma mark --OpenGLVertexBuffer--
    OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size) {
        KRISPY_PROFILE_FUNCTION();

        glCreateBuffers(1, &m_RendererID);

        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
        glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
    }

    OpenGLVertexBuffer::OpenGLVertexBuffer(float *vertices, uint32_t size) {
        KRISPY_PROFILE_FUNCTION();

        glCreateBuffers(1, &m_RendererID);

        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer() {
        KRISPY_PROFILE_FUNCTION();

        glDeleteBuffers(1, &m_RendererID);
    }

    void OpenGLVertexBuffer::Bind() const {
        KRISPY_PROFILE_FUNCTION();

        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    }

    void OpenGLVertexBuffer::Unbind() const {
        KRISPY_PROFILE_FUNCTION();

        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void OpenGLVertexBuffer::SetData(const void *data, uint32_t size) {
        KRISPY_PROFILE_FUNCTION();

        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
        glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
    }

#pragma mark --OpenGLIndexBuffer--
    OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t *indices, uint32_t count) : m_Count(count) {
        KRISPY_PROFILE_FUNCTION();

        glCreateBuffers(1, &m_RendererID);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
    }

    OpenGLIndexBuffer::~OpenGLIndexBuffer() {
        KRISPY_PROFILE_FUNCTION();

        glDeleteBuffers(1, &m_RendererID);
    }

    void OpenGLIndexBuffer::Bind() const {
        KRISPY_PROFILE_FUNCTION();

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    }

    void OpenGLIndexBuffer::Unbind() const {
        KRISPY_PROFILE_FUNCTION();

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

#pragma mark --OpenGLUniformBuffer--
    OpenGLUniformBuffer::OpenGLUniformBuffer(std::initializer_list<BufferElement> &elements) : m_RendererID(0) {
        KRISPY_PROFILE_FUNCTION();
        CreateLayout(elements);

        glCreateBuffers(1, &m_RendererID);
        glBindBuffer(GL_UNIFORM_BUFFER, m_RendererID);
        glBufferData(GL_UNIFORM_BUFFER, m_Size, nullptr, GL_STATIC_DRAW);
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
    }

    void OpenGLUniformBuffer::SetLayout(std::initializer_list<BufferElement> &elements) {
        CreateLayout(elements);
    }

    void OpenGLUniformBuffer::CreateLayout(std::initializer_list<BufferElement> &elements) {
        KRISPY_PROFILE_FUNCTION();

        std::unordered_map<std::string, BufferElement> elementMap;
        uint32_t offset = 0;
        for (auto element : elements) {
            auto [baseAlign, count] = UniformBaseAlignment(element.Type);

            element.Size = baseAlign * count;
            m_Size += element.Size;

            //Align to boundary
            if (offset % baseAlign != 0)
                offset += (baseAlign - (offset % baseAlign));

            element.Offset = offset;
            elementMap[element.Name] = element;

            //Advance offset to end of element
            offset += (baseAlign * count);
        }

        m_Layout.SetElements(elementMap);
    }

    void OpenGLUniformBuffer::Bind() const {
        glBindBuffer(GL_UNIFORM_BUFFER, m_RendererID);
    }

    void OpenGLUniformBuffer::Unbind() const {
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
    }

    void OpenGLUniformBuffer::BindShader(const std::string &uniformBlockName, const Ref <Shader> &shader,
                                         uint32_t bindPoint) {
        if (m_HasBound) {
            bindPoint = m_BindPoint;
        } else {
            glBindBufferBase(GL_UNIFORM_BUFFER, bindPoint, m_RendererID); // Bind uniform buffer to bind point
            m_BindPoint = bindPoint;
            m_HasBound = true;
        }

        shader->Bind();
        uint32_t blockIndex = glGetUniformBlockIndex(shader->GetRendererID(), uniformBlockName.c_str());
        glUniformBlockBinding(shader->GetRendererID(), blockIndex, bindPoint);
    }

    void OpenGLUniformBuffer::SetBool(const std::string &name, int value) {
        SetData(name, &value);
    }

    void OpenGLUniformBuffer::SetInt(const std::string &name, int value) {
        SetData(name, &value);
    }

    void OpenGLUniformBuffer::SetInt2(const std::string &name, const glm::vec2 &value) {
        SetData(name, glm::value_ptr(value));
    }

    void OpenGLUniformBuffer::SetInt3(const std::string &name, const glm::vec3 &value) {
        SetData(name, glm::value_ptr(value));
    }

    void OpenGLUniformBuffer::SetInt4(const std::string &name, const glm::vec4 &value) {
        SetData(name, glm::value_ptr(value));
    }

    void OpenGLUniformBuffer::SetFloat(const std::string &name, float value) {
        SetData(name, &value);
    }

    void OpenGLUniformBuffer::SetFloat2(const std::string &name, const glm::vec2 &value) {
        SetData(name, glm::value_ptr(value));
    }

    void OpenGLUniformBuffer::SetFloat3(const std::string &name, const glm::vec3 &value) {
        SetData(name, glm::value_ptr(value));
    }

    void OpenGLUniformBuffer::SetFloat4(const std::string &name, const glm::vec4 &value) {
        SetData(name, glm::value_ptr(value));
    }

    void OpenGLUniformBuffer::SetMat2(const std::string &name, const glm::mat2 &value) {
        SetData(name, glm::value_ptr(value));
    }

    void OpenGLUniformBuffer::SetMat3(const std::string &name, const glm::mat3 &value) {
        SetData(name, glm::value_ptr(value));
    }

    void OpenGLUniformBuffer::SetMat4(const std::string &name, const glm::mat4 &value) {
        SetData(name, glm::value_ptr(value));
    }

    void OpenGLUniformBuffer::SetData(const std::string &name, const void* value) {
        KRISPY_CORE_ASSERT(m_Layout.ElementExists(name), "Element does not exist in the Uniform Buffer!");
        BufferElement element = m_Layout.GetElement(name);

        glBufferSubData(GL_UNIFORM_BUFFER, element.Offset, element.Size, value);
    }

}

