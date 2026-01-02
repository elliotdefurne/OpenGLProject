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
    Escape(Game* game) : Key(nullptr, "Escape", ConfigKeys::KEY_ESCAPE), m_game(game) {}

    // Destructeur vide
    virtual ~Escape() {}

    // Methode appelee lorsque la touche est appuyee
    void onPress(InputContext context) override;

    // Methode appelee lorsque la touche est relachee
    void onRelease(InputContext context) override;

    // Methode appelee chaque frame si la touche est maintenue (utile pour des menus interactifs)
    void ifPressed(InputContext context) override;

private:
    Game* m_game; // Pointeur vers le jeu pour pouvoir interagir avec son etat (ex : ouvrir menu)
};
