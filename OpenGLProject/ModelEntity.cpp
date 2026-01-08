#include "ModelEntity.h"
#include "Model.h"
#include "Shader.h"
#include <memory>

ModelEntity::ModelEntity(Renderer* renderer, const std::string& modelPath,
	TextureManager* textureManager)
	: Entity(renderer) {
	m_model = std::make_unique<Model>(modelPath, textureManager);
}

ModelEntity::~ModelEntity() {
    // Le destructeur unique_ptr s'occupe de libérer la mémoire du modèle
}

void ModelEntity::draw(Shader* shader) {
    shader->use();

    // Matrice de transformation
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, m_position);

    // Rotation basée sur la direction
    glm::vec3 dir = m_direction->getDirectionVector();
    float yaw = atan2(dir.x, dir.z);
    model = glm::rotate(model, yaw, glm::vec3(0, 1, 0));

    shader->setMat4("model", model);

    // Dessiner le modèle
    m_model->draw(*shader);
}

void ModelEntity::drawDebug(Shader* shader) {
    shader->use();

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, m_position);

    glm::vec3 dir = m_direction->getDirectionVector();
    float yaw = atan2(dir.x, dir.z);
    model = glm::rotate(model, yaw, glm::vec3(0, 1, 0));

    shader->setMat4("model", model);

    // Dessiner la bounding box
    m_model->drawBoundingBox(*shader);
}

bool ModelEntity::checkCollision(const ModelEntity& other) const {
    glm::mat4 thisMatrix = getModelMatrix();
    glm::mat4 otherMatrix = other.getModelMatrix();

    return m_model->checkCollision(*other.m_model, thisMatrix, otherMatrix);
}

bool ModelEntity::raycast(const glm::vec3& origin, const glm::vec3& direction,
    float& distance) const {
    glm::mat4 modelMatrix = getModelMatrix();
    return m_model->raycast(origin, direction, modelMatrix, distance);
}

BoundingBox ModelEntity::getWorldBoundingBox() const {
    return m_model->getTransformedBoundingBox(getModelMatrix());
}

glm::mat4 ModelEntity::getModelMatrix() const {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, m_position);

    glm::vec3 dir = m_direction->getDirectionVector();
    float yaw = atan2(dir.x, dir.z);
    model = glm::rotate(model, yaw, glm::vec3(0, 1, 0));

    return model;
}