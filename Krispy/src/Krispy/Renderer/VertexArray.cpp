//
// Created by dallin on 8/20/20.
//

#include "VertexArray.h"

#include "Krispy/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGlVertexArray.h"

namespace Krispy {
    VertexArray* VertexArray::Create() {
        switch (Renderer::GetAPI()) {
            case RenderAPI::None: KRISPY_CORE_ASSERT(false, "RenderAPI::None not implemented!");
            case RenderAPI::OpenGL: return new OpenGLVertexArray();
        }

        KRISPY_CORE_ASSERT(false, "Unknown RenderAPI!");
        return nullptr;
    }
}

