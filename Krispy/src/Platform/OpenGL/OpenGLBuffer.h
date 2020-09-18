//
// Created by dallin on 8/20/20.
//

#pragma once

#include "Krispy/Renderer/Buffer.h"

namespace Krispy {
    class OpenGLVertexBuffer: public VertexBuffer {
    public:
        OpenGLVertexBuffer(uint32_t size);
        OpenGLVertexBuffer(float* vertices, uint32_t size);
        ~OpenGLVertexBuffer();
        void Bind() const override;
        void Unbind() const override;

        void SetData(const void *data, uint32_t size) override;

        const BufferLayout& GetLayout() const override { return m_Layout; };

        void SetLayout(const BufferLayout &layout) override {
            m_Layout = layout;
        };

    private:
        uint32_t m_RendererID;
        BufferLayout m_Layout;
    };

    class OpenGLIndexBuffer: public IndexBuffer {
    public:
        OpenGLIndexBuffer(uint32_t *indices, uint32_t count);
        ~OpenGLIndexBuffer();
        void Bind() const override;
        void Unbind() const override;

        uint32_t GetCount() const override { return m_Count; };

    private:
        uint32_t m_RendererID;
        uint32_t m_Count;
    };

    class OpenGLUniformBuffer: public UniformBuffer {
    public:
        OpenGLUniformBuffer(std::initializer_list<BufferElement>& elements);

        void BindShader(const std::string &uniformBlockName, const Ref <Shader> &shader, uint32_t bindPoint) override;

        void Bind() const override;
        void Unbind() const override;

        const UniformBufferLayout& GetLayout() const override { return m_Layout; }
        void SetLayout(std::initializer_list<BufferElement> &elements) override;

        void SetBool(const std::string &name, int value) override;
        void SetInt(const std::string &name, int value) override;
        void SetInt2(const std::string &name, const glm::vec2 &value) override;
        void SetInt3(const std::string &name, const glm::vec3 &value) override;
        void SetInt4(const std::string &name, const glm::vec4 &value) override;
        void SetFloat(const std::string &name, float value) override;
        void SetFloat2(const std::string &name, const glm::vec2 &value) override;
        void SetFloat3(const std::string &name, const glm::vec3 &value) override;
        void SetFloat4(const std::string &name, const glm::vec4 &value) override;
        void SetMat2(const std::string &name, const glm::mat2 &value) override;
        void SetMat3(const std::string &name, const glm::mat3 &value) override;
        void SetMat4(const std::string &name, const glm::mat4 &value) override;

    private:
        void CreateLayout(std::initializer_list<BufferElement> &elements);
        void SetData(const std::string &name, const void* value);
    private:
        uint32_t m_RendererID;
        UniformBufferLayout m_Layout;
        uint32_t m_Size;
        uint32_t m_BindPoint;
        bool m_HasBound = false;
    };
}



