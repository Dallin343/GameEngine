//
// Created by dallin on 9/11/20.
//

#pragma once

#include "Krispy/Renderer/OrthographicCamera.h"

#include "Krispy/Renderer/Texture.h"

namespace Krispy {
    class Renderer2D {
    public:
        static void Init();
        static void Shutdown();

        static void BeginScene(const OrthographicCamera& camera);
        static void EndScene();

        static void Flush();

        //Primitives
        static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
        static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
        static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor = 0.0f, const glm::vec4& tint = glm::vec4{1.0f});
        static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor = 0.0f, const glm::vec4& tint = glm::vec4{1.0f});
    };
}



