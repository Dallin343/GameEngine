//
// Created by dallin on 8/24/20.
//

#include "Texture.h"

#include "Krispy/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGlTexture.h"

namespace Krispy {

    Ref<Texture2D> Texture2D::Create(const std::string &path) {
        switch (Renderer::GetAPI()) {
            case RendererAPI::API::None: KRISPY_CORE_ASSERT(false, "RenderAPI::None not implemented!");
            case RendererAPI::API::OpenGL: return std::make_shared<OpenGLTexture2D>(path);
        }

        KRISPY_CORE_ASSERT(false, "Unknown RenderAPI!");
        return nullptr;
    }
}


