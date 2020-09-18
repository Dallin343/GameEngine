//
// Created by dallin on 8/24/20.
//

#include "OpenGLTexture.h"

#include "stb_image.h"

#include <glad/glad.h>

namespace Krispy {

#pragma mark --OpenGLTexture2D--

    OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height, TextureType type)
    : m_Width(width), m_Height(height), m_Type(type) {

        KRISPY_PROFILE_FUNCTION();

        m_InternalFormat = GL_RGBA8;
        m_DataFormat = GL_RGBA;

        glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
        glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);

        glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

    }

    OpenGLTexture2D::OpenGLTexture2D(const std::string &path, TextureType type): m_Path(path), m_Type(type) {
        KRISPY_PROFILE_FUNCTION();

        int width, height, channels;
        stbi_set_flip_vertically_on_load(true);
        stbi_uc *data = stbi_load(path.c_str(), &width, &height, &channels, 0);
        KRISPY_CORE_ASSERT(data, "Texture image failed to load!");

        m_Width = width;
        m_Height = height;

        m_InternalFormat = GL_RGBA8;
        m_DataFormat = GL_RGBA;

        if (channels == 1) {
            m_InternalFormat = GL_RED;
            m_DataFormat = GL_R8;
        } else if (channels == 3) {
            m_InternalFormat = GL_RGB8;
            m_DataFormat = GL_RGB;
        }

        glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
        glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);
        glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);

        stbi_image_free(data);
    }

    OpenGLTexture2D::~OpenGLTexture2D() {
        KRISPY_PROFILE_FUNCTION();

        glDeleteTextures(1, &m_RendererID);
    }

    void OpenGLTexture2D::Bind(uint32_t slot) const {
        KRISPY_PROFILE_FUNCTION();

        glBindTextureUnit(slot, m_RendererID);
    }

    void OpenGLTexture2D::SetData(void *data, uint32_t size) {
        KRISPY_PROFILE_FUNCTION();

        glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
    }

    TextureType OpenGLTexture2D::GetType() const {
        return TextureType::None;
    }


//#pragma mark --OpenGLTexture3D--
//
//    OpenGLTexture3D::OpenGLTexture3D(const std::string &path, TextureType type) : m_Type(type) {
//        KRISPY_PROFILE_FUNCTION();
//
//        int width, height, channels;
//        stbi_set_flip_vertically_on_load(true);
//        stbi_uc *data = stbi_load(path.c_str(), &width, &height, &channels, 0);
//        KRISPY_CORE_ASSERT(data, "Texture image failed to load!");
//
//        m_Width = width;
//        m_Height = height;
//
//        if (channels == 1) {
//            m_InternalFormat = GL_R8;
//            m_DataFormat = GL_RED;
//        } else if (channels == 3) {
//            m_InternalFormat = GL_RGB8;
//            m_DataFormat = GL_RGB;
//        } else if (channels == 4) {
//            m_InternalFormat = GL_RGBA8;
//            m_DataFormat = GL_RGBA;
//        }
//
//        glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
//        glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);
//        glGenerateMipmap(GL_TEXTURE_2D);
//
//        glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
//        glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
//        glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//        glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//        glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
//
//        stbi_image_free(data);
//    }
//
//    OpenGLTexture3D::OpenGLTexture3D(uint32_t width, uint32_t height) : m_Width(width), m_Height(height) {
//        KRISPY_PROFILE_FUNCTION();
//
//        m_InternalFormat = GL_RGBA8;
//        m_DataFormat = GL_RGBA;
//
//        glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
//        glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);
//
//        glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//        glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//
//        glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
//        glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
//    }
//
//    OpenGLTexture3D::~OpenGLTexture3D() {
//        KRISPY_PROFILE_FUNCTION();
//
//        glDeleteTextures(1, &m_RendererID);
//    }
//
//    void OpenGLTexture3D::SetData(void *data, uint32_t size) {
//        KRISPY_PROFILE_FUNCTION();
//
//        glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
//    }
//
//    void OpenGLTexture3D::Bind(uint32_t slot) const {
//        KRISPY_PROFILE_FUNCTION();
//
//        glBindTextureUnit(slot, m_RendererID);
//    }
}