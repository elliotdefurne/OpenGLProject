#pragma once

#include <vector>
#include <stdexcept>
#include <string>
#include <iostream>
#include <filesystem>
#include <unordered_map>
#include <memory>
#include <glm/glm.hpp>                // Pour les vecteurs et matrices
#include <glm/ext/matrix_transform.hpp> // Pour les transformations 3D

#include "configKeys.h" // Contient la sensibilite par defaut de la souris

class Player;

// Classe Mouse : gere les mouvements de la souris pour le joueur
class Mouse {

public:
    // Constructeur
    // player : pointeur vers le joueur qui recevra les mouvements de souris
    Mouse(Player* player)
        : m_player(player), m_xpos(0.0f), m_ypos(0.0f), m_sensitivity(ConfigKeys::DEFAULT_MOUSE_SENSITIVITY) {
    }

    // Methode pour gerer le mouvement de la souris
    // xpos, ypos : position actuelle de la souris
    void handleMovement(double xpos, double ypos);

private:
    Player* m_player;      // Pointeur vers le joueur pour appliquer les rotations de la camera
    double m_xpos, m_ypos; // Dernieres positions connues de la souris
    const float m_sensitivity; // Sensibilite de la souris (vitesse de rotation)
};
