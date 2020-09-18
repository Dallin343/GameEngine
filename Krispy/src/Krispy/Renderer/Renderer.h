//
// Created by dallin on 8/20/20.
//

#pragma once
#include "Krispy/Renderer/RenderCommand.h"
//#include "Krispy/Renderer/OrthographicCamera.h"
#include "Krispy/Renderer/PerspectiveCamera.h"
#include "Krispy/Renderer/Shader.h"
#include "Model.h"

namespace Krispy {
    class Renderer {
    public:
        static void Init();
        static void BeginScene(PerspectiveCamera& camera);
        static void Submit(
                const Ref<Shader>& shader,
                const Ref<VertexArray>& vertexArray,
                const glm::mat4& transform = glm::mat4(1.0f));

        static void EndScene();

        static void DrawModel(const Ref<Model>& model, const Ref<Shader>& shader);

        static void DrawCube(
                const Ref<Shader> &shader,
                const std::vector<Ref<Texture2D>>& textures,
                const glm::vec3& position);

        static void DrawTriangle(const Ref<Shader> &shader, const std::vector<Ref<Texture2D>>& textures);

        static void OnWindowResize(uint32_t width, uint32_t height);


        inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); };

    private:
        struct SceneData {
            glm::mat4 ViewProjectionMatrix;
            glm::vec3 ViewPosition;
        };

        static SceneData* m_SceneData;
    };
}



