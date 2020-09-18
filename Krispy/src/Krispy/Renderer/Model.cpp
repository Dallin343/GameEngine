//
// Created by dallin on 9/14/20.
//

#include "Model.h"

#include <filesystem>

namespace Krispy {

    static TextureType AssimpTexToKrispyTex (aiTextureType type) {
        switch (type) {
            case aiTextureType_DIFFUSE: return TextureType::Diffuse;
            case aiTextureType_SPECULAR: return TextureType::Specular;
            case aiTextureType_AMBIENT: return TextureType::Ambient;

            case aiTextureType_NONE:
            case aiTextureType_EMISSIVE:
            case aiTextureType_HEIGHT:
            case aiTextureType_NORMALS:
            case aiTextureType_SHININESS:
            case aiTextureType_OPACITY:
            case aiTextureType_DISPLACEMENT:
            case aiTextureType_LIGHTMAP:
            case aiTextureType_REFLECTION:
            case aiTextureType_BASE_COLOR:
            case aiTextureType_NORMAL_CAMERA:
            case aiTextureType_EMISSION_COLOR:
            case aiTextureType_METALNESS:
            case aiTextureType_DIFFUSE_ROUGHNESS:
            case aiTextureType_AMBIENT_OCCLUSION:
            case aiTextureType_UNKNOWN:
                return TextureType::None;
        }
        return TextureType::None;
    }
    void Model::Draw(const Ref <Shader> &shader) {
        for (auto& m_Mesh : m_Meshes) {
            m_Mesh->Draw(shader);
        }
    }

    void Model::LoadModel() {
        Assimp::Importer import;
        const aiScene* scene = import.ReadFile(m_Path, aiProcess_Triangulate | aiProcess_FlipUVs);

        KRISPY_CORE_ASSERT(scene && !(scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) && scene->mRootNode, import.GetErrorString());

        std::filesystem::path filepath = m_Path;
        m_Directory = filepath.parent_path().string();

        ProcessNode(scene->mRootNode, scene);
    }

    void Model::ProcessNode(aiNode *node, const aiScene *scene) {
        for (uint32_t i = 0; i < node->mNumMeshes; i++) {
            aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
            m_Meshes.push_back(ProcessMesh(mesh, scene));
        }

        for (uint32_t i = 0; i < node->mNumChildren; i++) {
            ProcessNode(node->mChildren[i], scene);
        }
    }

    Ref<Mesh> Model::ProcessMesh(aiMesh *mesh, const aiScene *scene) {
        std::vector<MeshVertex> vertices;
        std::vector<uint32_t> indices;
        std::vector<Ref<Texture>> textures;

        //Process vertices
        for (uint32_t i = 0; i < mesh->mNumVertices; i++) {
            MeshVertex vertex;
            vertex.Position = {mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z};
            vertex.Normal = {mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z};

            if (mesh->mTextureCoords[0]) {
                vertex.TexCoords = {mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y};
            } else {
                vertex.TexCoords = glm::vec2(0.0f);
            }

            vertices.push_back(vertex);
        }

        for (uint32_t i = 0; i < mesh->mNumFaces; i++) {
            aiFace face = mesh->mFaces[i];
            for (uint32_t j = 0; j < face.mNumIndices; j++) {
                indices.push_back(face.mIndices[j]);
            }
        }

        if (mesh->mMaterialIndex >= 0) {
            aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
            std::vector<Ref<Texture>> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE);

            textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

            std::vector<Ref<Texture>> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR);
            textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
        }

        return Mesh::Create(vertices, indices, textures);
    }

    std::vector<Ref<Texture>> Model::LoadMaterialTextures(aiMaterial *mat, aiTextureType type) {
        std::vector<Ref<Texture>> textures;

        for (uint32_t i = 0; i < mat->GetTextureCount(type); i++) {
            aiString str;
            mat->GetTexture(type, i, &str);

            std::filesystem::path fullPath = m_Directory;
            fullPath.append(str.C_Str());

            Ref<Texture> texture = Texture2D::Create(fullPath.string(), AssimpTexToKrispyTex(type));
            textures.push_back(texture);
        }

        return textures;
    }
}


