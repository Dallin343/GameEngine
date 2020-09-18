//
// Created by dallin on 8/19/20.
//

#include "Krispy/Core/Base.h"
#include "Platform/OpenGL/OpenGLContext.h"
#include "Krispy/Debug/OpenGLDebug.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Krispy {
    OpenGLContext::OpenGLContext(GLFWwindow *window) : m_Window(window) {

    };

    OpenGLContext::~OpenGLContext() {

    }

    void OpenGLContext::Init() {
        KRISPY_PROFILE_FUNCTION();

        glfwMakeContextCurrent(m_Window);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        KRISPY_CORE_ASSERT(status, "Could not initialize GLAD!");
        OpenGLDebug::enableGLDebug();
    }

    void OpenGLContext::SwapBuffers() {
        glfwSwapBuffers(m_Window);
    }
}

