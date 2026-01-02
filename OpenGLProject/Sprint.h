#pragma once

#include "Key.h"         // Classe de base pour toutes les touches
#include "configKeys.h"  // Contient les touches et configurations par defaut
#include <GLFW/glfw3.h>  // Librairie pour les touches et fenetres OpenGL

// Classe Sprint : represente la touche pour sprinter (courir plus vite)
// Herite de Key et definit son comportement
class Sprint : public Key {
public:
    // Constructeur
    // player : pointeur vers le joueur associe a cette touche
    Sprint(Player* player);

    // Destructeur vide
    virtual ~Sprint() {}
};
