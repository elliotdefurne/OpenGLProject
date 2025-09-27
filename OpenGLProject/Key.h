#pragma once

#include <string>
#include <iostream>
#include "Player.h" // Classe Player represente le joueur dans le jeu

// Classe Key : classe de base abstraite pour toutes les touches du jeu
// Chaque touche derivee (Forward, Backward, Jump, Crouch...) herite de cette classe
class Key {
public:
    // Constructeur
    // player : pointeur vers le joueur associe a cette touche (peut etre nullptr pour des touches globales comme Escape)
    // name : nom de la touche (ex : "Forward", "Jump")
    // key : code de la touche physique (ex : GLFW_KEY_W)
    Key(Player* player, const std::string& name, int key)
        : m_name(name), m_key(key), m_player(player), m_isPressed(false) {
    }

    // Destructeur virtuel : necessaire pour l'heritage
    virtual ~Key() {}

    // Accesseurs
    const std::string& getKeyName() const { return m_name; } // Retourne le nom de la touche
    int getKey() const { return m_key; }                     // Retourne le code de la touche physique
    bool getStatus() const { return m_isPressed; }          // Retourne si la touche est actuellement appuyee

    // Methodes virtuelles pures : doivent etre redefinies dans les classes derives
    virtual void onPress() = 0;    // Appellee lorsque la touche est appuyee
    virtual void onRelease() = 0;  // Appellee lorsque la touche est relachee
    virtual void ifPressed() = 0;  // Appellee chaque frame si la touche est maintenue

protected:
    Player* m_player;       // Pointeur vers le joueur associe a la touche
    const std::string m_name; // Nom de la touche
    const int m_key;          // Code de la touche physique
    bool m_isPressed;         // Etat de la touche (true si appuyee, false sinon)
};
