#pragma once

#include <vector>
#pragma warning(push)
#pragma warning(disable: 4244)
#include <memory>
#pragma warning(pop)

// Déclarations anticipées
class Window;
class Renderer;
class TextureManager;
class ShaderManager;
class KeyManager;
class Player;
class Camera;
class Cube;

class Game {
public:
    Game();
    ~Game(); // tu peux même le supprimer si tu n’as rien de spécial à libérer

    void run();
    void stop();

private:
    std::vector<std::unique_ptr<Cube>> m_cubes;

    std::unique_ptr<Window> m_window;
    std::unique_ptr<Renderer> m_renderer;
    std::unique_ptr<TextureManager> m_textureManager;
    std::unique_ptr<ShaderManager> m_shaderManager;
    std::unique_ptr<KeyManager> m_keyManager;
    std::unique_ptr<Player> m_player;
    std::unique_ptr<Camera> m_camera;

    bool m_isRunning = true;

    void initialize();
    void update();
    void render();
};
