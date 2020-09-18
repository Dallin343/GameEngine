//
// Created by dallin on 8/21/20.
//

#pragma once

#include "Krispy/Renderer/RendererApi.h"

namespace Krispy {
    class RenderCommand {
    public:
        inline static void Init() {
            s_RendererAPI->Init();
        }

        inline static void SetClearColor(const glm::vec4& color) {
            s_RendererAPI->SetClearColor(color);
        }

        inline static void Clear() {
            s_RendererAPI->Clear();
        }

        inline static void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0) {
            s_RendererAPI->DrawIndexed(vertexArray, indexCount);
        }

        inline static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
            s_RendererAPI->SetViewport(0, 0, width, height);
        }

    private:
        static RendererAPI *s_RendererAPI;
    };
}



