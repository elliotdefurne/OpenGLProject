#pragma once

#include <vector>
#include <stdexcept>
#include <string>
#include <iostream>
#include <filesystem>
#include <unordered_map>
#pragma warning(push)
#pragma warning(disable: 4244)
#include <memory>
#pragma warning(pop)
#include <glad/glad.h>   // Gestion des fonctions OpenGL
#include <GLFW/glfw3.h>  // Gestion des fenetres et des touches

// Déclarations anticipées pour eviter d'inclure tous les fichiers
class Game;
class Key;
class Window;
class Player;
class Mouse;

// Classe KeyManager : gere toutes les touches du jeu et leur etat
class KeyManager {
public:
    // Constructeur
    // game : pointeur vers le jeu
    // window : pointeur vers la fenetre
    // player : pointeur vers le joueur
    // Appelle loadKeys() pour initialiser toutes les touches
    KeyManager(Game* game, Window* window, Player* player)
        : m_game(game), m_window(window), m_player(player) {
        loadKeys();
    }

    // Destructeur
    ~KeyManager();

    // Retourne un pointeur vers une touche a partir de son nom
    Key* getKey(const std::string& name);

    // Methode appelee chaque frame pour mettre a jour l'etat de toutes les touches
    void update();

private:
    std::unordered_map<std::string, Key*> m_keys; // Contient toutes les touches accessibles par leur nom
    Mouse* m_mouse;                               // Pointeur vers la souris (pour gerer les actions liees a la souris)

    Player* m_player; // Pointeur vers le joueur
    Game* m_game;     // Pointeur vers le jeu
    Window* m_window; // Pointeur vers la fenetre

    // Charge et initialise toutes les touches du jeu
    void loadKeys();
};
