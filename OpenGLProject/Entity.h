#pragma once

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/fwd.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Renderer.h"
#include "Direction.h"
#include "constants.h"

// Namespace direction -> d�finit des constantes pour repr�senter des directions de mouvement
namespace direction {
    enum {
        FORWARD,   // Avancer
        BACKWARD,  // Reculer
        LEFT,      // Aller � gauche
        RIGHT,     // Aller � droite
        UP,        // Monter
        DOWN       // Descendre
    };
}

// Classe de base "Entity" : repr�sente un objet de la sc�ne (joueur, cube, cam�ra, etc.)
class Entity
{
public:
    // Constructeur : prend un pointeur vers le renderer
    Entity(Renderer* renderer);

    // Destructeur virtuel pour lib�rer correctement les ressources dans les classes d�riv�es
    ~Entity();

    // M�thodes virtuelles (peuvent �tre red�finies par les classes filles)
    // update() -> logique de mise � jour de l�entit� (mouvement, physique�)
    void virtual update();

    // draw() -> rendu de l�entit� (OpenGL)
    void virtual draw();

    // Getters
    glm::vec3 getPosition() const { return m_position; } // Retourne la position de l�entit�
    glm::vec3 getDirection() const { return m_direction->getDirectionVector(); }     // Retourne le point regard�/cibl�

protected:
    Renderer* m_renderer;   // Pointeur vers le Renderer (pour le timing/rendu)
    Direction* m_direction;
    glm::vec3 m_position;   // Position de l�entit� dans l�espace 3D
};
