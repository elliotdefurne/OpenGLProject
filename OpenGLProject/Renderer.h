#pragma once

class Renderer {
public:
    Renderer();   // Constructeur : initialise les variables (sera d�fini dans Renderer.cpp)
    ~Renderer();  // Destructeur : nettoyage si n�cessaire

    // � appeler une fois par frame
    // -> Sert � g�rer le timing entre chaque frame (calcul du deltaTime, FPS, etc.)
    void handleFrameTiming();

    // Lance le rendu d�une frame
    // -> En g�n�ral, on fait un glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) ici
    void clear();

    // Retourne le temps �coul� entre deux frames (en secondes)
    // ->  Utile pour rendre le d�placement des objets ind�pendant du FPS
    float getDeltaTime() const;

    // Active ou d�sactive la limitation de FPS
    void setCapFPS(bool enabled);

    // Fixe la valeur de FPS cible (par exemple 60)
    void setTargetFPS(int fps);

private:
    double m_lastTime;   // Temps de la derni�re frame (en secondes, via glfwGetTime par ex.)
    float m_deltaTime;   // Temps �coul� entre deux frames (delta)

    int m_frameCount;    // Nombre de frames �coul�es depuis le dernier calcul
    double m_fpsTimer;   // Timer pour mesurer les FPS

    bool m_capFPS;       // Si true -> la boucle est limit�e � m_targetFPS
    int m_targetFPS;     // FPS cible (exemple : 60, 120�)
};
