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

        void SetInt(const std::string &name, int value) override;
        void SetInt2(const std::string &name, const glm::vec2 &value) override;
        void SetInt3(const std::string &name, const glm::vec3 &value) override;
        void SetInt4(const std::string &name, const glm::vec4 &value) override;
        void SetIntArray(const std::string &name, int *data, uint32_t count) override;

        void SetFloat(const std::string &name, float value) override;
        void SetFloat2(const std::string &name, const glm::vec2 &value) override;
        void SetFloat3(const std::string &name, const glm::vec3 &value) override;
        void SetFloat4(const std::string &name, const glm::vec4 &value) override;

        void SetMat2(const std::string &name, const glm::mat2 &value) override;
        void SetMat3(const std::string &name, const glm::mat3 &value) override;
        void SetMat4(const std::string &name, const glm::mat4 &value) override;

    private:
        uint32_t FindUniform(const std::string &name);
        bool UniformExists(const std::string &name);

    private:
        std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
        std::string ReadFile(const std::string& path);
        void Compile(std::unordered_map<GLenum, std::string>& shaderSources);

    private:
        std::unordered_map<std::string, ShaderUniform> m_UniformCache;

        std::string m_Name;
        uint32_t m_RendererID;

    private:
        void UploadUniformMat2(const std::string &name, const glm::mat2 &uniform);
        void UploadUniformMat3(const std::string &name, const glm::mat3 &uniform);
        void UploadUniformMat4(const std::string& name, const glm::mat4 &uniform);
        void UploadUniformFloat(const std::string &name, float uniform);
        void UploadUniformFloat2(const std::string &name, const glm::vec2 &uniform);
        void UploadUniformFloat3(const std::string &name, const glm::vec3 &uniform);
        void UploadUniformFloat4(const std::string &name, const glm::vec4 &uniform);
        void UploadUniformInt(const std::string &name, uint32_t uniform);
        void UploadUniformInt2(const std::string &name, const glm::vec2 &uniform);
        void UploadUniformInt3(const std::string &name, const glm::vec3 &uniform);
        void UploadUniformInt4(const std::string &name, const glm::vec4 &uniform);
        void UploadUniformIntArray(const std::string &name, int *data, uint32_t count);
    };
}



