//
// Created by dallin on 8/24/20.
//

#pragma once
#include "Krispy/Renderer/Shader.h"

#include <glad/glad.h>

namespace Krispy {
    class OpenGLShader : public Shader{
    public:
        OpenGLShader(const std::string &path);
        OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
        ~OpenGLShader();

        void Bind() const override;
        void Unbind() const override;
        uint32_t GetRendererID() const override { return m_RendererID; };

        const std::string& GetName() const override { return m_Name; };


        void UploadUniformMat4(const std::string& name, const glm::mat4 &uniform) override;
        void UploadUniformFloat3(const std::string &name, const glm::vec3 &uniform) override;

        void UploadUniformMat2(const std::string &name, const glm::mat2 &uniform) override;

        void UploadUniformMat3(const std::string &name, const glm::mat3 &uniform) override;

        void UploadUniformFloat2(const std::string &name, const glm::vec2 &uniform) override;

        void UploadUniformFloat4(const std::string &name, const glm::vec4 &uniform) override;

        void UploadUniformFloat(const std::string &name, float uniform) override;

        void UploadUniformUInt(const std::string &name, uint32_t uniform) override;

        void UploadUniformUInt2(const std::string &name, const glm::vec2 &uniform) override;

        void UploadUniformUInt3(const std::string &name, const glm::vec3 &uniform) override;

        void UploadUniformUInt4(const std::string &name, const glm::vec4 &uniform) override;

    private:
        std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
        std::string ReadFile(const std::string& path);
        void Compile(std::unordered_map<GLenum, std::string>& shaderSources);

    private:
        std::string m_Name;
        uint32_t m_RendererID;
    };
}



