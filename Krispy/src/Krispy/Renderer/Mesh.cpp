//
// Created by dallin on 9/14/20.
//

#include "Mesh.h"

#include "Krispy/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLMesh.h"

namespace Krispy {
    Ref<Mesh> Mesh::Create(std::vector<MeshVertex> vertices, std::vector<uint32_t> indices, std::vector<Ref<Texture>> textures) {
        switch (Renderer::GetAPI()) {
            case RendererAPI::API::None: KRISPY_CORE_ASSERT(false, "RenderAPI::None not implemented!");
            case RendererAPI::API::OpenGL: return CreateRef<OpenGLMesh>(vertices, indices, textures);
        }

        KRISPY_CORE_ASSERT(false, "Unknown RenderAPI!");
        return nullptr;
    }
}

