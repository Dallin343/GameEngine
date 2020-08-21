//
// Created by dallin on 8/21/20.
//

#pragma once

#include "Krispy/Renderer/RendererApi.h"

namespace Krispy {
    class OpenGLRendererAPI: public RendererAPI {
    public:
        void SetClearColor(const glm::vec4 &color) override;

        void Clear() override;

        void DrawIndexed(const std::shared_ptr<VertexArray> &vertexArray) override;
    };
}