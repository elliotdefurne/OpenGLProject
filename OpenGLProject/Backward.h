#pragma once

// Inclusion des fichiers necessaires
#include "Key.h"         // Classe de base pour les touches
#include "configKeys.h"  // Contient les definitions des touches configurables
#include <GLFW/glfw3.h>  // Librairie pour la gestion des entrées et fenetres OpenGL

// Classe Backward : represente la touche pour reculer
// Elle herite de la classe Key, ce qui permet de definir son comportement
class Backward : public Key {
public:
    // Constructeur
    // player : pointeur vers le joueur associe a cette touche
    // Appelle le constructeur de Key avec le nom de la touche et la touche associee
    Backward(Player* player) : Key(player, "Backward", ConfigKeys::KEY_BACKWARD) {}

    // Destructeur (vide ici, mais necessaire pour l'heritage)
    virtual ~Backward() {}

    // Methode appelee lorsque la touche est appuyee
    void onPress() override;

    // Methode appelee lorsque la touche est relachee
    void onRelease() override;

    // Methode appelee a chaque frame si la touche est maintenue enfoncee
    void ifPressed() override;
};
