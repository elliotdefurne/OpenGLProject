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
    void load(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, std::vector<Texture*> textures, unsigned int attributesMask);

    /**
     * @brief Dessine le maillage à l'écran
     *
     * Bind le VAO et la texture, puis appelle glDrawElements.
     */
    void draw() const;

    /**
     * @brief Retourne la texture associée
     */
    inline std::vector<Texture*> getTextures() const { return m_textures; };

private:
    unsigned int m_vao = 0;      // Vertex Array Object
    unsigned int m_vbo = 0;      // Vertex Buffer Object
    unsigned int m_ebo = 0;      // Element Buffer Object
    int m_indexCount = 0;        // Nombre d'indices
    std::vector<Texture*> m_textures;           // Pointeur vers les textures
    
    /**
     * @brief Libère manuellement les ressources GPU (VAO, VBO, EBO)
     */
    void destroy();
};