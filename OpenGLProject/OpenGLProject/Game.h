#pragma once
#include "config.h"

class Game
{

	public:
		Game();
		~Game();
	
		void Run();
		void Update();
		void Render();

	private:
		Window* m_window;
		Renderer* m_renderer;
		TextureManager* m_textureManager;
		bool m_isRunning = true;
		void Initialize();
};

