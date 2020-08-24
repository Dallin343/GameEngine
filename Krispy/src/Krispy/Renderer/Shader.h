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

        static Shader* Create(const std::string& vertexSrc, const std::string& fragmentSrc);

#pragma mark --Upload Uniform Overloads--
        virtual void UploadUniform(const std::string& name, const glm::mat4& uniform) = 0;

    };
}



