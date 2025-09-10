#include "Renderer.h"
#include "constants.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <thread>
#include <chrono>

/**
 * @brief Constructeur par d�faut du Renderer.
 *
 * Initialise les variables de timing, compteur de FPS et configuration
 * de limitation des FPS avec les valeurs par d�faut d�finies dans Constants.
 */
Renderer::Renderer()
    : m_lastTime(glfwGetTime()), m_deltaTime(0.0f),
    m_frameCount(0), m_fpsTimer(0.0),
    m_capFPS(Constants::DEFAULT_IS_FPS_CAPPING), m_targetFPS(Constants::DEFAULT_FPS_CAPPING)
{
}

/**
 * @brief Destructeur du Renderer.
 *
 * Ne lib�re rien de particulier, mais reste pr�sent pour coh�rence.
 */
Renderer::~Renderer() {}

/**
 * @brief Met � jour le timing des frames et calcule le deltaTime.
 *
 * - Calcule le temps �coul� depuis la derni�re frame.
 * - Applique une limite de FPS si activ�e.
 * - Affiche les FPS dans la console chaque seconde.
 */
void Renderer::handleFrameTiming() {
    double frameTime = 1.0 / m_targetFPS;
    double currentTime = glfwGetTime();
    m_deltaTime = static_cast<float>(currentTime - m_lastTime);

    if (m_capFPS) {
        // Attente active jusqu'� atteindre le temps de frame voulu
        while ((glfwGetTime() - m_lastTime) < frameTime) {
            // Possibilit� d�ajouter une pause CPU ici :
            // std::this_thread::yield();
        }

        currentTime = glfwGetTime();
        m_deltaTime = static_cast<float>(currentTime - m_lastTime);
    }

    m_lastTime = currentTime;

    m_frameCount++;
    m_fpsTimer += m_deltaTime;

    if (m_fpsTimer >= 1.0) {
        std::cout << "FPS : " << m_frameCount << std::endl;
        m_frameCount = 0;
        m_fpsTimer = 0.0;
    }
}

/**
 * @brief Nettoie le framebuffer avec une couleur par d�faut.
 *
 * D�finit une couleur de fond (bleu sombre) et efface le buffer de couleur.
 */
void Renderer::clear() {
    glClearColor(0.0f, 0.1f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

/**
 * @brief Retourne le temps �coul� depuis la derni�re frame.
 *
 * @return float deltaTime en secondes.
 */
float Renderer::getDeltaTime() const {
    return m_deltaTime;
}

/**
 * @brief Active ou d�sactive la limitation de FPS.
 *
 * @param enabled true pour activer le capping, false pour le d�sactiver.
 */
void Renderer::setCapFPS(bool enabled) {
    m_capFPS = enabled;
}

/**
 * @brief D�finit la valeur cible de FPS pour la limitation.
 *
 * @param fps Nombre d�images par seconde souhait�es. Ignor� si <= 0.
 */
void Renderer::setTargetFPS(int fps) {
    if (fps > 0) {
        m_targetFPS = fps;
    }
}
