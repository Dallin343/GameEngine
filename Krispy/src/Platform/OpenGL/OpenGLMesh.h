//
// Created by dallin on 9/14/20.
//

#pragma once

#include "Krispy/Renderer/Mesh.h"
#include "Krispy/Renderer/VertexArray.h"
#include "Krispy/Renderer/Buffer.h"

namespace Krispy {
    class OpenGLMesh : public Mesh {
    public:
        OpenGLMesh(const OpenGLMesh&&) = delete;
        OpenGLMesh(OpenGLMesh&&) = delete;
        OpenGLMesh() = delete;
        OpenGLMesh(
                const std::vector<MeshVertex>& vertices,
                const std::vector<uint32_t>& indices,
                const std::vector<Ref<Texture>>& textures);

        void Draw(const Ref<Shader>& shader) override;

    private:
        void SetupMesh();

    private:

        Ref<VertexArray> m_VertexArray;
        Ref<VertexBuffer> m_VertexBuffer;
        Ref<IndexBuffer> m_IndexBuffer;

        std::vector<MeshVertex> m_Vertices;
        std::vector<uint32_t> m_Indices;
        std::vector<Ref<Texture>> m_Textures;
    };
}



