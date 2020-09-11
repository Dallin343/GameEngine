//
// Created by dallin on 8/21/20.
//

#pragma once

#include "Krispy/Renderer/RendererApi.h"

namespace Krispy {
    class OpenGLRendererAPI: public RendererAPI {
    public:
        void Init() override;

        void SetClearColor(const glm::vec4 &color) override;

        void Clear() override;

        void DrawIndexed(const Ref<VertexArray> &vertexArray) override;

        void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
    };
}