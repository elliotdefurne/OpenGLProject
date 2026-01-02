#pragma once

#include "Key.h"         // Classe de base pour toutes les touches
#include "configKeys.h"  // Contient les touches et configurations par defaut
#include <GLFW/glfw3.h>  // Librairie pour les touches et fenetres OpenGL

// Classe Crouch : represente la touche pour s'accroupir
// Elle herite de Key, ce qui permet de definir son comportement specifique
class Crouch : public Key {
public:
    // Constructeur
    // player : pointeur vers le joueur associe a cette touche
    // Appelle le constructeur de Key avec le nom "Crouch" et la touche associee
    Crouch(Player* player) : Key(player, "Crouch", ConfigKeys::KEY_CROUCH) {}

    // Destructeur vide, necessaire pour l'heritage
    virtual ~Crouch() {}

    // Methode appelee lorsque la touche est appuyee
    void onPress(InputContext context) override;

    // Methode appelee lorsque la touche est relachee
    void onRelease(InputContext context) override;

    // Methode appelee a chaque frame tant que la touche est maintenue
    void ifPressed(InputContext context) override;
};
