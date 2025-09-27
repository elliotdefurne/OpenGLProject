#pragma once

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/fwd.hpp>

#include "Renderer.h"
#include "Direction.h"
#include "constants.h"

// Namespace direction : contient des constantes pour les directions de mouvement
namespace direction {
    enum {
        FORWARD,   // Avancer
        BACKWARD,  // Reculer
        LEFT,      // Aller a gauche
        RIGHT,     // Aller a droite
        UP,        // Monter
        DOWN       // Descendre
    };
}

// Classe Entity : classe de base pour tous les objets de la scene
// Exemple : joueur, cube, camera, etc.
class Entity
{
public:
    // Constructeur
    // renderer : pointeur vers le renderer, utile pour dessiner l'entité
    Entity(Renderer* renderer);

    // Destructeur virtuel pour que les classes derives liberent correctement leur memoire
    ~Entity();

    // Methode virtuelle : mise a jour de l'entité (mouvement, physique, logique)
    void virtual update();

    // Methode virtuelle : rendu de l'entité (envoie les donnees a OpenGL)
    void virtual draw();

    // Getters
    glm::vec3 getPosition() const { return m_position; }           // Position de l'entité
    glm::vec3 getDirection() const { return m_direction->getDirectionVector(); } // Direction regardee

protected:
    Renderer* m_renderer;     // Renderer pour dessiner et gerer le rendu
    Direction* m_direction;   // Orientation de l'entité (yaw/pitch)
    glm::vec3 m_position;     // Position dans l'espace 3D
};
