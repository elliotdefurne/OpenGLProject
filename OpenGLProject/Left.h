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
    Left(Player* player);

    // Destructeur vide
    virtual ~Left() {}
};
