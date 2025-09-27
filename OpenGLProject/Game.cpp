#include "Game.h"

/**
 * @class Game
 * @brief Classe principale qui gère la boucle du jeu
 *
 * Cette classe s'occupe de :
 * - Initialiser GLFW et OpenGL
 * - Créer la fenêtre
 * - Lancer la boucle principale (update + render)
 * - Libérer les ressources à la fermeture
 */
Game::Game() : m_window(nullptr), m_renderer(nullptr) {
    // Initialisation de GLFW
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }
    initialize(); // Appelle la méthode privée pour initialiser les composants
}

/**
 * @brief Destructeur du jeu : libère la mémoire et termine GLFW
 */
Game::~Game() {
    if (m_keyManager) delete m_keyManager;              // Libération de KeyManager
    if (m_player) delete m_player;              // Libération de KeyManager
    if (m_shaderManager) delete m_shaderManager;   // Libération des shaders
    if (m_textureManager) delete m_textureManager; // Libération des textures
    if (m_camera) delete m_camera;              // Libération de la caméra
    if (m_renderer) delete m_renderer;         // Libération du moteur de rendu
    if (m_window) delete m_window;             // Libération de la fenêtre
    
    glfwTerminate();                            // Terminer GLFW proprement
}

/**
 * @brief Initialise les composants du jeu
 *
 * Crée les objets nécessaires :
 * - fenêtre
 * - renderer
 * - caméra
 * - gestionnaires de textures et shaders
 * - joueur et gestionnaire de touches
 * Configure OpenGL pour activer la 3D (depth test, face culling)
 */
void Game::initialize() {
    m_window = new Window(Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT, Constants::WINDOW_TITLE);
    m_renderer = new Renderer();
    m_camera = new Camera();
    m_textureManager = new TextureManager();
    m_shaderManager = new ShaderManager(m_camera);
    m_player = new Player(m_renderer);
    m_keyManager = new KeyManager(this, m_window, m_player);

    // Activer le test de profondeur
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Effacer les buffers couleur et profondeur
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Activer le culling des faces arrière (optionnel)
    glCullFace(GL_BACK);
}

/**
 * @brief Boucle principale du jeu
 *
 * La boucle continue tant que la fenêtre n'est pas fermée :
 * - gérer le timing (delta time, FPS)
 * - mettre à jour la logique du jeu
 * - effacer l'écran
 * - dessiner la scène
 * - mettre à jour la fenêtre
 */
void Game::run() {
    while (!m_window->getShouldClose()) {
        m_renderer->handleFrameTiming(); // Gérer le framerate
        update();  // Mettre à jour la logique
        m_renderer->clear(); // Effacer l'écran
        render(); // Dessiner la scène

        m_window->update(); // Swap buffers et gestion des événements
    }
}

/**
 * @brief Met à jour la logique du jeu
 *
 * Gestion des entrées clavier et mise à jour de la caméra
 */
void Game::update() {
	m_keyManager->update();      // Gestion des entrées clavier/souris
    m_camera->update(m_player);  // Caméra suit le joueur
}

/**
 * @brief Rendu de la scène
 *
 * Crée et dessine temporairement deux cubes avec un shader et une texture
 */
void Game::render() {
    Texture* texture = m_textureManager->getTexture("test/rocks.png"); // Récupérer la texture
    Shader* basic = m_shaderManager->getShader("cube");                // Récupérer le shader

    // Création de deux cubes
    Cube* cube = new Cube(glm::vec3(0, 0, 0), 1, basic, texture);
    Cube* cube2 = new Cube(glm::vec3(0, 1, 0), 1, basic, texture);

    // Mise à jour des buffers du mesh
    cube->update();
    cube2->update();

    // Dessin
    cube->draw();
    cube2->draw();

    // Nettoyage de la mémoire
    delete cube;
    delete cube2;
    texture = nullptr;
    basic = nullptr;
}

void Game::stop() {
    glfwSetWindowShouldClose(m_window->getGLFWwindow(), (int)true);
}