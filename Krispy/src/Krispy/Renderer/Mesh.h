//
// Created by dallin on 9/14/20.
//

#pragma once

#include <glm/glm.hpp>
#include "Krispy/Renderer/Shader.h"
#include "Krispy/Renderer/Texture.h"

namespace Krispy {

    struct MeshVertex {
        glm::vec3 Position;
        glm::vec3 Normal;
        glm::vec2 TexCoords;
    };

    class Mesh {
    public:
        virtual void Draw(const Ref<Shader>& shader) = 0;

        static Ref<Mesh> Create(
                std::vector<MeshVertex> vertices,
                std::vector<uint32_t> indices,
                std::vector<Ref<Texture>> textures);
    };
}



