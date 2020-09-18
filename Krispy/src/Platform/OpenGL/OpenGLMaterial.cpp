//
// Created by dallin on 9/15/20.
//

#include "OpenGLMaterial.h"

namespace Krispy {
    OpenGLMaterial::OpenGLMaterial(float shininess, const Ref <Texture2D> &diffuse, const Ref <Texture2D> &specular)
        : m_Shininess(shininess), m_Diffuse(diffuse), m_Specular(specular) {

    }

    void OpenGLMaterial::SetShininess(float shininess) {
        m_Shininess = shininess;
    }

    void OpenGLMaterial::SetDiffuseTexture(const Ref <Texture2D> &diffuse) {
        m_Diffuse = diffuse;
    }

    void OpenGLMaterial::SetSpecularTexture(const Ref <Texture2D> &specular) {
        m_Specular = specular;
    }
}
