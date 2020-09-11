//
// Created by dallin on 8/19/20.
//

#include "Shader.h"
#include "Krispy/Renderer/RendererApi.h"

#include "Platform/OpenGL/OpenGlShader.h"

namespace Krispy {
    Ref<Shader> Shader::Create(const std::string &path) {
        switch (RendererAPI::GetAPI()) {
            case RendererAPI::API::None: KRISPY_CORE_ASSERT(false, "RendererAPI::API::None is not implemented!"); break;
            case RendererAPI::API::OpenGL: return std::make_shared<OpenGLShader>(path);
        }

        KRISPY_CORE_ASSERT(false, "RendererAPI is unknown!");
        return nullptr;
    }

    Ref <Krispy::Shader>
    Shader::Create(const std::string &name, const std::string &vertexSrc, const std::string &fragmentSrc) {
        switch (RendererAPI::GetAPI()) {
            case RendererAPI::API::None: KRISPY_CORE_ASSERT(false, "RendererAPI::API::None is not implemented!"); break;
            case RendererAPI::API::OpenGL: return std::make_shared<OpenGLShader>(name, vertexSrc, fragmentSrc);
        }

        KRISPY_CORE_ASSERT(false, "RendererAPI is unknown!");
        return nullptr;
    }


#pragma mark --Shader Library--

    void ShaderLibrary::Add(const std::string &name, const Ref <Shader> &shader) {
        KRISPY_CORE_ASSERT(!Exists(name), "Shader Already Exists In Library!");
        m_Shaders[name] = shader;
    }

    void ShaderLibrary::Add(const Ref <Shader> &shader) {
        auto name = shader->GetName();
        Add(name, shader);
    }

    Ref<Shader> ShaderLibrary::Load(const std::string &path) {
        auto shader = Shader::Create(path);
        Add(shader);
        return shader;
    }

    Ref<Shader> ShaderLibrary::Load(const std::string &name, const std::string &path) {
        auto shader = Shader::Create(path);
        Add(name, shader);
        return shader;
    }

    Ref<Shader> ShaderLibrary::Get(const std::string &name) {
        KRISPY_CORE_ASSERT(Exists(name), "Shader Doesn't Exist In Library!");
        return m_Shaders[name];
    }

    bool ShaderLibrary::Exists(const std::string &name) const {
        return m_Shaders.find(name) != m_Shaders.end();
    }
}