//
// Created by dallin on 8/20/20.
//

#pragma once

namespace Krispy {
    enum class RenderAPI {
        None = 0, OpenGL
    };
    class Renderer {
    public:
        static RenderAPI GetAPI() { return s_RenderAPI; };

    private:
        static RenderAPI s_RenderAPI;
    };
}



