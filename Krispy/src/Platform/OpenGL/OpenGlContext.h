//
// Created by dallin on 8/19/20.
//

#pragma once

#include "Krispy/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Krispy {
    class OpenGLContext: public GraphicsContext {
    public:
        OpenGLContext(GLFWwindow *window);
        ~OpenGLContext();

        void Init() override;

        void SwapBuffers() override;

    private:
        GLFWwindow* m_Window;
    };
}