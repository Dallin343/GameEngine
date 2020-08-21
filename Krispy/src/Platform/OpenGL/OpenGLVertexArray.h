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

        void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;

        void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;

        const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const override { return m_VertexBuffers; };

        const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const override { return m_IndexBuffer; };
        //uint32_t m_RenderID;
    private:

        std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
        std::shared_ptr<IndexBuffer> m_IndexBuffer;
    };
}