//
// Created by dallin on 9/15/20.
//

#include "Material.h"

#include "Krispy/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLMaterial.h"

namespace Krispy {
    Ref<Material> Material::Create(float ambientStrength, const Ref <Texture2D> &diffuse, const Ref <Texture2D> &specular) {
        switch (Renderer::GetAPI()) {
            case RendererAPI::API::None: KRISPY_CORE_ASSERT(false, "RenderAPI::None not implemented!"); return nullptr;
            case RendererAPI::API::OpenGL: return CreateRef<OpenGLMaterial>(ambientStrength, diffuse, specular);
        }

        KRISPY_CORE_ASSERT(false, "Unknown RenderAPI!");
        return nullptr;
    }
}

