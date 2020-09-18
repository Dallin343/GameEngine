//
// Created by dallin on 9/14/20.
//

#include "OpenGLMesh.h"

#include <glad/glad.h>

namespace Krispy {
    OpenGLMesh::OpenGLMesh(const std::vector<MeshVertex>& vertices,
                           const std::vector<uint32_t>& indices,
                           const std::vector<Ref<Texture>>& textures)
    : m_Vertices(vertices), m_Indices(indices), m_Textures(textures) {

        SetupMesh();
    }

    void OpenGLMesh::SetupMesh() {
        m_VertexArray = VertexArray::Create();
        m_VertexBuffer = VertexBuffer::Create(reinterpret_cast<float *>(&m_Vertices[0]), m_Vertices.size());
        m_VertexBuffer->SetLayout({
            {ShaderDataType::Float3, "a_Position"},
            {ShaderDataType::Float3, "a_Normal"},
            {ShaderDataType::Float2, "a_TexCoord"},
        });

        m_VertexArray->AddVertexBuffer(m_VertexBuffer);

        m_IndexBuffer = IndexBuffer::Create(&m_Indices[0], m_Indices.size());

        m_VertexArray->SetIndexBuffer(m_IndexBuffer);

        m_VertexArray->Unbind();
    }

    void OpenGLMesh::Draw(const Ref<Shader>& shader) {
        uint32_t diffuseIndex = 1;
        uint32_t specularIndex = 1;

        shader->Bind();

        for (uint32_t i = 0; i < m_Textures.size(); i++) {

            std::string number;
            TextureType type = m_Textures[i]->GetType();

            if (type == TextureType::Diffuse) {
                number = std::to_string(diffuseIndex++);
                shader->SetFloat("u_Material.texture_diffuse" + number, i);
            } else if (type == TextureType::Specular) {
                number = std::to_string(specularIndex++);
                shader->SetFloat("u_Material.texture_specular" + number, i);
            }

            m_Textures[i]->Bind(i);
        }

        glActiveTexture(GL_TEXTURE0);

        m_VertexArray->Bind();

        glDrawElements(GL_TRIANGLES, m_VertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
    }
}


