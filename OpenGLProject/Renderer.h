#pragma once

class Renderer {
public:
    Renderer();   // Constructeur : initialise les variables (sera défini dans Renderer.cpp)
    ~Renderer();  // Destructeur : nettoyage si nécessaire

    // À appeler une fois par frame
    // -> Sert à gérer le timing entre chaque frame (calcul du deltaTime, FPS, etc.)
    void handleFrameTiming();

    // Lance le rendu d’une frame
    // -> En général, on fait un glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) ici
    void clear();

    // Retourne le temps écoulé entre deux frames (en secondes)
    // ->  Utile pour rendre le déplacement des objets indépendant du FPS
    float getDeltaTime() const;

    // Active ou désactive la limitation de FPS
    void setCapFPS(bool enabled);

    // Fixe la valeur de FPS cible (par exemple 60)
    void setTargetFPS(int fps);

private:
    double m_lastTime;   // Temps de la dernière frame (en secondes, via glfwGetTime par ex.)
    float m_deltaTime;   // Temps écoulé entre deux frames (delta)

    int m_frameCount;    // Nombre de frames écoulées depuis le dernier calcul
    double m_fpsTimer;   // Timer pour mesurer les FPS

    bool m_capFPS;       // Si true -> la boucle est limitée à m_targetFPS
    int m_targetFPS;     // FPS cible (exemple : 60, 120…)
};
