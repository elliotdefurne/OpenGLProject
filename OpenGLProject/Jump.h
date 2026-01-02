#pragma once

#include "Key.h"         // Classe de base pour toutes les touches
#include "configKeys.h"  // Contient les touches et configurations par defaut
#include <GLFW/glfw3.h>  // Librairie pour la gestion des touches et fenetres OpenGL

// Classe Jump : represente la touche pour sauter
// Herite de Key pour definir son comportement specifique
class Jump : public Key {
public:
    // Constructeur
    // player : pointeur vers le joueur associe a cette touche
    // Appelle le constructeur de Key avec le nom "Jump" et la touche associee
    Jump(Player* player);

    // Destructeur vide, necessaire pour l'heritage
    virtual ~Jump() {}
};
