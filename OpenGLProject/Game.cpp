#include "Game.h"
#include "config.h"

Game::Game() : m_window(nullptr), m_renderer(nullptr) {
    // Initialisation de GLFW (si ça échoue, on arrête tout)
    if (!glfwInit()) {
        throw std::runtime_error("Impossible d'initialiser GLFW");
    }
    initialize(); // On prépare tous les objets nécessaires au jeu
}

Game::~Game() {
    if (m_keyManager) delete m_keyManager;
    if (m_player) delete m_player;
    if (m_shaderManager) delete m_shaderManager;
    if (m_textureManager) delete m_textureManager;
    if (m_camera) delete m_camera;
    if (m_renderer) delete m_renderer;
    if (m_window) delete m_window;

    glfwTerminate(); // On termine GLFW proprement
}

void Game::initialize() {
    m_window = new Window(Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT, Constants::WINDOW_TITLE);
    m_renderer = new Renderer();
    m_camera = new Camera();
    m_textureManager = new TextureManager();
    m_shaderManager = new ShaderManager(m_camera);
    m_player = new Player(m_renderer);
    m_keyManager = new KeyManager(this, m_window, m_player);

    // Active le test de profondeur (évite que des objets derrière passent devant)
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Efface l’écran au lancement
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Active l’option qui permet de ne pas dessiner les faces arrière des objets (gain de perf)
    glCullFace(GL_BACK);

    // Création des cubes
    Texture* texture = m_textureManager->getTexture("test/rocks.png");
    Texture* light = m_textureManager->getTexture("light.png");
    Shader* basic = m_shaderManager->getShader("cube");

    m_cubes.push_back(new Cube(glm::vec3(0, 0, 0), 1, basic, texture));
	m_cubes.push_back(new Cube(glm::vec3(1, 0.5, 2), 0.5, basic, light));
}

void Game::run() {
    while (!m_window->getShouldClose()) {
        m_renderer->handleFrameTiming();
        update();
        m_renderer->clear();
        render();
        m_window->update();
    }
}

void Game::update() {
    m_keyManager->update();
    m_camera->update(m_player);

    for (auto& cube : m_cubes) {
        cube->update();
	}
}

void Game::render() {
    // Dessine les cubes
    for (auto& cube : m_cubes) {
        cube->draw();
    }
}

void Game::stop() {
    glfwSetWindowShouldClose(m_window->getGLFWwindow(), (int)true);
}
