//
// Created by dallin on 8/21/20.
//

#pragma once

#include "Krispy/Renderer/RendererApi.h"

namespace Krispy {
    class RenderCommand {
    public:
        inline static void SetClearColor(const glm::vec4& color) {
            s_RendererAPI->SetClearColor(color);
        }

        inline static void Clear() {
            s_RendererAPI->Clear();
        }

        inline static void DrawIndexed(const Ref<VertexArray>& vertexArray) {
            s_RendererAPI->DrawIndexed(vertexArray);
        }

    private:
        static RendererAPI *s_RendererAPI;
    };
}



