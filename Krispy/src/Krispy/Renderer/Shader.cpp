//
// Created by dallin on 8/19/20.
//

#include "Shader.h"
#include "Krispy/Renderer/RendererApi.h"

#include "Platform/OpenGL/OpenGlShader.h"

namespace Krispy {
    Shader *Shader::Create(const std::string &vertexSrc, const std::string &fragmentSrc) {
        switch (RendererAPI::GetAPI()) {
            case RendererAPI::API::None: break;
            case RendererAPI::API::OpenGL: return new OpenGLShader(vertexSrc, fragmentSrc);
        }

        KRISPY_CORE_ASSERT(false, "RendererAPI::API::None is unknown!");
        return nullptr;
    }
}