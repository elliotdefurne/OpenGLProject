#include "Mesh.h"

/**
 * @brief Constructeur par défaut de Mesh.
 *
 * Initialise les identifiants OpenGL (VAO, VBO, EBO) à 0.
 */
Mesh::Mesh() : m_texture(nullptr){
    // Rien à faire ici, on initialise les IDs à 0
}

/**
 * @brief Destructeur de Mesh.
 *
 * Libère automatiquement les ressources GPU associées
 * (VAO, VBO, EBO) via destroy().
 */
Mesh::~Mesh() {
    destroy(); // Libération auto à la destruction
}

/**
 * @brief Charge les données du maillage dans la mémoire GPU.
 *
 * Crée et configure les buffers OpenGL nécessaires :
 * - VAO (Vertex Array Object)
 * - VBO (Vertex Buffer Object)
 * - EBO (Element Buffer Object)
 *
 * Définit aussi le layout des attributs de sommet :
 * - Position (location 0, 3 floats)
 * - Couleur (location 1, 3 floats)
 * - Coordonnées de texture (location 2, 2 floats)
 *
 * @param vertices Vecteur de sommets (Vertex).
 * @param indices Vecteur d’indices pour le rendu avec EBO.
 * @param texture Pointeur vers la texture associée.
 */
void Mesh::load(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, Texture* texture) {
    m_texture = texture;
    m_indexCount = static_cast<GLsizei>(indices.size());

    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);
    glGenBuffers(1, &m_ebo);

    glBindVertexArray(m_vao);

    // Upload vertex
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    // Upload indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    // Layout de Vertex : position (x, y, z)
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

    // Layout de Vertex : color (r, g, b)
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(
        1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float))
    );

    // Layout de Vertex : texture (u, v)
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

    glBindVertexArray(0);
}

/**
 * @brief Dessine le maillage à l’écran.
 *
 * Active la texture associée, lie le VAO et appelle
 * glDrawElements pour dessiner les triangles.
 */
void Mesh::draw() const {
    glBindTexture(GL_TEXTURE_2D, m_texture->getID());
    glBindVertexArray(m_vao);
    glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}

/**
 * @brief Libère les ressources GPU du maillage.
 *
 * Supprime VAO, VBO et EBO si existants, puis remet leurs
 * identifiants et le compteur d’indices à 0.
 */
void Mesh::destroy() {
    if (m_ebo) glDeleteBuffers(1, &m_ebo);
    if (m_vbo) glDeleteBuffers(1, &m_vbo);
    if (m_vao) glDeleteVertexArrays(1, &m_vao);

    m_vao = m_vbo = m_ebo = 0;
    m_indexCount = 0;
}
