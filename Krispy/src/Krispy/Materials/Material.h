//
// Created by dallin on 9/15/20.
//

#pragma once

#include "Krispy/Renderer/Texture.h"

namespace Krispy {
    class Material {
    public:
        static Ref<Material> Create(float shininess, const Ref<Texture2D>& diffuse, const Ref<Texture2D>& specular);

        virtual void SetShininess(float shininess) = 0;
        virtual void SetDiffuseTexture(const Ref<Texture2D>& diffuse) = 0;
        virtual void SetSpecularTexture(const Ref<Texture2D>& specular) = 0;

        virtual float GetShininess() const = 0;
        virtual const Ref<Texture2D>& GetDiffuseTexture() const = 0;
        virtual const Ref<Texture2D>& GetSpecularTexture() const = 0;
    };
}



