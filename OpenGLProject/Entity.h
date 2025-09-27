#pragma once

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/fwd.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Renderer.h"
#include "constants.h"

// Namespace direction -> définit des constantes pour représenter des directions de mouvement
namespace direction {
    enum {
        FORWARD,   // Avancer
        BACKWARD,  // Reculer
        LEFT,      // Aller à gauche
        RIGHT,     // Aller à droite
        UP,        // Monter
        DOWN       // Descendre
    };
}

// Classe de base "Entity" : représente un objet de la scène (joueur, cube, caméra, etc.)
class Entity
{
public:
    // Constructeur : prend un pointeur vers le renderer
    Entity(Renderer* renderer);

    // Destructeur virtuel pour libérer correctement les ressources dans les classes dérivées
    ~Entity();

    // Méthodes virtuelles (peuvent être redéfinies par les classes filles)
    // update() -> logique de mise à jour de l’entité (mouvement, physique…)
    void virtual update();

    // draw() -> rendu de l’entité (OpenGL)
    void virtual draw();

    // Getters
    glm::vec3 getPosition() const { return m_position; } // Retourne la position de l’entité
    glm::vec3 getTarget() const { return m_target; }     // Retourne le point regardé/ciblé

protected:
    glm::vec3 m_target;     // Vecteur de direction ou "cible" de l’entité
    glm::vec3 m_position;   // Position de l’entité dans l’espace 3D
    Renderer* m_renderer;   // Pointeur vers le Renderer (pour le timing/rendu)
};
