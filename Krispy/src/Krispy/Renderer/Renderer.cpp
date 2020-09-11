//
// Created by dallin on 8/20/20.
//

#include "Renderer.h"

namespace Krispy {

    Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

    void Renderer::Init() {
        RenderCommand::Init();
    }

    void Renderer::BeginScene(OrthographicCamera& camera) {
        m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
    }

    void Renderer::Submit(const Ref<Shader> &shader, const Ref<VertexArray> &vertexArray, const glm::mat4& transform) {
        shader->Bind();
        shader->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
        shader->UploadUniformMat4("u_Transform", transform);

        vertexArray->Bind();
        RenderCommand::DrawIndexed(vertexArray);
    }

    void Renderer::EndScene() {

    }
}


