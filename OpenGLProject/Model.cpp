#include "Model.h"
#include "Mesh.h"
#include "Shader.h"
#include "TextureManager.h"
#include "Vertex.h"
#include <iostream>
#include <exception>

// ===== BoundingBox =====
BoundingBox BoundingBox::transform(const glm::mat4& matrix) const {
    BoundingBox result;

    // Les 8 coins de la box
    glm::vec3 corners[8] = {
        glm::vec3(min.x, min.y, min.z),
        glm::vec3(max.x, min.y, min.z),
        glm::vec3(min.x, max.y, min.z),
        glm::vec3(max.x, max.y, min.z),
        glm::vec3(min.x, min.y, max.z),
        glm::vec3(max.x, min.y, max.z),
        glm::vec3(min.x, max.y, max.z),
        glm::vec3(max.x, max.y, max.z)
    };

    // Transformer chaque coin et recalculer min/max
    for (int i = 0; i < 8; i++) {
        glm::vec4 transformed = matrix * glm::vec4(corners[i], 1.0f);
        result.expand(glm::vec3(transformed));
    }

    return result;
}

bool BoundingBox::intersects(const BoundingBox& other) const {
    return (min.x <= other.max.x && max.x >= other.min.x) &&
        (min.y <= other.max.y && max.y >= other.min.y) &&
        (min.z <= other.max.z && max.z >= other.min.z);
}

// ===== BoundingSphere =====
BoundingSphere::BoundingSphere(const BoundingBox& box) {
    center = box.getCenter();
    radius = glm::length(box.getSize()) * 0.5f;
}

BoundingSphere BoundingSphere::transform(const glm::mat4& matrix) const {
    BoundingSphere result;
    glm::vec4 transformedCenter = matrix * glm::vec4(center, 1.0f);
    result.center = glm::vec3(transformedCenter);

    // Pour le rayon, on prend l'échelle maximale
    glm::vec3 scale;
    scale.x = glm::length(glm::vec3(matrix[0]));
    scale.y = glm::length(glm::vec3(matrix[1]));
    scale.z = glm::length(glm::vec3(matrix[2]));
    result.radius = radius * glm::max(glm::max(scale.x, scale.y), scale.z);

    return result;
}

bool BoundingSphere::intersects(const BoundingSphere& other) const {
    float distance = glm::length(center - other.center);
    return distance < (radius + other.radius);
}

// ===== Model =====
Model::Model(const std::string& path, TextureManager* textureManager)
    : m_textureManager(textureManager), m_debugBoundingBoxMesh(nullptr) {
    loadModel(path);
    calculateBoundingBox();
    calculateBoundingSphere();
    createDebugBoundingBoxMesh();
}

void Model::draw(Shader& shader) {
    for (auto* mesh : m_meshes) {
        mesh->draw();
    }
}

void Model::drawBoundingBox(Shader& shader) {
    if (m_debugBoundingBoxMesh) {
        shader.use();
        shader.setVec3("color", glm::vec3(0.0f, 1.0f, 0.0f)); // Vert
        m_debugBoundingBoxMesh->draw();
    }
}

BoundingBox Model::getTransformedBoundingBox(const glm::mat4& modelMatrix) const {
    return m_boundingBox.transform(modelMatrix);
}

BoundingSphere Model::getTransformedBoundingSphere(const glm::mat4& modelMatrix) const {
    return m_boundingSphere.transform(modelMatrix);
}

bool Model::checkCollision(const Model& other, const glm::mat4& thisMatrix,
    const glm::mat4& otherMatrix) const {
    // Test rapide avec les sphères
    BoundingSphere thisSphere = getTransformedBoundingSphere(thisMatrix);
    BoundingSphere otherSphere = other.getTransformedBoundingSphere(otherMatrix);

    if (!thisSphere.intersects(otherSphere)) {
        return false; // Pas de collision
    }

    // Test précis avec les boxes
    BoundingBox thisBox = getTransformedBoundingBox(thisMatrix);
    BoundingBox otherBox = other.getTransformedBoundingBox(otherMatrix);

    return thisBox.intersects(otherBox);
}

bool Model::raycast(const glm::vec3& origin, const glm::vec3& direction,
    const glm::mat4& modelMatrix, float& distance) const {
    // Transformer le rayon dans l'espace du modèle
    glm::mat4 invMatrix = glm::inverse(modelMatrix);
    glm::vec3 localOrigin = glm::vec3(invMatrix * glm::vec4(origin, 1.0f));
    glm::vec3 localDir = glm::normalize(glm::vec3(invMatrix * glm::vec4(direction, 0.0f)));

    // Test d'intersection rayon-box (algorithme slab)
    glm::vec3 tMin = (m_boundingBox.min - localOrigin) / localDir;
    glm::vec3 tMax = (m_boundingBox.max - localOrigin) / localDir;

    glm::vec3 t1 = glm::min(tMin, tMax);
    glm::vec3 t2 = glm::max(tMin, tMax);

    float tNear = glm::max(glm::max(t1.x, t1.y), t1.z);
    float tFar = glm::min(glm::min(t2.x, t2.y), t2.z);

    if (tNear > tFar || tFar < 0) {
        return false;
    }

    distance = tNear > 0 ? tNear : tFar;
    return true;
}

