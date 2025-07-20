#pragma once
#include "Window.h"
#include "Renderer.h"
#include "InputManager.h"
#include "Rectangle.h"
class Game
{

	public:
	Game();
	~Game();
	void Initialize();
	void Run();

	private:
	Window* m_window;
	Renderer* m_renderer;
	InputManager* m_inputManager;
	Rectangle* m_rectangle;
	bool m_isRunning = true;
	void ProcessInput();
};

