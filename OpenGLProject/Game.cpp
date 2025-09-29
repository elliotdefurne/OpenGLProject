#include "Game.h"
#include "config.h"

Game::Game() {
    if (!glfwInit()) {
        throw std::runtime_error("Impossible d'initialiser GLFW");
    }
    initialize();
}

Game::~Game() {
    glfwTerminate(); // pas besoin de delete, les unique_ptr nettoient tout seuls
}

void Game::initialize() {
    m_window         = std::make_unique<Window>(Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT, Constants::WINDOW_TITLE);
    m_renderer       = std::make_unique<Renderer>();
    m_camera         = std::make_unique<Camera>();
    m_textureManager = std::make_unique<TextureManager>();
    m_shaderManager  = std::make_unique<ShaderManager>(m_camera.get());
    m_player         = std::make_unique<Player>(m_renderer.get());
    m_keyManager     = std::make_unique<KeyManager>(this, m_window.get(), m_player.get());

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glCullFace(GL_BACK);

    Texture* rocksTexture = m_textureManager->getTexture("test/rocks.png");
    Texture* lightTexture   = m_textureManager->getTexture("light.png");
    Shader* cubeShader = m_shaderManager->getShader("cube");
    Shader* lightShader    = m_shaderManager->getShader("light");

    m_cubes.push_back(std::make_unique<Cube>(glm::vec3(0, 0, 0), 1, cubeShader, rocksTexture));
    m_cubes.push_back(std::make_unique<LightBlock>(glm::vec3(1, 0.5, 2), 0.5, lightShader, lightTexture));
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
    m_camera->update(m_player.get());

    for (auto& cube : m_cubes) {
        cube->update();
    }
}

void Game::render() {
    for (auto& cube : m_cubes) {
        cube->draw();
    }
}

void Game::stop() {
    glfwSetWindowShouldClose(m_window->getGLFWwindow(), GLFW_TRUE);
}
