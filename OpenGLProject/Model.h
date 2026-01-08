#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>

class Shader;
class Mesh;
class TextureManager;

// Structure pour représenter une bounding box
struct BoundingBox {
    glm::vec3 min;
    glm::vec3 max;

    BoundingBox() : min(FLT_MAX), max(-FLT_MAX) {}

    void expand(const glm::vec3& point) {
        min = glm::min(min, point);
        max = glm::max(max, point);
    }

    glm::vec3 getCenter() const {
        return (min + max) * 0.5f;
    }

    glm::vec3 getSize() const {
        return max - min;
    }

    // Transforme la bounding box avec une matrice
    BoundingBox transform(const glm::mat4& matrix) const;

    // Vérifie la collision avec une autre bounding box
    bool intersects(const BoundingBox& other) const;
};

// Structure pour une hitbox sphérique (plus simple pour certains objets)
struct BoundingSphere {
    glm::vec3 center;
    float radius;

    BoundingSphere() : center(0.0f), radius(0.0f) {}
    BoundingSphere(const BoundingBox& box);

    // Transforme la sphère avec une matrice
    BoundingSphere transform(const glm::mat4& matrix) const;

    // Vérifie la collision avec une autre sphère
    bool intersects(const BoundingSphere& other) const;
};

class Model {
public:
    // Constructeur avec chemin du modèle et texture manager
    Model(const std::string& path, TextureManager* textureManager = nullptr);

    // Dessine le modèle
    void draw(Shader& shader);

    // Dessine la bounding box (pour debug)
    void drawBoundingBox(Shader& shader);

    // Getters pour les hitbox
    const BoundingBox& getBoundingBox() const { return m_boundingBox; }
    const BoundingSphere& getBoundingSphere() const { return m_boundingSphere; }

    // Obtenir la bounding box transformée
    BoundingBox getTransformedBoundingBox(const glm::mat4& modelMatrix) const;
    BoundingSphere getTransformedBoundingSphere(const glm::mat4& modelMatrix) const;

    // Vérifier collision avec un autre modèle
    bool checkCollision(const Model& other, const glm::mat4& thisMatrix,
        const glm::mat4& otherMatrix) const;

    // Raycast - renvoie true si le rayon touche le modèle
    bool raycast(const glm::vec3& origin, const glm::vec3& direction,
        const glm::mat4& modelMatrix, float& distance) const;

private:
    std::vector<Mesh*> m_meshes;
    std::string m_directory;
    TextureManager* m_textureManager;

    // Hitbox du modèle entier
    BoundingBox m_boundingBox;
    BoundingSphere m_boundingSphere;

    // Mesh pour visualiser la bounding box
    Mesh* m_debugBoundingBoxMesh;

    // Chargement
    void loadModel(const std::string& path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh* processMesh(aiMesh* mesh, const aiScene* scene);

    // Calcul des hitbox
    void calculateBoundingBox();
    void calculateBoundingSphere();

    // Création du mesh de debug
    void createDebugBoundingBoxMesh();

    // Helpers pour les textures
    std::vector<unsigned int> loadMaterialTextures(aiMaterial* mat,
        aiTextureType type);
};