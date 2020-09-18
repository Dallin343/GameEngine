//
// Created by dallin on 9/14/20.
//

#pragma once

#include "Shader.h"
#include "Mesh.h"
#include "Krispy/Renderer/Texture.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Krispy {
    class Model {
    public:
        Model(const std::string& path) : m_Path(path) { LoadModel(); }

        void Draw(const Ref<Shader>& shader);

    private:
        void LoadModel();
        void ProcessNode(aiNode* node, const aiScene* scene);
        Ref<Mesh> ProcessMesh(aiMesh* mesh, const aiScene* scene);
        std::vector<Ref<Texture>> LoadMaterialTextures(aiMaterial* mat, aiTextureType type);
    private:
        std::string m_Path;
        std::string m_Directory;

        std::vector<Ref<Mesh>> m_Meshes;
    };
}



