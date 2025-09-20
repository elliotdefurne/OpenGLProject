#pragma once
#include "config.h"


class Game
{

	public:
		Game();
		~Game();
		Camera* getCamera() const;
		void Run();
		void Update();
		void Render();

	private:
		Window* m_window;
		Renderer* m_renderer;
		TextureManager* m_textureManager;
		ShaderManager* m_shaderManager;
		Camera* m_camera;
		bool m_isRunning = true;
		void Initialize();
};

