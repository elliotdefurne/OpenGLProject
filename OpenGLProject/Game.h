#pragma once 

#include "config.h"

class Game
{
public:
	Game();   // Constructeur (initialise les sous-syst�mes du jeu)
	~Game();  // Destructeur (nettoie les ressources)

	// Boucle principale du jeu
	void run();
	void stop();

private:
	Window* m_window;					// Pointeur vers la fen�tre (gestion GLFW + contexte OpenGL)
	Renderer* m_renderer;				// Pointeur vers le moteur de rendu (FPS, clear, deltaTime�)
	TextureManager* m_textureManager;	// Gestionnaire de textures (chargement et r�cup�ration des textures)
	ShaderManager* m_shaderManager;		// Gestionnaire de shaders (compilation, stockage et utilisation des programmes GLSL)
	KeyManager* m_keyManager;			// Gestionnaire de clavier (d�tecte et traite les entr�es utilisateur)
	Player* m_player;					// Joueur (h�rite s�rement de Entity)
	Camera* m_camera;					// Cam�ra (utilis�e pour g�n�rer la matrice de vue)
	bool m_isRunning = true;			// Bool�en pour contr�ler si le jeu est en cours d�ex�cution
	void initialize();					// M�thode d�initialisation du jeu (cr�ation fen�tre, chargement ressources�)
	void update();						// Mise � jour de la logique du jeu (input, entit�s, physique�)
	void render();						// Rendu de la sc�ne (dessiner les entit�s, appliquer les shaders/textures�)
};
