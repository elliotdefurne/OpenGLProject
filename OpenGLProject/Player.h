#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "Entity.h"

// Classe qui représente le joueur dans le jeu
// Hérite de Entity
// Gère le déplacement, le rendu et le traitement des entrées clavier
class Player : public Entity {
public:
    // Constructeur : prend un pointeur vers le moteur de rendu
    // Appelle le constructeur de la classe de base Entity
    Player(Renderer* renderer) : Entity(renderer) {};

    // Destructeur par défaut, aucune ressource supplémentaire à libérer
    ~Player() = default;

    // Met à jour la logique du joueur (position, mouvement, etc.)
    void update() override;

    // Dessine le joueur à l'écran
    void draw() override;

    // Traite les touches de direction (FORWARD, BACKWARD, LEFT, RIGHT, UP, DOWN)
    void proccessDirectionKey(int direction);

    void processEscapeKey();
};
