#pragma once

#include <vector>
#include <functional>
#include "Model.h"
#include "ModelEntity.h"
#include "Entity.h"

class ModelEntity;

// Structure pour stocker les informations de collision
struct CollisionInfo {
    ModelEntity* entityA;
    ModelEntity* entityB;
    glm::vec3 penetrationVector; // Vecteur de séparation minimum
    float penetrationDepth;

    CollisionInfo() : entityA(nullptr), entityB(nullptr),
        penetrationVector(0.0f), penetrationDepth(0.0f) {
    }
};

class CollisionManager {
public:
    CollisionManager() = default;

    // Enregistrer une entité pour la détection de collision
    void registerEntity(ModelEntity* entity) {
        m_entities.push_back(entity);
    }

    void unregisterEntity(ModelEntity* entity) {
        m_entities.erase(
            std::remove(m_entities.begin(), m_entities.end(), entity),
            m_entities.end()
        );
    }

    // Vérifier toutes les collisions
    std::vector<CollisionInfo> checkCollisions() {
        std::vector<CollisionInfo> collisions;

        for (size_t i = 0; i < m_entities.size(); i++) {
            for (size_t j = i + 1; j < m_entities.size(); j++) {
                CollisionInfo info;
                if (checkCollision(m_entities[i], m_entities[j], info)) {
                    collisions.push_back(info);
                }
            }
        }

        return collisions;
    }

    // Vérifier collision entre deux entités spécifiques
    bool checkCollision(ModelEntity* entityA, ModelEntity* entityB,
        CollisionInfo& outInfo) {
        // Test rapide avec les sphères
        BoundingSphere sphereA = entityA->getModel()->getTransformedBoundingSphere(
            entityA->getModelMatrix());
        BoundingSphere sphereB = entityB->getModel()->getTransformedBoundingSphere(
            entityB->getModelMatrix());

        if (!sphereA.intersects(sphereB)) {
            return false;
        }

        // Test précis avec les boxes
        BoundingBox boxA = entityA->getWorldBoundingBox();
        BoundingBox boxB = entityB->getWorldBoundingBox();

        if (!boxA.intersects(boxB)) {
            return false;
        }

        // Calculer les informations de collision
        outInfo.entityA = entityA;
        outInfo.entityB = entityB;
        calculatePenetration(boxA, boxB, outInfo);

        return true;
    }

    // Résoudre une collision en séparant les entités
    void resolveCollision(const CollisionInfo& info, bool moveA = true, bool moveB = true) {
        if (!moveA && !moveB) return;

        glm::vec3 separation = info.penetrationVector * info.penetrationDepth;

        if (moveA && moveB) {
            // Les deux bougent
            info.entityA->setPosition(info.entityA->getPosition() - separation * 0.5f);
            info.entityB->setPosition(info.entityB->getPosition() + separation * 0.5f);
        }
        else if (moveA) {
            // Seulement A bouge
            info.entityA->setPosition(info.entityA->getPosition() - separation);
        }
        else {
            // Seulement B bouge
            info.entityB->setPosition(info.entityB->getPosition() + separation);
        }
    }

    // Raycast contre toutes les entités
    ModelEntity* raycast(const glm::vec3& origin, const glm::vec3& direction,
        float maxDistance, float& outDistance) {
        ModelEntity* closest = nullptr;
        float closestDist = maxDistance;

        for (auto* entity : m_entities) {
            float dist;
            if (entity->raycast(origin, direction, dist)) {
                if (dist < closestDist) {
                    closestDist = dist;
                    closest = entity;
                }
            }
        }

        outDistance = closestDist;
        return closest;
    }

    // Trouver toutes les entités dans un rayon
    std::vector<ModelEntity*> findEntitiesInRadius(const glm::vec3& center,
        float radius) {
        std::vector<ModelEntity*> result;

        for (auto* entity : m_entities) {
            BoundingSphere sphere = entity->getModel()->getTransformedBoundingSphere(
                entity->getModelMatrix());

            float distance = glm::length(sphere.center - center);
            if (distance < radius + sphere.radius) {
                result.push_back(entity);
            }
        }

        return result;
    }

private:
    std::vector<ModelEntity*> m_entities;

    void calculatePenetration(const BoundingBox& boxA, const BoundingBox& boxB,
        CollisionInfo& outInfo) {
        glm::vec3 centerA = boxA.getCenter();
        glm::vec3 centerB = boxB.getCenter();
        glm::vec3 delta = centerB - centerA;

        // Calculer la pénétration sur chaque axe
        glm::vec3 sizeA = boxA.getSize() * 0.5f;
        glm::vec3 sizeB = boxB.getSize() * 0.5f;

        glm::vec3 overlap = (sizeA + sizeB) - glm::abs(delta);

        // Trouver l'axe de pénétration minimum
        if (overlap.x < overlap.y && overlap.x < overlap.z) {
            outInfo.penetrationDepth = overlap.x;
            outInfo.penetrationVector = glm::vec3(delta.x > 0 ? 1.0f : -1.0f, 0, 0);
        }
        else if (overlap.y < overlap.z) {
            outInfo.penetrationDepth = overlap.y;
            outInfo.penetrationVector = glm::vec3(0, delta.y > 0 ? 1.0f : -1.0f, 0);
        }
        else {
            outInfo.penetrationDepth = overlap.z;
            outInfo.penetrationVector = glm::vec3(0, 0, delta.z > 0 ? 1.0f : -1.0f);
        }
    }
};
