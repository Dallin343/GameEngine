//
// Created by dallin on 8/19/20.
//

#pragma once

#include <string>
#include <glm/glm.hpp>

namespace Krispy {
    class Shader {
    public:
        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual uint32_t GetRendererID() const = 0;
        virtual const std::string& GetName() const = 0;

        static Ref<Shader> Create(const std::string& path);
        static Ref <Krispy::Shader>
            Create(const std::string &name, const std::string &vertexSrc, const std::string &fragmentSrc);

#pragma mark --Upload Uniforms--
        virtual void UploadUniformMat2(const std::string& name, const glm::mat2& uniform) = 0;
        virtual void UploadUniformMat3(const std::string& name, const glm::mat3& uniform) = 0;
        virtual void UploadUniformMat4(const std::string& name, const glm::mat4& uniform) = 0;
        virtual void UploadUniformFloat(const std::string& name, float uniform) = 0;
        virtual void UploadUniformFloat2(const std::string& name, const glm::vec2& uniform) = 0;
        virtual void UploadUniformFloat3(const std::string& name, const glm::vec3& uniform) = 0;
        virtual void UploadUniformFloat4(const std::string& name, const glm::vec4& uniform) = 0;
        virtual void UploadUniformUInt(const std::string& name, uint32_t uniform) = 0;
        virtual void UploadUniformUInt2(const std::string& name, const glm::vec2& uniform) = 0;
        virtual void UploadUniformUInt3(const std::string& name, const glm::vec3& uniform) = 0;
        virtual void UploadUniformUInt4(const std::string& name, const glm::vec4& uniform) = 0;

    };

    class ShaderLibrary {
    public:
        void Add(const std::string& name, const Ref<Shader>& shader);
        void Add(const Ref<Shader>& shader);
        Ref<Shader> Load(const std::string& path);
        Ref<Shader> Load(const std::string& name, const std::string& path);

        Ref<Shader> Get(const std::string& name);

        bool Exists(const std::string& name) const;

    private:
        std::unordered_map<std::string, Ref<Shader>> m_Shaders;
    };
}



