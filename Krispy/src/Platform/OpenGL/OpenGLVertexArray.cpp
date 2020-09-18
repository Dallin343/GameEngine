//
// Created by dallin on 8/20/20.
//

#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Krispy {

    static GLenum ShaderDataTypeToGL(ShaderDataType type) {
        switch (type) {
            case ShaderDataType::Float:
            case ShaderDataType::Float2:
            case ShaderDataType::Float3:
            case ShaderDataType::Float4: return GL_FLOAT;
            case ShaderDataType::Int:
            case ShaderDataType::Int2:
            case ShaderDataType::Int3:
            case ShaderDataType::Int4: return GL_INT;
            case ShaderDataType::Bool: return GL_BOOL;
        }

        KRISPY_CORE_ASSERT(false, "Unknown ShaderDataType!");
        return GL_NONE;
    }

    OpenGLVertexArray::OpenGLVertexArray() {
        KRISPY_PROFILE_FUNCTION();

        glCreateVertexArrays(1, &m_RenderID);
    }

    OpenGLVertexArray::~OpenGLVertexArray() {
        KRISPY_PROFILE_FUNCTION();

        glDeleteVertexArrays(1, &m_RenderID);
    }

    void OpenGLVertexArray::Bind() {
        KRISPY_PROFILE_FUNCTION();

        glBindVertexArray(m_RenderID);
    }

    void OpenGLVertexArray::Unbind() {
        KRISPY_PROFILE_FUNCTION();

        glBindVertexArray(0);
    }

    void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) {
        KRISPY_PROFILE_FUNCTION();

        KRISPY_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

        glBindVertexArray(m_RenderID);
        vertexBuffer->Bind();

        const auto& layout = vertexBuffer->GetLayout();
        uint32_t index = 0;
        for (const auto& element : layout) {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(
                    index,
                    element.GetComponentCount(),
                    ShaderDataTypeToGL(element.Type),
                    element.Normalized ? GL_TRUE : GL_FALSE,
                    layout.GetStride(),
                    (const void *) element.Offset
            );
            index++;
        }

        m_VertexBuffers.push_back(vertexBuffer);
    }

    void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) {
        KRISPY_PROFILE_FUNCTION();

        glBindVertexArray(m_RenderID);
        indexBuffer->Bind();

        m_IndexBuffer = indexBuffer;
    }
}


