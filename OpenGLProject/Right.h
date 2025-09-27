#pragma once

#include "Key.h"         // Classe de base pour toutes les touches
#include "configKeys.h"  // Contient les touches et configurations par defaut
#include <GLFW/glfw3.h>  // Librairie pour les touches et fenetres OpenGL

// Classe Right : represente la touche pour se deplacer a droite
// Herite de Key et definit son comportement
class Right : public Key {
public:
    // Constructeur
    // player : pointeur vers le joueur associe a cette touche
    Right(Player* player) : Key(player, "Right", ConfigKeys::KEY_RIGHT) {}

    // Destructeur vide
    virtual ~Right() {}

    // Methode appelee lorsque la touche est appuyee
    void onPress() override;

    // Methode appelee lorsque la touche est relachee
    void onRelease() override;

    // Methode appelee chaque frame tant que la touche est maintenue
    void ifPressed() override;
};
