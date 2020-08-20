//
// Created by dallin on 8/19/20.
//

#include "Krispy/Core/Base.h"
#include "Platform/OpenGL/OpenGlContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Krispy {
    OpenGLContext::OpenGLContext(GLFWwindow *window) : m_Window(window) {

    };

    OpenGLContext::~OpenGLContext() {

    }

    void OpenGLContext::Init() {
        glfwMakeContextCurrent(m_Window);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        KRISPY_CORE_ASSERT(status, "Could not initialize GLAD!");
    }

    void OpenGLContext::SwapBuffers() {
        glfwSwapBuffers(m_Window);
    }
}

