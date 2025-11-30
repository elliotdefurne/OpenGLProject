#include "Game.h"
#include "config.h"

Game::Game() {
    if (!glfwInit()) {
        throw std::runtime_error("Impossible d'initialiser GLFW");
    }
    initialize();
}

Game::~Game() {
    m_socket->stop();
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
    m_lightManager   = std::make_unique<LightManager>(m_renderer.get(), m_player.get());
    m_socket         = std::make_unique<Socket>();

    m_socket->connectToServer(Constants::SERVER_IP, Constants::SERVER_PORT);

    Texture* containerTexture = m_textureManager->getTexture("container");

    Shader* cubeShader = m_shaderManager->getShader("cube/severallights");
    Shader* lightShader    = m_shaderManager->getShader("cube/lightsource");

	std::vector<Texture*> crateTextures = { containerTexture };

    // Dans Game::initialize()

    // Lumière 1 - Rouge forte
    m_lightManager->addPointLight(new LightSource(
        glm::vec3(1, 0.5, 2),            // position
        lightShader,
        m_player.get(),
        glm::vec3(0.2f, 0.0f, 0.0f),     // ambient rouge
        glm::vec3(1.0f, 0.0f, 0.0f),     // diffuse ROUGE INTENSE
        glm::vec3(1.0f, 1.0f, 1.0f),     // specular
        1.0f,                             // constant
        0.09f,                            // linear (portée ~50 unités)
        0.032f,                           // quadratic
        glm::vec3(5.0f, 0.0f, 0.0f)      // lightColor
    ));

    // Lumière 2 - Verte forte
    m_lightManager->addPointLight(new LightSource(
        glm::vec3(3, 0.5, -2),           // position
        lightShader,
        m_player.get(),
        glm::vec3(0.0f, 0.2f, 0.0f),     // ambient vert
        glm::vec3(0.0f, 1.0f, 0.0f),     // diffuse VERT INTENSE
        glm::vec3(1.0f, 1.0f, 1.0f),     // specular
        1.0f,                             // constant
        0.09f,                            // linear
        0.032f,                           // quadratic
        glm::vec3(0.0f, 5.0f, 0.0f)      // lightColor
    ));
    m_cubes.push_back(std::make_unique<Cube>(glm::vec3(1, 0, 0), 1.0, cubeShader, crateTextures, m_renderer.get(), m_lightManager.get(), m_player.get()));
    m_cubes.push_back(std::make_unique<Cube>(glm::vec3(0, 0, -2), 1.0, cubeShader, crateTextures, m_renderer.get(), m_lightManager.get(), m_player.get()));
    m_cubes.push_back(std::make_unique<Cube>(glm::vec3(1, 0.5, 2), 1.0, cubeShader, crateTextures, m_renderer.get(), m_lightManager.get(), m_player.get()));

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
    // Printing socket data
    std::string socketdata;
    if(m_socket->pollEvent(socketdata)){
        printf("%s\n", socketdata.c_str());
    }
    // Sending socket ping
    std::string pingData;
    pingData = "Ping from " + m_socket->getLocalIP() + ":" + std::to_string(m_socket->getLocalPort()) + " to " + m_socket->getServerIP() + ":" + std::to_string(m_socket->getServerPort());
    m_socket->sendPacket(pingData);

    m_keyManager->update();
    m_camera->update(m_player.get());


    m_cubes.at(2).get()->getTransformation()->rotate(glm::vec3(1, 0, 0), 10.0f * static_cast<float>(fmod(m_renderer->getDeltaTime(), 360.0)));
    for (auto& cube : m_cubes) {
        cube->update();
    }
    for (auto& alphacube : m_alphacubes) {
        alphacube->update();
    }
    m_lightManager->update();
}

void Game::render() {
    // 1. Opaques
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    for (auto& cube : m_cubes) {
        cube->draw();
    }
    m_lightManager->draw();

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
