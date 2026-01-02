#pragma once

#include "Key.h"         // Classe de base pour toutes les touches
#include "configKeys.h"  // Contient les touches et configurations par defaut

class Game; // Declaration anticipee : permet d'utiliser un pointeur vers Game sans inclure le fichier complet ici

// Classe Escape : represente la touche Escape
// Utilisee par exemple pour ouvrir le menu ou quitter le jeu
// Herite de Key pour reutiliser le systeme de touches
class Escape : public Key {
public:
    // Constructeur
    // game : pointeur vers le jeu associe a cette touche
    // Appelle le constructeur de Key avec nullptr pour le joueur (Escape n'agit pas sur un joueur directement)
    Escape(Game* game);

    // Destructeur vide
    virtual ~Escape() {}
private:
    Game* m_game; // Pointeur vers le jeu pour pouvoir interagir avec son etat (ex : ouvrir menu)
};
