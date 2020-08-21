//
// Created by dallin on 8/21/20.
//

#pragma once

#include "Krispy/Renderer/VertexArray.h"
#include "Krispy/Renderer/Buffer.h"

#include <glm/glm.hpp>

namespace Krispy {
    class RendererAPI {
    public:
        enum class API {
            None = 0, OpenGL
        };

        virtual void SetClearColor(const glm::vec4& color) = 0;
        virtual void Clear() = 0;

        virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;

        inline static API GetAPI() { return s_API; }
    private:
        static API s_API;
    };
}


