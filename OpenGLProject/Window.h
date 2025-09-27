#pragma once

struct GLFWwindow; // D�claration anticip�e pour �viter d'inclure GLFW ici

/**
 * @class Window
 * @brief G�re la cr�ation et l'utilisation d'une fen�tre OpenGL via GLFW
 *
 * La classe encapsule :
 * - la largeur et la hauteur de la fen�tre
 * - le titre de la fen�tre
 * - le pointeur vers GLFWwindow
 *
 * Elle fournit des fonctions pour :
 * - Mettre � jour la fen�tre (swap buffers et gestion des �v�nements)
 * - R�cup�rer les informations de la fen�tre
 * - Initialiser et fermer correctement GLFW
 */
class Window {
public:
    /**
     * @brief Constructeur
     * @param width Largeur de la fen�tre
     * @param height Hauteur de la fen�tre
     * @param title Titre de la fen�tre
     *
     * Cr�e la fen�tre et initialise GLFW
     */
    Window(int width, int height, const char* title);

    /**
     * @brief Destructeur
     *
     * D�truit la fen�tre et lib�re les ressources GLFW
     */
    ~Window();

    /**
     * @brief Met � jour la fen�tre
     *
     * Swap les buffers pour afficher le rendu et r�cup�re les �v�nements
     */
    void update() const;

    // Getters
    GLFWwindow* getGLFWwindow() const; // Retourne le pointeur GLFW
    bool getShouldClose() const;       // Indique si la fen�tre doit se fermer
    int getWidth() const;              // Largeur de la fen�tre
    int getHeight() const;             // Hauteur de la fen�tre

private:
    int m_width;            // Largeur
    int m_height;           // Hauteur
    const char* m_title;    // Titre
    GLFWwindow* m_window;   // Pointeur vers la fen�tre GLFW

    void pollEvents() const;  // R�cup�re les �v�nements (clavier, souris)
    void swapBuffers() const; // �change les buffers pour le rendu
    bool init();              // Initialise GLFW et cr�e la fen�tre
};

