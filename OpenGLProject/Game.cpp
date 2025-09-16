#include "Game.h"

/**
 * @class Game
 * @brief Classe principale qui gère la boucle du jeu.
 *
 * Cette classe s'occupe de :
 * - Initialiser les bibliothèques externes (GLFW, OpenGL...).
 * - Créer la fenêtre et le contexte de rendu.
 * - Lancer la boucle principale du jeu (update + render).
 * - Nettoyer correctement les ressources à la fermeture.
 */
Game::Game() : m_window(nullptr), m_renderer(nullptr) {
    // Initialisation de GLFW (librairie qui gère fenêtre, inputs, contexte OpenGL)
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }
    Initialize();
}

/**
 * @brief Destructeur du jeu : libère la mémoire et ferme GLFW.
 *
 * En C++, le destructeur est appelé automatiquement quand l’objet sort de portée.
 * Ici, on s’assure de libérer la mémoire pour éviter les fuites
 * (fenêtre, renderer, textures), puis on termine GLFW proprement.
 */
Game::~Game() {
    if (m_window) {
        delete m_window;
    }
    if (m_renderer) {
        delete m_renderer;
    }
    if (m_textureManager) {
        delete m_textureManager;
    }
    glfwTerminate();
}

/**
 * @brief Initialise les composants du jeu.
 *
 * Étapes principales :
 * 1. Crée la fenêtre (classe Window).
 * 2. Crée le moteur de rendu (Renderer).
 * 3. Crée le gestionnaire de textures (TextureManager).
 * 4. Configure OpenGL pour activer la 3D (test de profondeur, face culling...).
 */
void Game::Initialize() {
    m_window = new Window(Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT, Constants::WINDOW_TITLE);
    m_renderer = new Renderer();
    m_textureManager = new TextureManager();
	m_shaderManager = new ShaderManager();

    // Active le test de profondeur : permet de savoir quels objets sont devant
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Nettoie le buffer couleur et profondeur au démarrage
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Optionnel : supprime le rendu des faces arrière des objets (culling)
    // glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    // glFrontFace(GL_CCW);  // Définit le sens des faces avant (anti-horaire)
}

/**
 * @brief Lance la boucle principale du jeu.
 *
 * Boucle classique d’un moteur de jeu :
 * - UPDATE : met à jour la logique (mouvements, collisions, IA...).
 * - RENDER : dessine la scène à l’écran.
 * La boucle continue jusqu’à ce que la fenêtre soit fermée.
 */
void Game::Run() {
    while (!m_window->getShouldClose()) {
        // Gestion du framerate
        m_renderer->handleFrameTiming();

        // Logique du jeu
        Update();

        // Rendu graphique
        m_renderer->clear();
        Render();

        // Mise à jour de la fenêtre (swap buffers + gestion events)
        m_window->update();
    }
}

/**
 * @brief Met à jour la logique du jeu.
 *
 * Ici, tu mettras les déplacements des personnages, gestion d’entrées clavier,
 * collisions, IA, scripts... Pour l’instant, elle est vide.
 */
void Game::Update() {
    // Update game logic here
}

/**
 * @brief Gère le rendu 3D de la scène.
 */
void Game::Render() {
    Texture* texture = m_textureManager->getTexture("test/absolutecinema.png");
	Shader* basic = m_shaderManager->getShader("cube");

	Cube* cube = new Cube(glm::vec3(0,0,0),1, basic, texture);
    Cube* cube2 = new Cube(glm::vec3(0, 1, 0), 1, basic, texture);

    cube->update();
    cube2->update();
    cube->draw();
    cube2->draw();

    delete cube, cube2;
    texture = nullptr;
    basic = nullptr;
}
