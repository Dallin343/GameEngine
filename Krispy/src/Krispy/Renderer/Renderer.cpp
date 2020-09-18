//
// Created by dallin on 8/20/20.
//

#include <glm/gtc/matrix_transform.hpp>
#include "Renderer.h"
#include "Renderer2D.h"

//Temporary
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Krispy {

    Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

    struct RenderData {
        Ref<VertexArray> CubeVertexArray;
        Ref<VertexBuffer> CubeVertexBuffer;
        Ref<IndexBuffer> CubeIndexbuffer;

        Ref<VertexArray> TriangleVertexArray;
        Ref<VertexBuffer> TriangleVertexBuffer;
        Ref<IndexBuffer> TriangleIndexBuffer;
    };

    static RenderData s_Data;

    void Renderer::Init() {
        KRISPY_PROFILE_FUNCTION();

        RenderCommand::Init();
        Renderer2D::Init();

        float triVertices[] = {
                0.5f, 0.5f, 0.0f, 1.0f, 1.0f, // Top right
                0.5f, -0.5f, 0.0f, 1.0f, 0.0f,// bottom right
                -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
                -0.5f, 0.5f, 0.0f, 0.0f, 1.0f // top left
        };

        uint32_t triIndices[] = {
                0, 1, 3,
                1, 2, 3
        };

        s_Data.TriangleVertexArray = VertexArray::Create();
        s_Data.TriangleVertexBuffer = VertexBuffer::Create(triVertices, sizeof(triVertices));
        s_Data.TriangleVertexBuffer->SetLayout({
            {ShaderDataType::Float3, "a_Position"},
            {ShaderDataType::Float3, "a_Normal"},
            { ShaderDataType::Float2, "a_TexCoords"}
        });

        s_Data.TriangleIndexBuffer = IndexBuffer::Create(triIndices, 6);

        s_Data.TriangleVertexArray->AddVertexBuffer(s_Data.TriangleVertexBuffer);
        s_Data.TriangleVertexArray->SetIndexBuffer(s_Data.TriangleIndexBuffer);


        float cubeVertices[] = {
                // positions          // normals           // texture coords
                -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
                0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
                0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
                0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
                -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
                -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

                -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
                0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
                0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
                0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
                -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
                -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

                -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
                -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
                -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
                -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
                -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
                -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

                0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
                0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
                0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
                0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
                0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
                0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

                -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
                0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
                0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
                0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
                -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
                -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

                -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
                0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
                0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
                0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
                -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
                -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
        };


        s_Data.CubeVertexArray = VertexArray::Create();
        s_Data.CubeVertexBuffer = VertexBuffer::Create(cubeVertices, sizeof(cubeVertices));
        s_Data.CubeVertexBuffer->SetLayout({
            {ShaderDataType::Float3, "a_Position"},
            {ShaderDataType::Float3, "a_Normal"},
            { ShaderDataType::Float2, "a_TexCoord"}
        });

        s_Data.CubeVertexArray->AddVertexBuffer(s_Data.CubeVertexBuffer);
    }

    void Renderer::BeginScene(PerspectiveCamera& camera) {
        m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
        m_SceneData->ViewPosition = camera.GetPosition();
    }

    void Renderer::Submit(const Ref<Shader> &shader, const Ref<VertexArray> &vertexArray, const glm::mat4& transform) {
        /*shader->Bind();
        shader->SetMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
        shader->SetMat4("u_Transform", transform);

        vertexArray->Bind();
        RenderCommand::DrawIndexed(vertexArray);*/
    }

    void Renderer::DrawModel(const Ref<Model> &model, const Ref<Shader>& shader) {
        shader->Bind();
        shader->SetMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
        shader->SetMat4("u_Transform", glm::mat4(1.0f));
        shader->SetFloat4("u_Color", {0.8f, 0.4f, 0.4f, 1.0f});
        model->Draw(shader);
    }

    void Renderer::DrawCube(const Ref<Shader> &shader, const std::vector<Ref<Texture2D>>& textures, const glm::vec3& position) {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, position);
        model = glm::rotate(model, glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));

        uint32_t count = 0;
        for (const Ref<Texture2D>& texture : textures) {
            texture->Bind(count++);
        }


        shader->Bind();
        shader->SetInt("u_Material.diffuse", 0);
        shader->SetInt("u_Material.specular", 1);
        shader->SetFloat("u_Material.shininess", 128.0f);

        shader->SetFloat3("u_Light.position", {1.0f, -2.0f, 1.0f});
        shader->SetFloat3("u_Light.ambient", {0.2f, 0.2f, 0.2f});
        shader->SetFloat3("u_Light.diffuse", {1.0f, 1.0f, 1.0f});
        shader->SetFloat3("u_Light.specular", {0.8f, 0.8f, 0.8f});


        shader->SetMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
        shader->SetMat4("u_Model", model);
        shader->SetFloat3("u_ViewPosition", m_SceneData->ViewPosition);

        s_Data.CubeVertexArray->Bind();
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    void Renderer::DrawTriangle(const Ref<Shader> &shader, const std::vector<Ref<Texture2D>>& textures) {

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(-55.0f), {1.0f, 0.0f, 0.0f});

        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view, {0.0f, 0.0f, -3.0f});

        glm::mat4 proj = glm::mat4(1.0f);
        proj = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 100.0f);

        shader->Bind();
        uint32_t count = 0;
        for (const Ref<Texture2D>& texture : textures) {
            texture->Bind(count++);
        }

        shader->SetMat4("u_Model", model);
        shader->SetMat4("u_ViewProjection", proj * view);
        shader->SetInt("u_Texture", 0);
        shader->SetInt("u_Texture2", 1);
        shader->SetFloat4("u_Color", {0.2f, 0.3f, 0.6f, 1.0f});
        s_Data.TriangleVertexArray->Bind();
        RenderCommand::DrawIndexed(s_Data.TriangleVertexArray);
    }

    void Renderer::EndScene() {

    }

    void Renderer::OnWindowResize(uint32_t width, uint32_t height) {
        RenderCommand::SetViewport(0, 0, width, height);
    }
}


