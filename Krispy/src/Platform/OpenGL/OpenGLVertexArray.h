//
// Created by dallin on 8/20/20.
//

#pragma once
#include "Krispy/Renderer/VertexArray.h"

namespace Krispy {
    class OpenGLVertexArray: public VertexArray {
    public:
        OpenGLVertexArray();
        ~OpenGLVertexArray();
        void Bind() override;

        void Unbind() override;

        void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;

        void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;

        const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const override { return m_VertexBuffers; };

        const Ref<IndexBuffer>& GetIndexBuffer() const override { return m_IndexBuffer; };
        //uint32_t m_RenderID;
    private:
        uint32_t m_RenderID;
        std::vector<Ref<VertexBuffer>> m_VertexBuffers;
        Ref<IndexBuffer> m_IndexBuffer;
    };
}