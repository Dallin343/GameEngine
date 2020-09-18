//
// Created by dallin on 9/15/20.
//

#pragma once

#include "Krispy/Materials/Material.h"

namespace Krispy {
    class OpenGLMaterial : public Material {
    public:
        OpenGLMaterial(float shininess, const Ref<Texture2D>& diffuse, const Ref<Texture2D>& specular);

        void SetShininess(float shininess) override;
        void SetDiffuseTexture(const Ref <Texture2D> &diffuse) override;
        void SetSpecularTexture(const Ref <Texture2D> &specular) override;

        float GetShininess() const override { return m_Shininess; };
        const Ref<Texture2D>& GetDiffuseTexture() const override { return m_Diffuse; };
        const Ref<Texture2D>& GetSpecularTexture() const override { return m_Specular; };

    private:
        float m_Shininess;
        Ref<Texture2D> m_Diffuse;
        Ref<Texture2D> m_Specular;
    };
}



