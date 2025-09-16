#include "Game.h"

/**
 * @class Game
 * @brief Classe principale qui g�re la boucle du jeu.
 *
 * Cette classe s'occupe de :
 * - Initialiser les biblioth�ques externes (GLFW, OpenGL...).
 * - Cr�er la fen�tre et le contexte de rendu.
 * - Lancer la boucle principale du jeu (update + render).
 * - Nettoyer correctement les ressources � la fermeture.
 */
Game::Game() : m_window(nullptr), m_renderer(nullptr) {
    // Initialisation de GLFW (librairie qui g�re fen�tre, inputs, contexte OpenGL)
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }
    Initialize();
}

/**
 * @brief Destructeur du jeu : lib�re la m�moire et ferme GLFW.
 *
 * En C++, le destructeur est appel� automatiquement quand l�objet sort de port�e.
 * Ici, on s�assure de lib�rer la m�moire pour �viter les fuites
 * (fen�tre, renderer, textures), puis on termine GLFW proprement.
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
 * �tapes principales :
 * 1. Cr�e la fen�tre (classe Window).
 * 2. Cr�e le moteur de rendu (Renderer).
 * 3. Cr�e le gestionnaire de textures (TextureManager).
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

    // Nettoie le buffer couleur et profondeur au d�marrage
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Optionnel : supprime le rendu des faces arri�re des objets (culling)
    // glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    // glFrontFace(GL_CCW);  // D�finit le sens des faces avant (anti-horaire)
}

/**
 * @brief Lance la boucle principale du jeu.
 *
 * Boucle classique d�un moteur de jeu :
 * - UPDATE : met � jour la logique (mouvements, collisions, IA...).
 * - RENDER : dessine la sc�ne � l��cran.
 * La boucle continue jusqu�� ce que la fen�tre soit ferm�e.
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

        // Mise � jour de la fen�tre (swap buffers + gestion events)
        m_window->update();
    }
}

/**
 * @brief Met � jour la logique du jeu.
 *
 * Ici, tu mettras les d�placements des personnages, gestion d�entr�es clavier,
 * collisions, IA, scripts... Pour l�instant, elle est vide.
 */
void Game::Update() {
    // Update game logic here
}

/**
 * @brief G�re le rendu 3D de la sc�ne.
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
