#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vector>

class Model;
class Shader;
class Mesh;
class Texture;

class Model {
public:
    Model(char* path) { loadModel(path); }
    void draw(Shader& shader);
private:
    // model data
    std::vector<Mesh> m_meshes;
    std::string m_directory;

    void loadModel(std::string path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};