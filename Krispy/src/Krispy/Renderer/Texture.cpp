//
// Created by dallin on 8/24/20.
//

#include "Texture.h"

#include "Krispy/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Krispy {

    Ref<Texture2D> Texture2D::Create(const std::string &path, TextureType type) {
        switch (Renderer::GetAPI()) {
            case RendererAPI::API::None: KRISPY_CORE_ASSERT(false, "RenderAPI::None not implemented!");
            case RendererAPI::API::OpenGL: return CreateRef<OpenGLTexture2D>(path);
        }

        KRISPY_CORE_ASSERT(false, "Unknown RenderAPI!");
        return nullptr;
    }

    Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height, TextureType type) {
        switch (Renderer::GetAPI()) {
            case RendererAPI::API::None: KRISPY_CORE_ASSERT(false, "RenderAPI::None not implemented!");
            case RendererAPI::API::OpenGL: return CreateRef<OpenGLTexture2D>(width, height, type);
        }

        KRISPY_CORE_ASSERT(false, "Unknown RenderAPI!");
        return nullptr;
    }
}


