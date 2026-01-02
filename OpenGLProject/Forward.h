#pragma once

#include "Key.h"         // Classe de base pour toutes les touches
#include "configKeys.h"  // Contient les touches et configurations par defaut
#include <GLFW/glfw3.h>  // Librairie pour les touches et fenetres OpenGL

// Classe Forward : represente la touche pour avancer
// Herite de Key pour definir son comportement specifique
class Forward : public Key {
public:
    // Constructeur
    // player : pointeur vers le joueur associe a cette touche
    // Appelle le constructeur de Key avec le nom "Forward" et la touche associee
    Forward(Player* player) : Key(player, "Forward", ConfigKeys::KEY_FORWARD) {}

    // Destructeur vide, necessaire pour l'heritage
    virtual ~Forward() {}

    // Methode appelee lorsque la touche est appuyee
    void onPress(InputContext context) override;

    // Methode appelee lorsque la touche est relachee
    void onRelease(InputContext context) override;

    // Methode appelee chaque frame si la touche est maintenue
    void ifPressed(InputContext context) override;
};
