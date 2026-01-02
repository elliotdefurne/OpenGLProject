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
    void onPress(InputContext context) override;

    // Methode appelee lorsque la touche est relachee
    void onRelease(InputContext context) override;

    // Methode appelee chaque frame si la touche est maintenue
    void ifPressed(InputContext context) override;
};