void Model::loadModel(const std::string& path) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path,
        aiProcess_Triangulate |
        aiProcess_FlipUVs |
        aiProcess_CalcTangentSpace |
        aiProcess_GenNormals);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cerr << "ERREUR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return;
    }

    m_directory = path.substr(0, path.find_last_of('/'));
    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene) {
    // Traiter tous les meshes du noeud
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        m_meshes.push_back(processMesh(mesh, scene));
    }

    // Traiter récursivement les enfants
    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        processNode(node->mChildren[i], scene);
    }
}

Mesh* Model::processMesh(aiMesh* mesh, const aiScene* scene) {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<unsigned int> textureIDs;

    // Vertices
    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        // Position

        glm::vec3 position, normal = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec2 texCoords = glm::vec2(0.0f, 0.0f);

        position = glm::vec3(
            mesh->mVertices[i].x,
            mesh->mVertices[i].y,
            mesh->mVertices[i].z
        );

        // Normales
        if (mesh->HasNormals()) {
            normal = glm::vec3(
                mesh->mNormals[i].x,
                mesh->mNormals[i].y,
                mesh->mNormals[i].z
            );
        }

        // Coordonnées de texture
        if (mesh->mTextureCoords[0]) {
            texCoords = glm::vec2(
                mesh->mTextureCoords[0][i].x,
                mesh->mTextureCoords[0][i].y
            );
        }
        else {
            texCoords = glm::vec2(0.0f, 0.0f);
        }

        Vertex vertex = Vertex(position.x, position.y, position.z, normal.x, normal.y, normal.z, texCoords.x, texCoords.y);
        vertices.push_back(vertex);
    }

    // Indices
    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

    // Textures
    if (mesh->mMaterialIndex >= 0) {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

        // Diffuse
        std::vector<unsigned int> diffuseMaps = loadMaterialTextures(
            material, aiTextureType_DIFFUSE);
        textureIDs.insert(textureIDs.end(), diffuseMaps.begin(), diffuseMaps.end());

        // Specular
        std::vector<unsigned int> specularMaps = loadMaterialTextures(
            material, aiTextureType_SPECULAR);
        textureIDs.insert(textureIDs.end(), specularMaps.begin(), specularMaps.end());
    }

    return new Mesh(vertices, indices);
}

std::vector<unsigned int> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type) {
    std::vector<unsigned int> textureIDs;

    if (!m_textureManager) {
        return textureIDs;
    }

    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
        aiString str;
        mat->GetTexture(type, i, &str);

        std::string texturePath = m_directory + "/" + std::string(str.C_Str());

        try {
            Texture* texture = m_textureManager->getTexture(texturePath);
            textureIDs.push_back(texture->getID());
        }
        catch (const std::exception& e) {
            std::cerr << "Échec du chargement de texture: " << texturePath << std::endl;
        }
    }

    return textureIDs;
}

void Model::calculateBoundingBox() {
    m_boundingBox = BoundingBox();

    for (auto* mesh : m_meshes) {
        const std::vector<Vertex>& vertices = mesh->getVertices();
        for (const auto& vertex : vertices) {
            m_boundingBox.expand(vertex.getPositions());
        }
    }
}

void Model::calculateBoundingSphere() {
    m_boundingSphere = BoundingSphere(m_boundingBox);
}

void Model::createDebugBoundingBoxMesh() {
    glm::vec3 min = m_boundingBox.min;
    glm::vec3 max = m_boundingBox.max;

    // 8 sommets de la box
    std::vector<Vertex> vertices = {
        Vertex(min.x, min.y, min.z),
        Vertex(max.x, min.y, min.z),
        Vertex(max.x, max.y, min.z),
        Vertex(min.x, max.y, min.z),
        Vertex(min.x, min.y, max.z),
        Vertex(max.x, min.y, max.z),
        Vertex(max.x, max.y, max.z),
        Vertex(min.x, max.y, max.z)
    };

    // Indices pour dessiner les lignes de la box
    std::vector<unsigned int> indices = {
        // Face avant
        0, 1, 1, 2, 2, 3, 3, 0,
        // Face arrière
        4, 5, 5, 6, 6, 7, 7, 4,
        // Connexions
        0, 4, 1, 5, 2, 6, 3, 7
    };

    m_debugBoundingBoxMesh = new Mesh(vertices, indices);
}