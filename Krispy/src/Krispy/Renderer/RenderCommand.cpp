//
// Created by dallin on 8/21/20.
//

#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Krispy {
    RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}

