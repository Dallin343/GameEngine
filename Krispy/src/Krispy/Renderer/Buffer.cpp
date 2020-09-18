//
// Created by dallin on 8/20/20.
//

#include "Buffer.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Krispy {
    Ref<VertexBuffer> VertexBuffer::Create(float *vertices, uint32_t size) {
        switch (Renderer::GetAPI()) {
            case RendererAPI::API::None: KRISPY_CORE_ASSERT(false, "RenderAPI::None not implemented!"); return nullptr;
            case RendererAPI::API::OpenGL: return CreateRef<OpenGLVertexBuffer>(vertices, size);
        }

        KRISPY_CORE_ASSERT(false, "Unknown RenderAPI!");
        return nullptr;
    }

    Ref<VertexBuffer> VertexBuffer::Create(uint32_t size) {
        switch (Renderer::GetAPI()) {
            case RendererAPI::API::None: KRISPY_CORE_ASSERT(false, "RenderAPI::None not implemented!"); return nullptr;
            case RendererAPI::API::OpenGL: return CreateRef<OpenGLVertexBuffer>(size);
        }

        KRISPY_CORE_ASSERT(false, "Unknown RenderAPI!");
        return nullptr;
    }

    Ref<IndexBuffer> IndexBuffer::Create(uint32_t *indices, uint32_t count) {
        switch (Renderer::GetAPI()) {
            case RendererAPI::API::None: KRISPY_CORE_ASSERT(false, "RenderAPI::None not implemented!"); return nullptr;
            case RendererAPI::API::OpenGL: return CreateRef<OpenGLIndexBuffer>(indices, count);
        }

        KRISPY_CORE_ASSERT(false, "Unknown RenderAPI!");
        return nullptr;
    }

    Ref<UniformBuffer> UniformBuffer::Create(std::initializer_list<BufferElement>& elements) {
        switch (Renderer::GetAPI()) {
            case RendererAPI::API::None: KRISPY_CORE_ASSERT(false, "RenderAPI::None not implemented!"); return nullptr;
            case RendererAPI::API::OpenGL: return CreateRef<OpenGLUniformBuffer>(elements);
        }

        KRISPY_CORE_ASSERT(false, "Unknown RenderAPI!");
        return nullptr;
    }
}

