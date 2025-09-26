#pragma once

#include <vector>
#include <glad/glad.h>
#include "Vertex.h"
#include "Texture.h"

/**
 * @class Mesh
 * @brief Représente un maillage 3D pour OpenGL
 *
 * Un maillage contient :
 * - Des sommets (Vertex) : positions, couleurs, coordonnées de texture
 * - Des indices pour former les triangles
 * - Une texture associée
 *
 * La classe gère aussi les objets GPU suivants :
 * - VAO (Vertex Array Object)
 * - VBO (Vertex Buffer Object)
 * - EBO (Element Buffer Object)
 */
class Mesh {
public:
    /**
     * @brief Constructeur par défaut
     *
     * Initialise le pointeur de texture à nullptr.
     * Les IDs VAO, VBO, EBO seront générés dans load().
     */
    Mesh();

    /**
     * @brief Destructeur
     *
     * Appelle destroy() pour libérer correctement les ressources GPU.
     */
    ~Mesh();

    /**
     * @brief Charge les données du maillage dans la mémoire GPU
     *
     * @param vertices Vecteur de sommets (positions, couleurs, UV)
     * @param indices Vecteur d'indices pour former les triangles
     * @param texture Pointeur vers la texture associée
     */
    void load(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, Texture* texture);

    /**
     * @brief Dessine le maillage à l'écran
     *
     * Bind le VAO et la texture, puis appelle glDrawElements.
     */
    void draw() const;

    /**
     * @brief Retourne la texture associée
     */
    inline Texture* getTexture() const { return m_texture; };

private:
    GLuint m_vao = 0;          // Vertex Array Object
    GLuint m_vbo = 0;          // Vertex Buffer Object
    GLuint m_ebo = 0;          // Element Buffer Object
    GLsizei m_indexCount = 0;  // Nombre d'indices
    Texture* m_texture;        // Pointeur vers la texture

    /**
     * @brief Libère manuellement les ressources GPU (VAO, VBO, EBO)
     */
    void destroy();
};
