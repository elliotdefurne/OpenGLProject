#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "Entity.h"

// Classe Player : repr�sente le joueur dans le jeu
// H�rite de Entity et g�re le d�placement, la vue et le rendu
class Player : public Entity {
public:
    // Constructeur : prend un pointeur vers le moteur de rendu
    // Appelle le constructeur de la classe de base Entity
    Player(Renderer* renderer) : Entity(renderer) {};

    // Destructeur par d�faut, aucune ressource suppl�mentaire � lib�rer
    ~Player() = default;

    // Met � jour la logique du joueur chaque frame
    // D�placement, animations, actions
    void update() override;

    // Dessine le joueur � l'�cran
    void draw() override;

    // Traite les touches de direction
    // direction : valeur parmi direction::FORWARD, BACKWARD, LEFT, RIGHT, UP, DOWN
    void processDirectionKey(int direction);

    // Traite les mouvements de la souris
    // yaw : rotation horizontale
    // pitch : rotation verticale
    void processMouseMovements(double yaw, double pitch);
};
