#include "Window.h"
#include "constants.h"
#include <iostream>
#include <cstdlib>

/**
 * @brief Constructeur de la classe Window.
 *
 * Initialise une fen�tre GLFW avec les dimensions et le titre fournis.
 * Charge le contexte OpenGL via GLAD.
 * Si l'initialisation �choue, le programme se termine.
 *
 * @param width Largeur de la fen�tre.
 * @param height Hauteur de la fen�tre.
 * @param title Titre de la fen�tre.
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
 * D�truit la fen�tre GLFW si elle a �t� cr��e pour lib�rer les ressources.
 */
Window::~Window() {
    if (m_window) {
        glfwDestroyWindow(m_window);
    }
}

/**
 * @brief V�rifie si la fen�tre doit se fermer.
 *
 * @return true si l'utilisateur ou le syst�me a demand� la fermeture.
 * @return false sinon.
 */
bool Window::getShouldClose() const {
    return glfwWindowShouldClose(m_window);
}

/**
 * @brief Traite les �v�nements en attente (clavier, souris, etc.).
 */
void Window::pollEvents() const {
    glfwPollEvents();
}

/**
 * @brief �change les buffers avant et arri�re.
 *
 * N�cessaire pour afficher le rendu OpenGL � l'�cran.
 */
void Window::swapBuffers() const {
    glfwSwapBuffers(m_window);
}

/**
 * @brief Met � jour la fen�tre.
 *
 * Combine le swap des buffers et la gestion des �v�nements.
 */
void Window::update() const {
    swapBuffers();
    pollEvents();
}

/**
 * @brief Retourne le pointeur interne vers la fen�tre GLFW.
 *
 * @return GLFWwindow* Pointeur vers la fen�tre GLFW.
 */
GLFWwindow* Window::getGLFWwindow() const {
    return m_window;
}

/**
 * @brief Obtient la largeur de la fen�tre.
 *
 * @return int Largeur en pixels.
 */
int Window::getWidth() const {
    return m_width;
}

/**
 * @brief Obtient la hauteur de la fen�tre.
 *
 * @return int Hauteur en pixels.
 */
int Window::getHeight() const {
    return m_height;
}

/**
 * @brief Initialise la fen�tre GLFW et le contexte OpenGL.
 *
 * Configure les options de cr�ation, cr�e la fen�tre, initialise GLAD et d�finit le viewport.
 *
 * @return true si l'initialisation r�ussit.
 * @return false en cas d'�chec.
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

        // Fixer la r�solution, le taux de rafra�chissement et les bits couleur
        glfwWindowHint(GLFW_RED_BITS, mode->redBits);
        glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
        glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
        glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

        m_width = mode->width;
        m_height = mode->height;
    }

    // Cr�ation de la fen�tre
    m_window = glfwCreateWindow(
        m_width, m_height, m_title,
        monitor, // nullptr pour fen�tre normale, sinon fullscreen
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

	// Focus sur la fen�tre et capture de la souris
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // D�finition de la zone de rendu
    glViewport(0, 0, m_width, m_height);
    return true;
}
