#pragma once
#include "Window.h"
#include "Renderer.h"
class Game
{

	public:
	Game();
	~Game();
	
	void Run();

	private:
	Window* m_window;
	Renderer* m_renderer;
	bool m_isRunning = true;
	void Initialize();
};

