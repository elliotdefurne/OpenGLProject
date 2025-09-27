#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "Entity.h"

// Classe qui repr�sente le joueur dans le jeu
// H�rite de Entity
// G�re le d�placement, le rendu et le traitement des entr�es clavier
class Player : public Entity {
public:
    // Constructeur : prend un pointeur vers le moteur de rendu
    // Appelle le constructeur de la classe de base Entity
    Player(Renderer* renderer) : Entity(renderer) {};

    // Destructeur par d�faut, aucune ressource suppl�mentaire � lib�rer
    ~Player() = default;

    // Met � jour la logique du joueur (position, mouvement, etc.)
    void update() override;

    // Dessine le joueur � l'�cran
    void draw() override;

    // Traite les touches de direction (FORWARD, BACKWARD, LEFT, RIGHT, UP, DOWN)
    void proccessDirectionKey(int direction);

    void processEscapeKey();
};
