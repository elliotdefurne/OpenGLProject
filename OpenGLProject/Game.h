#pragma once 

#include "config.h"

class Game
{
public:
	Game();   // Constructeur (initialise les sous-systèmes du jeu)
	~Game();  // Destructeur (nettoie les ressources)

	// Boucle principale du jeu
	void run();
	void stop();

private:
	Window* m_window;					// Pointeur vers la fenêtre (gestion GLFW + contexte OpenGL)
	Renderer* m_renderer;				// Pointeur vers le moteur de rendu (FPS, clear, deltaTime…)
	TextureManager* m_textureManager;	// Gestionnaire de textures (chargement et récupération des textures)
	ShaderManager* m_shaderManager;		// Gestionnaire de shaders (compilation, stockage et utilisation des programmes GLSL)
	KeyManager* m_keyManager;			// Gestionnaire de clavier (détecte et traite les entrées utilisateur)
	Player* m_player;					// Joueur (hérite sûrement de Entity)
	Camera* m_camera;					// Caméra (utilisée pour générer la matrice de vue)
	bool m_isRunning = true;			// Booléen pour contrôler si le jeu est en cours d’exécution
	void initialize();					// Méthode d’initialisation du jeu (création fenêtre, chargement ressources…)
	void update();						// Mise à jour de la logique du jeu (input, entités, physique…)
	void render();						// Rendu de la scène (dessiner les entités, appliquer les shaders/textures…)
};
