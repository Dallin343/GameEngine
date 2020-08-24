//
// Created by dallin on 8/24/20.
//

#pragma once
#include "Krispy/Renderer/Shader.h"

namespace Krispy {
    class OpenGLShader : public Shader{
    public:
        OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
        ~OpenGLShader();
        void UploadUniform(const std::string& name, const glm::mat4 &matrix) override;

        void Bind() const override;

        void Unbind() const override;

        uint32_t GetRendererID() const override { return m_RendererID; };

    private:
        uint32_t m_RendererID;
    };
}



