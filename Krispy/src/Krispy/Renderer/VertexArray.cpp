//
// Created by dallin on 8/20/20.
//

#include "VertexArray.h"

#include "Krispy/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Krispy {

    Ref<VertexArray> VertexArray::Create() {
        switch (Renderer::GetAPI()) {
            case RendererAPI::API::None: KRISPY_CORE_ASSERT(false, "RenderAPI::None not implemented!"); break;
            case RendererAPI::API::OpenGL: return CreateRef<OpenGLVertexArray>();
        }

        KRISPY_CORE_ASSERT(false, "Unknown RenderAPI!");
        return nullptr;
    }
}

