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

    Texture* rocksTexture = m_textureManager->getTexture("test/rocks.png");
    Texture* glassTexture = m_textureManager->getTexture("glass/glass.png");
    Texture* lightTexture   = m_textureManager->getTexture("light.png");
    Shader* cubeShader = m_shaderManager->getShader("cube");
    Shader* lightShader    = m_shaderManager->getShader("light");

    m_lights.push_back(std::make_unique<LightSource>(glm::vec3(1, 0.5, 2), lightShader, lightTexture));
    m_cubes.push_back(std::make_unique<Cube>(glm::vec3(0, 0, 0), 1, cubeShader, rocksTexture, m_lights.back().get()));
    m_alphacubes.push_back(std::make_unique<Cube>(glm::vec3(1, 1, 0), 1, cubeShader, glassTexture, m_lights.back().get()));

    glGetString(GL_VERSION) ? std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl
        : throw std::runtime_error("Impossible de récupérer la version OpenGL");
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
    for (auto& alphacube : m_alphacubes) {
        alphacube->update();
    }
    for (auto& light : m_lights) {
        light->update();
    }
}

void Game::render() {
    // 1. Opaques
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    for (auto& cube : m_cubes) {
        cube->draw();
    }
    for (auto& light : m_lights) {
        light->draw();
    }

    // 2. Transparences
    glEnable(GL_BLEND);
    glDepthMask(GL_FALSE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Tri des cubes transparents du plus loin au plus proche
    std::sort(m_alphacubes.begin(), m_alphacubes.end(),
        [this](const std::unique_ptr<Cube>& a, const std::unique_ptr<Cube>& b) {
            float da = glm::length(m_camera->getPosition() - a->getCenter());
            float db = glm::length(m_camera->getPosition() - b->getCenter());
            return da > db; // plus loin d'abord
        }
    );

    for (auto& alphacube : m_alphacubes) {
        alphacube->draw();
    }

    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);
}


void Game::stop() {
    glfwSetWindowShouldClose(m_window->getGLFWwindow(), GLFW_TRUE);
}
