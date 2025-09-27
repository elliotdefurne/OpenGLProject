#pragma once

// Déclarations anticipées pour éviter les inclusions circulaires
class Window;
class Renderer;
class TextureManager;
class ShaderManager;
class KeyManager;
class Player;
class Camera;

// Classe Game : coeur du jeu, gère la boucle principale et tous les sous-systèmes
class Game
{
public:
    // Constructeur : initialise les sous-systèmes du jeu
    Game();

    // Destructeur : libère toutes les ressources
    ~Game();

    // Boucle principale du jeu
    void run();

    // Stoppe le jeu
    void stop();

private:
    Window* m_window;                    // Fenêtre GLFW + contexte OpenGL
    Renderer* m_renderer;                // Gestion du rendu (FPS, clear, deltaTime…)
    TextureManager* m_textureManager;    // Chargement et stockage des textures
    ShaderManager* m_shaderManager;      // Compilation et stockage des shaders GLSL
    KeyManager* m_keyManager;            // Gestion des entrées clavier
    Player* m_player;                    // Joueur (hérite d'Entity)
    Camera* m_camera;                    // Caméra pour générer la matrice de vue
    bool m_isRunning = true;             // Indique si le jeu est en cours d'exécution

    // Méthode d'initialisation : crée la fenêtre et charge les ressources
    void initialize();

    // Mise à jour de la logique du jeu chaque frame : input, entités, physique…
    void update();

    // Rendu de la scène chaque frame : dessiner les entités et appliquer shaders/textures
    void render();
};
