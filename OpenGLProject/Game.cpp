#include "Game.h"
#include "constants.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

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
	if (m_inputManager) {
		delete m_inputManager;
	}
	if (m_rectangle) {
		delete m_rectangle;
	}
	glfwTerminate();
}

void Game::Initialize() {
	m_window = new Window(Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT, Constants::WINDOW_TITLE);
	m_renderer = new Renderer();
	m_inputManager = new InputManager(m_window->getGLFWwindow());
	m_rectangle = new Rectangle(100.0f, 100.0f, 50.0f, 50.0f);

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

		ProcessInput();

		m_renderer->clear();

		// DRAW
		glColor3f(1.0f, 1.0f, 1.0f);
		m_rectangle->draw();
	}
}

void Game::ProcessInput() {
	// Process input events
	if (m_inputManager->isKeyPressed(GLFW_KEY_ESCAPE)) {
		delete this; // Exit the game
	}
	else {
		// Déplacement
		if (m_inputManager->isKeyPressed(GLFW_KEY_W))
			m_rectangle->move(0, Constants::PLAYER_SPEED * m_renderer->getDeltaTime());
		if (m_inputManager->isKeyPressed(GLFW_KEY_S))
			m_rectangle->move(0, -Constants::PLAYER_SPEED * m_renderer->getDeltaTime());
		if (m_inputManager->isKeyPressed(GLFW_KEY_A))
			m_rectangle->move(-Constants::PLAYER_SPEED * m_renderer->getDeltaTime(), 0);
		if (m_inputManager->isKeyPressed(GLFW_KEY_D))
			m_rectangle->move(Constants::PLAYER_SPEED * m_renderer->getDeltaTime(), 0);
	}
}