#pragma once

// D�clarations anticip�es pour �viter les inclusions circulaires
class Window;
class Renderer;
class TextureManager;
class ShaderManager;
class KeyManager;
class Player;
class Camera;

// Classe Game : coeur du jeu, g�re la boucle principale et tous les sous-syst�mes
class Game
{
public:
    // Constructeur : initialise les sous-syst�mes du jeu
    Game();

    // Destructeur : lib�re toutes les ressources
    ~Game();

    // Boucle principale du jeu
    void run();

    // Stoppe le jeu
    void stop();

private:
    Window* m_window;                    // Fen�tre GLFW + contexte OpenGL
    Renderer* m_renderer;                // Gestion du rendu (FPS, clear, deltaTime�)
    TextureManager* m_textureManager;    // Chargement et stockage des textures
    ShaderManager* m_shaderManager;      // Compilation et stockage des shaders GLSL
    KeyManager* m_keyManager;            // Gestion des entr�es clavier
    Player* m_player;                    // Joueur (h�rite d'Entity)
    Camera* m_camera;                    // Cam�ra pour g�n�rer la matrice de vue
    bool m_isRunning = true;             // Indique si le jeu est en cours d'ex�cution

    // M�thode d'initialisation : cr�e la fen�tre et charge les ressources
    void initialize();

    // Mise � jour de la logique du jeu chaque frame : input, entit�s, physique�
    void update();

    // Rendu de la sc�ne chaque frame : dessiner les entit�s et appliquer shaders/textures
    void render();
};
