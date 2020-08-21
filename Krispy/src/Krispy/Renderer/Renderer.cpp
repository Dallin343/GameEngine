//
// Created by dallin on 8/20/20.
//

#include "Renderer.h"

namespace Krispy {
    void Renderer::BeginScene() {

    }

    void Renderer::Submit(const std::shared_ptr<VertexArray> &vertexArray) {
        RenderCommand::DrawIndexed(vertexArray);
    }

    void Renderer::EndScene() {

    }
}


