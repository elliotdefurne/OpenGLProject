#include "Window.h"
#include "constants.h"
#include <iostream>
#include <cstdlib>

/**
 * @brief Constructeur de la classe Window.
 *
 * Initialise une fenêtre GLFW avec les dimensions et le titre fournis.
 * Charge le contexte OpenGL via GLAD.
 * Si l'initialisation échoue, le programme se termine.
 *
 * @param width Largeur de la fenêtre.
 * @param height Hauteur de la fenêtre.
 * @param title Titre de la fenêtre.
 */
Window::Window(int width, int height, const char* title)
    : m_width(width), m_height(height), m_title(title), m_window(nullptr) {
    if (!init()) {
        std::cerr << "Failed to initialize Window\n";
        std::exit(EXIT_FAILURE);
    }
}

/**
 * @brief Destructeur de la classe Window.
 *
 * Détruit la fenêtre GLFW si elle a été créée pour libérer les ressources.
 */
Window::~Window() {
    if (m_window) {
        glfwDestroyWindow(m_window);
    }
}

/**
 * @brief Vérifie si la fenêtre doit se fermer.
 *
 * @return true si l'utilisateur ou le système a demandé la fermeture.
 * @return false sinon.
 */
bool Window::getShouldClose() const {
    return glfwWindowShouldClose(m_window);
}

/**
 * @brief Traite les événements en attente (clavier, souris, etc.).
 */
void Window::pollEvents() const {
    glfwPollEvents();
}

/**
 * @brief Échange les buffers avant et arrière.
 *
 * Nécessaire pour afficher le rendu OpenGL à l'écran.
 */
void Window::swapBuffers() const {
    glfwSwapBuffers(m_window);
}

/**
 * @brief Met à jour la fenêtre.
 *
 * Combine le swap des buffers et la gestion des événements.
 */
void Window::update() const {
    swapBuffers();
    pollEvents();
}

/**
 * @brief Retourne le pointeur interne vers la fenêtre GLFW.
 *
 * @return GLFWwindow* Pointeur vers la fenêtre GLFW.
 */
GLFWwindow* Window::getGLFWwindow() const {
    return m_window;
}

/**
 * @brief Obtient la largeur de la fenêtre.
 *
 * @return int Largeur en pixels.
 */
int Window::getWidth() const {
    return m_width;
}

/**
 * @brief Obtient la hauteur de la fenêtre.
 *
 * @return int Hauteur en pixels.
 */
int Window::getHeight() const {
    return m_height;
}

/**
 * @brief Initialise la fenêtre GLFW et le contexte OpenGL.
 *
 * Configure les options de création, crée la fenêtre, initialise GLAD et définit le viewport.
 *
 * @return true si l'initialisation réussit.
 * @return false en cas d'échec.
 */
bool Window::init() {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWmonitor* monitor = nullptr;
    const GLFWvidmode* mode = nullptr;

    if (Constants::IS_WINDOW_FULLSCREEN) {
        monitor = glfwGetPrimaryMonitor();
        mode = glfwGetVideoMode(monitor);
        if (!mode) {
            std::cerr << "Failed to get video mode for fullscreen\n";
            return false;
        }

        // Fixer la résolution, le taux de rafraîchissement et les bits couleur
        glfwWindowHint(GLFW_RED_BITS, mode->redBits);
        glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
        glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
        glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

        m_width = mode->width;
        m_height = mode->height;
    }

    // Création de la fenêtre
    m_window = glfwCreateWindow(
        m_width, m_height, m_title,
        monitor, // nullptr pour fenêtre normale, sinon fullscreen
        nullptr
    );

    if (!m_window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(m_window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return false;
    }

	// Focus sur la fenêtre et capture de la souris
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Définition de la zone de rendu
    glViewport(0, 0, m_width, m_height);
    return true;
}
