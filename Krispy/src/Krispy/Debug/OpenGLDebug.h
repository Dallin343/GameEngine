//
// Created by dallin on 8/21/20.
//

#pragma once

#include <glad/glad.h>

namespace Krispy {
    enum class OpenGLDebugLevel {
        Off, All, Error, Notification
    };
    class OpenGLDebug {
    public:
        static void SetPrintLevel(OpenGLDebugLevel level) { s_PrintLevel = level; };
        static OpenGLDebugLevel GetPrintLevel() { return s_PrintLevel; };
        static void enableGLDebug(OpenGLDebugLevel printLevel = OpenGLDebugLevel::Error);
        static void GLDebugCallback(GLenum source,
                             GLenum type,
                             GLuint id,
                             GLenum severity,
                             GLsizei length,
                             const GLchar *message,
                             const void *userParam);
    private:
        static bool IsInPrintLevel(GLenum type);
        static OpenGLDebugLevel s_PrintLevel;
    };
}



