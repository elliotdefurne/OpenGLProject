#pragma once

#include <vector>
#include "Vertex.h"   // Structure d'un sommet (position, couleur, UV)
#include "Texture.h"  // Classe pour gerer les textures

enum class VertexAttribute {
    POSITION = 1 << 0,  // 0001
    NORMAL = 1 << 1,  // 0010
    COLOR = 1 << 2,  // 0100
    TEXCOORD = 1 << 3   // 1000
};

/**
 * @class Mesh
 * @brief Represente un maillage 3D pour OpenGL
 *
 * Un maillage contient :
 * - Des sommets (Vertex) : positions, couleurs, coordonnees de texture
 * - Des indices pour former les triangles
 * - Une texture associee
 *
 * La classe gere aussi les objets GPU suivants :
 * - VAO (Vertex Array Object)
 * - VBO (Vertex Buffer Object)
 * - EBO (Element Buffer Object)
 */
class Mesh {
public:
    /**
     * @brief Constructeur par defaut
     *
     * Initialise le pointeur de texture a nullptr.
     * Les IDs VAO, VBO, EBO seront generes dans load().
     */
    Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, unsigned int attributesMask = 0b0101);

    /**
     * @brief Destructeur
     *
     * Appelle destroy() pour liberer correctement les ressources GPU.
     */
    ~Mesh();

    /**
     * @brief Charge les donnees du maillage dans la memoire GPU
     *
     * @param vertices Vecteur de sommets (positions, couleurs, UV)
     * @param indices Vecteur d'indices pour former les triangles
     * @param texture Pointeur vers la texture associee
     */

    /**
     * @brief Dessine le maillage a l'ecran
     *
     * Bind le VAO et la texture, puis appelle glDrawElements.
     */
    void draw() const;

	std::vector<Vertex> getVertices() const { return m_vertices; }
    std::vector<unsigned int> getIndices() const { return m_indices; }

private:
    unsigned int m_vao = 0;      // Vertex Array Object
    unsigned int m_vbo = 0;      // Vertex Buffer Object
    unsigned int m_ebo = 0;      // Element Buffer Object
    int m_indexCount = 0;        // Nombre d'indices

    std::vector<Vertex> m_vertices;
    std::vector<unsigned int> m_indices;

    void setupMesh(unsigned int attributesMask);
};