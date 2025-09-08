#include "Game.h"


Game::Game() : m_window(nullptr), m_renderer(nullptr) {
	// Initialize GLFW
	if (!glfwInit()) {
		throw std::runtime_error("Failed to initialize GLFW");
	}
	Initialize();
}

Game::~Game() {
	// Clean up resources
	if (m_window) {
		delete m_window;
	}
	if (m_renderer) {
		delete m_renderer;
	}
	glfwTerminate();
}

void Game::Initialize() {
	m_window = new Window(Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT, Constants::WINDOW_TITLE);
	m_renderer = new Renderer();

	// Setup orthographic projection (2D pixels)
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, Constants::WINDOW_WIDTH, 0, Constants::WINDOW_HEIGHT, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Texture parameters

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
}

void Game::Run() {
	while (!m_window->getShouldClose()) {
		// UPDATE

		m_renderer->handleFrameTiming();
		m_window->update(); 

		Update();

		// RENDER

		m_renderer->clear();
		
		Render();

	}
}

void Game::Update() {
	// Update game logic here
}

void Game::Render() {
	// Render the game scene here

	std::vector<Texture*> textures;
	Texture* texture = new Texture("./res/textures/verstappen.jpg", 0);
	textures.emplace_back(texture); // Appel le constructeur de Texture avec le chemin et le booléen

	std::vector<Vertex> verts = {
			Vertex(0.5f,0.5f,0.0f,1.0f,0.0f,0.0f,1.0f,1.0f),
			Vertex(0.5f,-0.5f,0.0f,0.0f,1.0f,0.0f,1.0f,0.0f),
			Vertex(-0.5f,-0.5f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f),
			Vertex(-0.5f,0.5f,0.0f,1.0f,1.0f,0.0f,0.0f,1.0f),
	};

	std::vector<unsigned int> indices = { 0, 1, 3, 1, 2, 3};

	Shader basic("./res/shaders/basic.vert", "./res/shaders/basic.frag", true);

	basic.use();
	basic.setTexture("texture0", texture->getID());

	Mesh mesh;
	mesh.load(verts, indices, textures.back());
	mesh.draw();

	delete texture;
}