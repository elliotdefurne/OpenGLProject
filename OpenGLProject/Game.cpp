#include "config.h"


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

	std::vector<Vertex> verts = {
			Vertex(0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f), // Rouge
			Vertex(0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f), // Vert
			Vertex(-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f), // Bleu
	};

	std::vector<unsigned int> indices = { 0, 1, 2};

	Shader basic("./res/shaders/basic.vert", "./res/shaders/basic.frag", true);

	float timeValue = glfwGetTime();
	float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
	int vertexColorLocation = glGetUniformLocation(basic.getID(), "ourColor");
	glUseProgram(basic.getID());
	glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

	basic.use();

	Mesh mesh;
	mesh.load(verts, indices);
	mesh.draw();
}