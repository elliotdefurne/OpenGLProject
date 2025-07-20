#pragma once

class Renderer {
public:
    Renderer();
    ~Renderer();

    // À appeler une fois par frame
    void handleFrameTiming();

    // Lance le rendu (clear, etc)
    void clear();

    // Delta time en secondes
    float getDeltaTime() const;

    // Activer/désactiver le cap FPS
    void setCapFPS(bool enabled);

    // Fixer le FPS cible
    void setTargetFPS(int fps);

private:
    double m_lastTime;
    float m_deltaTime;

    int m_frameCount;
    double m_fpsTimer;

    bool m_capFPS;
    int m_targetFPS;
};