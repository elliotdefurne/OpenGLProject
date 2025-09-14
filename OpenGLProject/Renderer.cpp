#include "Renderer.h"
#include "constants.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <thread>
#include <chrono>

/**
 * @class Renderer
 * @brief Gere le rendu et la synchronisation des frames (timing, FPS).
 *
 * Cette classe s'occupe de :
 * - Calculer le deltaTime (temps ecoule entre deux frames)
 * - Limiter le nombre de frames par seconde si l'option est activee (cap FPS)
 * - Afficher les FPS reels dans la console
 * - Nettoyer l'ecran avant chaque rendu (clear)
 *
 * Notion importante : le "deltaTime" est utilise dans les jeux pour rendre les mouvements
 * independants de la vitesse du PC. Exemple : si un objet avance de 1 unite par seconde,
 * on le deplace de (1 * deltaTime) chaque frame.
 */

Renderer::Renderer()
    : m_lastTime(glfwGetTime()), m_deltaTime(0.0f),
    m_frameCount(0), m_fpsTimer(0.0),
    m_capFPS(Constants::DEFAULT_IS_FPS_CAPPING),
    m_targetFPS(Constants::DEFAULT_FPS_CAPPING)
{
    // Rien a faire de plus : on initialise juste les variables
}

/**
 * @brief Destructeur de Renderer.
 *
 * Rien de special ici, car Renderer n'alloue pas de ressources GPU
 * ou memoire dynamique a liberer. Mais il est defini pour respecter
 * les bonnes pratiques.
 */
Renderer::~Renderer() {}

/**
 * @brief Gere le temps entre les frames et le calcul des FPS.
 *
 * - Calcule le temps ecoule depuis la derniere frame (deltaTime).
 * - Si le cap FPS est active, attend jusqu'a atteindre la duree cible d'une frame.
 *   Exemple : pour 60 FPS, chaque frame doit durer ~0.016 secondes.
 * - Compte le nombre de frames par seconde et l'affiche dans la console.
 *
 * Exemple : si la machine est tres rapide et calcule une frame en 0.005s,
 * et que la limite est 60 FPS, la fonction "attend" pour que la frame dure 0.016s.
 */
void Renderer::handleFrameTiming() {
    double frameTime = 1.0 / m_targetFPS;
    double currentTime = glfwGetTime();
    m_deltaTime = static_cast<float>(currentTime - m_lastTime);

    if (m_capFPS) {
        // Boucle active qui attend jusqu'a ce que le temps de frame soit atteint
        while ((glfwGetTime() - m_lastTime) < frameTime) {
            // On pourrait utiliser std::this_thread::yield() ou sleep
            // mais ici c'est volontairement commente.
        }
        currentTime = glfwGetTime();
        m_deltaTime = static_cast<float>(currentTime - m_lastTime);
    }

    m_lastTime = currentTime;

    // Comptage des FPS
    m_frameCount++;
    m_fpsTimer += m_deltaTime;

    if (m_fpsTimer >= 1.0) {
        std::cout << "FPS: " << m_frameCount << std::endl;
        m_frameCount = 0;
        m_fpsTimer = 0.0;
    }
}

/**
 * @brief Efface l'ecran avant chaque rendu.
 *
 * - Fixe la couleur de fond avec glClearColor(r, g, b, a).
 * - Efface le color buffer ET le depth buffer.
 *
 * Important : le depth buffer est utilise pour la 3D,
 * il permet de savoir quels pixels sont devant ou derriere.
 */
void Renderer::clear() {
    glClearColor(0.0f, 0.1f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

/**
 * @brief Retourne le deltaTime (temps entre deux frames).
 *
 * @return float Temps en secondes depuis la derniere frame.
 */
float Renderer::getDeltaTime() const {
    return m_deltaTime;
}

/**
 * @brief Active ou desactive la limitation du nombre de FPS.
 *
 * @param enabled true pour activer, false pour desactiver.
 */
void Renderer::setCapFPS(bool enabled) {
    m_capFPS = enabled;
}

/**
 * @brief Change la valeur cible de FPS (si capFPS est active).
 *
 * Exemple : setTargetFPS(120) limitera le jeu a 120 FPS.
 *
 * @param fps Nombre de frames par seconde (doit etre > 0).
 */
void Renderer::setTargetFPS(int fps) {
    if (fps > 0) {
        m_targetFPS = fps;
    }
}
