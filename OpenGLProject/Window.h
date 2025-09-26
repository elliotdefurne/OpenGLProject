#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

/*
 * Classe Window
 * G�re la cr�ation et l'utilisation d'une fen�tre OpenGL via GLFW.
 *
 * Cette classe encapsule :
 * - La largeur et la hauteur de la fen�tre
 * - Le titre de la fen�tre
 * - Le pointeur vers GLFWwindow
 *
 * Elle fournit des fonctions pour :
 * - Mettre � jour la fen�tre (swap buffers et gestion des �v�nements)
 * - R�cup�rer les informations de la fen�tre
 * - Initialiser et fermer correctement GLFW
 */
class Window {
public:
    Window(int width, int height, const char* title); // Constructeur : cr�e la fen�tre
    ~Window(); // Destructeur : d�truit la fen�tre et lib�re les ressources

    void update() const; // Met � jour la fen�tre (swap buffers + gestion events)

    // Getters
    GLFWwindow* getGLFWwindow() const; // Retourne le pointeur GLFW
    bool getShouldClose() const;       // Indique si la fen�tre doit se fermer
    int getWidth() const;              // Largeur de la fen�tre
    int getHeight() const;             // Hauteur de la fen�tre

private:
    int m_width;            // Largeur
    int m_height;           // Hauteur
    const char* m_title;    // Titre de la fen�tre
    GLFWwindow* m_window;   // Pointeur vers la fen�tre GLFW

    void pollEvents() const;  // R�cup�re les �v�nements (clavier, souris...)
    void swapBuffers() const; // �change les buffers pour le rendu
    bool init();              // Initialise GLFW et cr�e la fen�tre
};
