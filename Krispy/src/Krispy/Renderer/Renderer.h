//
// Created by dallin on 8/20/20.
//

#pragma once
#include "Krispy/Renderer/RenderCommand.h"

namespace Krispy {
    class Renderer {
    public:
        static void BeginScene();
        static void Submit(const std::shared_ptr<VertexArray>& vertexArray);
        static void EndScene();

        inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); };
    };
}



