#include "Mesh.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

Mesh::Mesh() : m_texture(nullptr) {
    // Rien à faire ici : les IDs seront initialisés dans load()
}

Mesh::~Mesh() {
    destroy(); // Libération des ressources GPU
}

void Mesh::load(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, Texture* texture) {
    m_texture = texture; // Stocke la texture
    m_indexCount = static_cast<GLsizei>(indices.size()); // Nombre d'indices

    // Création des objets OpenGL
    glGenVertexArrays(1, &m_vao); // VAO
    glGenBuffers(1, &m_vbo);      // VBO
    glGenBuffers(1, &m_ebo);      // EBO

    glBindVertexArray(m_vao); // Bind du VAO

    // Chargement des sommets dans le VBO
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    // Chargement des indices dans le EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    // Définition du layout mémoire pour chaque attribut
    // Position (x, y, z)
// Position (layout = 0) : offset = 0
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

    // Normal (layout = 1) : offset = 3 floats
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));

    // Couleur (layout = 2) : offset = 6 floats
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(6 * sizeof(float)));

    // TexCoord (layout = 3) : offset = 9 floats
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(9 * sizeof(float)));

    glBindVertexArray(0); // Débind pour éviter les erreurs plus tard
}

void Mesh::draw() const {
    glBindVertexArray(m_vao);                                             // Bind du VAO
    glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, nullptr); // Dessin
    glBindVertexArray(0);                                                 // Débind
}


void Mesh::destroy() {
    if (m_ebo) glDeleteBuffers(1, &m_ebo);
    if (m_vbo) glDeleteBuffers(1, &m_vbo);
    if (m_vao) glDeleteVertexArrays(1, &m_vao);

    m_vao = m_vbo = m_ebo = 0; // Réinitialisation des IDs
    m_indexCount = 0;
}
