//
// Created by dallin on 8/21/20.
//

#pragma once

#include <glm/glm.hpp>

#include "Krispy/Renderer/VertexArray.h"
#include "Krispy/Renderer/Buffer.h"

namespace Krispy {
    class RendererAPI {
    public:
        enum class API {
            None = 0, OpenGL
        };

        virtual void Init() = 0;
        virtual void SetClearColor(const glm::vec4& color) = 0;
        virtual void Clear() = 0;

        virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) = 0;

        inline static API GetAPI() { return s_API; }
    private:
        static API s_API;
    };
}


