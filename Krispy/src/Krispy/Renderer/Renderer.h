//
// Created by dallin on 8/20/20.
//

#pragma once
#include "Krispy/Renderer/RenderCommand.h"
#include "Krispy/Renderer/OrthographicCamera.h"
#include "Krispy/Renderer/Shader.h"

namespace Krispy {
    class Renderer {
    public:
        static void BeginScene(OrthographicCamera& camera);
        static void Submit(
                const Ref<Shader>& shader,
                const Ref<VertexArray>& vertexArray,
                const glm::mat4& transform = glm::mat4(1.0f));

        static void EndScene();

        inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); };

    private:
        struct SceneData {
            glm::mat4 ViewProjectionMatrix;
        };

        static SceneData* m_SceneData;
    };
}



