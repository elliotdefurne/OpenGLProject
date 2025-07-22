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

		// RENDER

		std::vector<Vertex> verts = {
			Vertex(-0.5f, -0.5f, 0.0f),
			Vertex(0.5f, -0.5f, 0.0f),
			Vertex(0.0f, 0.5f, 0.0f)
		};

		std::vector<unsigned int> indices = { 0, 1, 2 };

		Mesh mesh;
		mesh.load(verts, indices);
		mesh.draw();

		m_renderer->clear();
	}
}