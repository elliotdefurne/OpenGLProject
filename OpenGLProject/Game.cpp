#include "Game.h"

/**
 * @class Game
 * @brief Classe principale qui g�re la boucle du jeu
 *
 * Cette classe s'occupe de :
 * - Initialiser GLFW et OpenGL
 * - Cr�er la fen�tre
 * - Lancer la boucle principale (update + render)
 * - Lib�rer les ressources � la fermeture
 */
Game::Game() : m_window(nullptr), m_renderer(nullptr) {
    // Initialisation de GLFW
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }
    initialize(); // Appelle la m�thode priv�e pour initialiser les composants
}

/**
 * @brief Destructeur du jeu : lib�re la m�moire et termine GLFW
 */
Game::~Game() {
    if (m_keyManager) delete m_keyManager;              // Lib�ration de KeyManager
    if (m_player) delete m_player;              // Lib�ration de KeyManager
    if (m_shaderManager) delete m_shaderManager;   // Lib�ration des shaders
    if (m_textureManager) delete m_textureManager; // Lib�ration des textures
    if (m_camera) delete m_camera;              // Lib�ration de la cam�ra
    if (m_renderer) delete m_renderer;         // Lib�ration du moteur de rendu
    if (m_window) delete m_window;             // Lib�ration de la fen�tre
    
    glfwTerminate();                            // Terminer GLFW proprement
}

/**
 * @brief Initialise les composants du jeu
 *
 * Cr�e les objets n�cessaires :
 * - fen�tre
 * - renderer
 * - cam�ra
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

    // Activer le culling des faces arri�re (optionnel)
    glCullFace(GL_BACK);
}

/**
 * @brief Boucle principale du jeu
 *
 * La boucle continue tant que la fen�tre n'est pas ferm�e :
 * - g�rer le timing (delta time, FPS)
 * - mettre � jour la logique du jeu
 * - effacer l'�cran
 * - dessiner la sc�ne
 * - mettre � jour la fen�tre
 */
void Game::run() {
    while (!m_window->getShouldClose()) {
        m_renderer->handleFrameTiming(); // G�rer le framerate
        update();  // Mettre � jour la logique
        m_renderer->clear(); // Effacer l'�cran
        render(); // Dessiner la sc�ne

        m_window->update(); // Swap buffers et gestion des �v�nements
    }
}

/**
 * @brief Met � jour la logique du jeu
 *
 * Gestion des entr�es clavier et mise � jour de la cam�ra
 */
void Game::update() {
	m_keyManager->update();      // Gestion des entr�es clavier/souris
    m_camera->update(m_player);  // Cam�ra suit le joueur
}

/**
 * @brief Rendu de la sc�ne
 *
 * Cr�e et dessine temporairement deux cubes avec un shader et une texture
 */
void Game::render() {
    Texture* texture = m_textureManager->getTexture("test/rocks.png"); // R�cup�rer la texture
    Shader* basic = m_shaderManager->getShader("cube");                // R�cup�rer le shader

    // Cr�ation de deux cubes
    Cube* cube = new Cube(glm::vec3(0, 0, 0), 1, basic, texture);
    Cube* cube2 = new Cube(glm::vec3(0, 1, 0), 1, basic, texture);

    // Mise � jour des buffers du mesh
    cube->update();
    cube2->update();

    // Dessin
    cube->draw();
    cube2->draw();

    // Nettoyage de la m�moire
    delete cube;
    delete cube2;
    texture = nullptr;
    basic = nullptr;
}

void Game::stop() {
    glfwSetWindowShouldClose(m_window->getGLFWwindow(), (int)true);
}