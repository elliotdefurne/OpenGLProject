#pragma once
#include "config.h"

class Game
{

	public:
		Game();
		~Game();
	
		void Run();

	private:
		Window* m_window;
		Renderer* m_renderer;
		TextureManager* m_textureManager;
		ShaderManager* m_shaderManager;
		KeyManager* m_keyManager;
		Player* m_player;
		Camera* m_camera;
		bool m_isRunning = true;
		void Initialize();
		void update();
		void render();
};

