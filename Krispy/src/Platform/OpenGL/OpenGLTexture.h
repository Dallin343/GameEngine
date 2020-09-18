//
// Created by dallin on 8/24/20.
//

#pragma once

#include "Krispy/Renderer/Texture.h"

#include <glad/glad.h>

namespace Krispy {
    class OpenGLTexture2D : public Texture2D {
    public:
        OpenGLTexture2D(const std::string& path, TextureType type = TextureType::Diffuse);
        OpenGLTexture2D(uint32_t width, uint32_t height, TextureType type);
        virtual ~OpenGLTexture2D();

        uint32_t GetWidth() const override { return m_Width; }
        uint32_t GetHeight() const override { return m_Height; }
        uint32_t GetRendererID() const { return m_RendererID; }

        TextureType GetType() const override;

        void SetData(void *data, uint32_t size) override;

        void Bind(uint32_t slot) const override;

        bool operator==(const Texture &other) const override {
            return m_RendererID == ((OpenGLTexture2D&)other).GetRendererID();
        }

    private:
        TextureType m_Type;
        std::string m_Path;
        uint32_t m_Width, m_Height;
        GLenum m_InternalFormat, m_DataFormat;
        uint32_t m_RendererID;
    };
}



