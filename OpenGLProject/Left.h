#pragma once

#include "Key.h"         // Classe de base pour toutes les touches
#include "configKeys.h"  // Contient les touches et configurations par defaut
#include <GLFW/glfw3.h>  // Librairie pour les touches et fenetres OpenGL

// Classe Left : represente la touche pour se deplacer a gauche
// Herite de Key et definit son comportement
class Left : public Key {
public:
    // Constructeur
    // player : pointeur vers le joueur associe a cette touche
    Left(Player* player) : Key(player, "Left", ConfigKeys::KEY_LEFT) {}

    // Destructeur vide
    virtual ~Left() {}

    // Methode appelee lorsque la touche est appuyee
    void onPress() override {
        if (!m_isPressed) {
            m_isPressed = true; // Change l'etat pour indiquer que la touche est appuyee
        }
    }

    // Methode appelee lorsque la touche est relachee
    void onRelease() override {
        if (m_isPressed) {
            m_isPressed = false; // Change l'etat pour indiquer que la touche est relachee
        }
    }

    // Methode appelee chaque frame si la touche est maintenue
    void ifPressed() override {
        if (m_isPressed) {
            m_player->processDirectionKey(direction::LEFT);
            // Demande au joueur de se deplacer a gauche
            // "processDirectionKey" est la methode du joueur qui gere le deplacement
        }
    }
};
