//
// Created by dallin on 8/19/20.
//

#pragma once

#include <string>
#include <glm/glm.hpp>

namespace Krispy {

    struct ShaderUniform {
        std::string Name;
        ShaderDataType Type;
        bool Cached = false;
        uint32_t Location = 0;
    };

    class Shader {
    public:
        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual uint32_t GetRendererID() const = 0;
        virtual const std::string& GetName() const = 0;

        static Ref<Shader> Create(const std::string& path);
        static Ref<Shader> Create(const std::string &name, const std::string &vertexSrc, const std::string &fragmentSrc);

        virtual void SetInt(const std::string& name, int value) = 0;
        virtual void SetInt2(const std::string& name, const glm::vec2& value) = 0;
        virtual void SetInt3(const std::string& name, const glm::vec3& value) = 0;
        virtual void SetInt4(const std::string& name, const glm::vec4& value) = 0;
        virtual void SetIntArray(const std::string& name, int* data, uint32_t count) = 0;
        virtual void SetFloat(const std::string& name, float value) = 0;
        virtual void SetFloat2(const std::string& name, const glm::vec2& value) = 0;
        virtual void SetFloat3(const std::string& name, const glm::vec3& value) = 0;
        virtual void SetFloat4(const std::string& name, const glm::vec4& value) = 0;
        virtual void SetMat2(const std::string& name, const glm::mat2& value) = 0;
        virtual void SetMat3(const std::string& name, const glm::mat3& value) = 0;
        virtual void SetMat4(const std::string& name, const glm::mat4& value) = 0;
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



