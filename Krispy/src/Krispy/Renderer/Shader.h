//
// Created by dallin on 8/19/20.
//

#pragma once

namespace Krispy {
    class Shader {
    public:
        Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
        ~Shader();

        void Bind() const;
        void Unbind() const;

        uint32_t GetRendererID() const { return m_RendererID; }

    private:
        uint32_t m_RendererID;
    };
}



