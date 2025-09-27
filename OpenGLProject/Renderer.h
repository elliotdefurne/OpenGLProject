#pragma once

// Classe Renderer : g�re le rendu et le timing des frames
class Renderer {
public:
    // Constructeur : initialise les variables
    Renderer();

    // Destructeur : nettoyage si n�cessaire
    ~Renderer();

    // � appeler une fois par frame
    // -> Sert � calculer le deltaTime et �ventuellement les FPS
    void handleFrameTiming();

    // Lance le rendu d'une frame
    // -> G�n�ralement fait un glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    void clear();

    // Retourne le temps �coul� entre deux frames (en secondes)
    // -> Utile pour rendre le d�placement des objets ind�pendant du FPS
    float getDeltaTime() const;

    // Active ou d�sactive la limitation de FPS
    void setCapFPS(bool enabled);

    // Fixe la valeur de FPS cible (par exemple 60)
    void setTargetFPS(int fps);

private:
    double m_lastTime;   // Temps de la derni�re frame (en secondes)
    float m_deltaTime;   // Temps �coul� entre deux frames (deltaTime)

    int m_frameCount;    // Nombre de frames depuis le dernier calcul
    double m_fpsTimer;   // Timer pour mesurer les FPS

    bool m_capFPS;       // Si true -> limite le FPS � m_targetFPS
    int m_targetFPS;     // FPS cible (ex: 60, 120�)
};
