#include <utility>
#include "Shader.h"

//
// Created by dallin on 8/20/20.
//

#pragma once

namespace Krispy {
    static uint32_t ShaderDataTypeSize(ShaderDataType type) {
        switch (type) {
            case ShaderDataType::Float:     return 4;
            case ShaderDataType::Float2:    return 4 * 2;
            case ShaderDataType::Float3:    return 4 * 3;
            case ShaderDataType::Float4:    return 4 * 4;
            case ShaderDataType::Int:       return 4;
            case ShaderDataType::Int2:      return 4 * 2;
            case ShaderDataType::Int3:      return 4 * 3;
            case ShaderDataType::Int4:      return 4 * 4;
            case ShaderDataType::Bool:      return 1;
        }

        KRISPY_CORE_ASSERT(false, "Unknown ShaderDataType!");
        return 0;
    }

    struct BufferElement {
        std::string Name;
        ShaderDataType Type;
        uint32_t Size;
        uint32_t Offset;
        bool Normalized;

        BufferElement()  {};

        BufferElement(ShaderDataType type, const std::string&  name, uint32_t size = 0, bool normalized = false)
            : Type(type), Name(name), Normalized(normalized), Size(size ? size : ShaderDataTypeSize(type)), Offset(0) {}

        uint32_t GetComponentCount() const {
            switch (Type) {
                case ShaderDataType::Float:     return 1;
                case ShaderDataType::Float2:    return 2;
                case ShaderDataType::Float3:    return 3;
                case ShaderDataType::Float4:    return 4;
                case ShaderDataType::Int:       return 1;
                case ShaderDataType::Int2:      return 2;
                case ShaderDataType::Int3:      return 3;
                case ShaderDataType::Int4:      return 4;
                case ShaderDataType::Bool:      return 1;
            }

            KRISPY_CORE_ASSERT(false, "Unknown ShaderDataType!");
            return 0;
        }
    };

    class BufferLayout {
    public:
        BufferLayout() = default;

        BufferLayout(const std::initializer_list<BufferElement>& elements) : m_Elements(elements), m_Stride(0) {
            CalculateOffsetsAndStride();
        };

        inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }

        inline uint32_t GetStride() const { return m_Stride; }

        std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); };
        std::vector<BufferElement>::iterator end() { return m_Elements.end(); };
        std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); };
        std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); };

    private:
        void CalculateOffsetsAndStride() {
            uint32_t offset = 0;
            m_Stride = 0;
            for (auto& element : m_Elements) {
                element.Offset = offset;
                offset += element.Size;
                m_Stride += element.Size;
            }
        }

    private:
        uint32_t m_Stride;

    protected:
        std::vector<BufferElement> m_Elements;
    };

    class VertexBuffer {
    public:
        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void SetData(const void* data, uint32_t size) = 0;

        virtual const BufferLayout& GetLayout() const = 0;
        virtual void SetLayout(const BufferLayout& layout) = 0;

        static Ref<VertexBuffer> Create(float* vertices, uint32_t size);
        static Ref<VertexBuffer> Create(uint32_t size);
    };

    class IndexBuffer {
    public:
        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual uint32_t GetCount() const = 0;

        static Ref<IndexBuffer> Create(uint32_t* indices, uint32_t count);
    };

    class UniformBufferLayout {
    public:
        UniformBufferLayout() = default;

        void SetElements(const std::unordered_map<std::string, BufferElement>& elements) { m_Elements = elements; }
        inline const std::unordered_map<std::string, BufferElement>& GetElements() const { return m_Elements; }

        std::unordered_map<std::string, BufferElement>::iterator begin() { return m_Elements.begin(); };
        std::unordered_map<std::string, BufferElement>::iterator end() { return m_Elements.end(); };
        std::unordered_map<std::string, BufferElement>::const_iterator begin() const { return m_Elements.begin(); };
        std::unordered_map<std::string, BufferElement>::const_iterator end() const { return m_Elements.end(); };

        bool ElementExists(const std::string& name) {
            auto element = m_Elements.find(name);
            if (element == m_Elements.end())
                return false;
            return true;
        }

        BufferElement GetElement(const std::string& name) {
            KRISPY_CORE_ASSERT(ElementExists(name), "Element does not exist in the Uniform Buffer!");
            return m_Elements.at(name);
        }

    private:
        std::unordered_map<std::string, BufferElement> m_Elements;
        uint32_t m_Size;
    };

    class UniformBuffer {
    public:
        virtual const UniformBufferLayout& GetLayout() const = 0;
        virtual void SetLayout(std::initializer_list<BufferElement>& elements) = 0;

        virtual void BindShader(const std::string& uniformBlockName, const Ref<Shader>& shader, uint32_t bindPoint = 0) = 0;
        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;


        virtual void SetBool(const std::string& name, int value) = 0;
        virtual void SetInt(const std::string& name, int value) = 0;
        virtual void SetInt2(const std::string& name, const glm::vec2& value) = 0;
        virtual void SetInt3(const std::string& name, const glm::vec3& value) = 0;
        virtual void SetInt4(const std::string& name, const glm::vec4& value) = 0;
        virtual void SetFloat(const std::string& name, float value) = 0;
        virtual void SetFloat2(const std::string& name, const glm::vec2& value) = 0;
        virtual void SetFloat3(const std::string& name, const glm::vec3& value) = 0;
        virtual void SetFloat4(const std::string& name, const glm::vec4& value) = 0;
        virtual void SetMat2(const std::string& name, const glm::mat2& value) = 0;
        virtual void SetMat3(const std::string& name, const glm::mat3& value) = 0;
        virtual void SetMat4(const std::string& name, const glm::mat4& value) = 0;

        static Ref<UniformBuffer> Create(std::initializer_list<BufferElement>& elements);
    };
}
