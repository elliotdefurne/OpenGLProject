#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

/*
 * Classe Window
 * Gère la création et l'utilisation d'une fenêtre OpenGL via GLFW.
 *
 * Cette classe encapsule :
 * - La largeur et la hauteur de la fenêtre
 * - Le titre de la fenêtre
 * - Le pointeur vers GLFWwindow
 *
 * Elle fournit des fonctions pour :
 * - Mettre à jour la fenêtre (swap buffers et gestion des événements)
 * - Récupérer les informations de la fenêtre
 * - Initialiser et fermer correctement GLFW
 */
class Window {
public:
    Window(int width, int height, const char* title); // Constructeur : crée la fenêtre
    ~Window(); // Destructeur : détruit la fenêtre et libère les ressources

    void update() const; // Met à jour la fenêtre (swap buffers + gestion events)

    // Getters
    GLFWwindow* getGLFWwindow() const; // Retourne le pointeur GLFW
    bool getShouldClose() const;       // Indique si la fenêtre doit se fermer
    int getWidth() const;              // Largeur de la fenêtre
    int getHeight() const;             // Hauteur de la fenêtre

private:
    int m_width;            // Largeur
    int m_height;           // Hauteur
    const char* m_title;    // Titre de la fenêtre
    GLFWwindow* m_window;   // Pointeur vers la fenêtre GLFW

    void pollEvents() const;  // Récupère les événements (clavier, souris...)
    void swapBuffers() const; // Échange les buffers pour le rendu
    bool init();              // Initialise GLFW et crée la fenêtre
};
