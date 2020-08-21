//
// Created by dallin on 8/21/20.
//

#include "OpenGLDebug.h"
#include <GLFW/glfw3.h>

namespace Krispy {
    OpenGLDebugLevel OpenGLDebug::s_PrintLevel = OpenGLDebugLevel::Off;

    static void PrintMessage(
            const std::string& source, const std::string& type,
            GLuint id, const std::string& severity, const GLchar *message) {

        std::cout << std::endl << "OpenGL Debug Message: (Severity= " << severity << ")"
                  << " (Source=" << source << ")"
                  << " (Type=" << type << ")"
                  << " (ID=" << id << ")" << std::endl
                  << "  Message: " << message << std::endl << std::endl;
    }

    static const std::string GLEnumToString(GLenum item) {
        switch (item) {
            case GL_DEBUG_SEVERITY_NOTIFICATION: return "Notification";
            case GL_DEBUG_SEVERITY_LOW: return "Low";
            case GL_DEBUG_SEVERITY_MEDIUM: return "Medium";
            case GL_DEBUG_SEVERITY_HIGH: return "High";
            case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: return "Deprecated Behavior";
            case GL_DEBUG_TYPE_ERROR: return "Error";
            case GL_DEBUG_TYPE_MARKER: return "Marker";
            case GL_DEBUG_TYPE_OTHER: return "Other";
            case GL_DEBUG_TYPE_PERFORMANCE: return "Performance";
            case GL_DEBUG_TYPE_POP_GROUP: return "Pop Group";
            case GL_DEBUG_TYPE_PORTABILITY: return "Portability";
            case GL_DEBUG_TYPE_PUSH_GROUP: return "Push Group";
            case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: return "Undefined Behavior";

            case GL_DEBUG_SOURCE_API: return "Source API";
            case GL_DEBUG_SOURCE_APPLICATION: return "Source Application";
            case GL_DEBUG_SOURCE_OTHER: return "Other";
            case GL_DEBUG_SOURCE_SHADER_COMPILER: return "Shader Compiler";
            case GL_DEBUG_SOURCE_THIRD_PARTY: return "Third Party";
            case GL_DEBUG_SOURCE_WINDOW_SYSTEM: return "Window System";
        }

        return "GLenum Value Not Found";
    }

    void OpenGLDebug::enableGLDebug(OpenGLDebugLevel printLevel) {
        s_PrintLevel = printLevel;
        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(GLDebugCallback, nullptr);
    }

    void OpenGLDebug::GLDebugCallback(
            GLenum source, GLenum type, GLuint id, GLenum severity,
            GLsizei length, const GLchar *message, const void *userParam
    ) {

        if (IsInPrintLevel(type))
            PrintMessage(GLEnumToString(source), GLEnumToString(type), id, GLEnumToString(severity), message);

        if (type == GL_DEBUG_TYPE_ERROR) {
            KRISPY_DEBUGBREAK();
        }
    }

    bool OpenGLDebug::IsInPrintLevel(GLenum type) {
        switch (s_PrintLevel) {
            case OpenGLDebugLevel::Off: return false;
            case OpenGLDebugLevel::All: return true;
            case OpenGLDebugLevel::Error:
                if (type == GL_DEBUG_TYPE_ERROR)
                    return true;
                return false;
            case OpenGLDebugLevel::Notification:
                if (type == GL_DEBUG_TYPE_OTHER)
                    return true;
                return false;
        }

        return false;
    }
}

