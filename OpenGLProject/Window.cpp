#include <iostream>
#include <cstdlib>

#include "Window.h"
#include "constants.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

Window::Window(int width, int height, const char* title)
    : m_width(width), m_height(height), m_title(title), m_window(nullptr) {
    if (!init()) {
        std::cerr << "Failed to initialize Window\n";
        std::exit(EXIT_FAILURE);
    }
}

Window::~Window() {
    if (m_window) {
        glfwDestroyWindow(m_window);
    }
}

bool Window::getShouldClose() const {
    return glfwWindowShouldClose(m_window);
}

void Window::pollEvents() const {
    glfwPollEvents();
}

void Window::swapBuffers() const {
    glfwSwapBuffers(m_window);
}

void Window::update() const {
    swapBuffers();
    pollEvents();
}

GLFWwindow* Window::getGLFWwindow() const {
    return m_window;
}

int Window::getWidth() const {
    return m_width;
}

int Window::getHeight() const {
    return m_height;
}

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

    // Définition de la zone de rendu
    glViewport(0, 0, m_width, m_height);

    //efface le bouton de la souris et permet de capturer la souris
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    return true;
}
