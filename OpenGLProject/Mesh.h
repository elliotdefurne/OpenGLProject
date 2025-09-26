#pragma once

#include <vector>
#include <glad/glad.h>
#include "Vertex.h"
#include "Texture.h"

/**
 * @class Mesh
 * @brief Repr�sente un maillage 3D pour OpenGL
 *
 * Un maillage contient :
 * - Des sommets (Vertex) : positions, couleurs, coordonn�es de texture
 * - Des indices pour former les triangles
 * - Une texture associ�e
 *
 * La classe g�re aussi les objets GPU suivants :
 * - VAO (Vertex Array Object)
 * - VBO (Vertex Buffer Object)
 * - EBO (Element Buffer Object)
 */
class Mesh {
public:
    /**
     * @brief Constructeur par d�faut
     *
     * Initialise le pointeur de texture � nullptr.
     * Les IDs VAO, VBO, EBO seront g�n�r�s dans load().
     */
    Mesh();

    /**
     * @brief Destructeur
     *
     * Appelle destroy() pour lib�rer correctement les ressources GPU.
     */
    ~Mesh();

    /**
     * @brief Charge les donn�es du maillage dans la m�moire GPU
     *
     * @param vertices Vecteur de sommets (positions, couleurs, UV)
     * @param indices Vecteur d'indices pour former les triangles
     * @param texture Pointeur vers la texture associ�e
     */
    void load(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, Texture* texture);

    /**
     * @brief Dessine le maillage � l'�cran
     *
     * Bind le VAO et la texture, puis appelle glDrawElements.
     */
    void draw() const;

    /**
     * @brief Retourne la texture associ�e
     */
    inline Texture* getTexture() const { return m_texture; };

private:
    GLuint m_vao = 0;          // Vertex Array Object
    GLuint m_vbo = 0;          // Vertex Buffer Object
    GLuint m_ebo = 0;          // Element Buffer Object
    GLsizei m_indexCount = 0;  // Nombre d'indices
    Texture* m_texture;        // Pointeur vers la texture

    /**
     * @brief Lib�re manuellement les ressources GPU (VAO, VBO, EBO)
     */
    void destroy();
};
