#include "Mesh.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

Mesh::Mesh() : m_texture(nullptr) {
    // Rien � faire ici : les IDs seront initialis�s dans load()
}

Mesh::~Mesh() {
    destroy(); // Lib�ration des ressources GPU
}

void Mesh::load(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, Texture* texture) {

    if (m_loaded) return; // d�j� charg�, on ne refait rien

    m_texture = texture; // Stocke la texture
    m_indexCount = static_cast<GLsizei>(indices.size()); // Nombre d'indices

    // Cr�ation des objets OpenGL
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

    // D�finition du layout m�moire pour chaque attribut
    // Position (x, y, z)
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

    // Couleur (r, g, b)
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));

    // Coordonn�es de texture (s, t)
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(6 * sizeof(float)));

    glBindVertexArray(0); // D�bind pour �viter les erreurs plus tard

    m_loaded = true;
}

void Mesh::draw() const {
    glBindTexture(GL_TEXTURE_2D, m_texture->getID());   // Active la texture
    glBindVertexArray(m_vao);                           // Bind du VAO
    glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, nullptr); // Dessin
    glBindVertexArray(0);                               // D�bind
}


void Mesh::destroy() {
    if (m_ebo) glDeleteBuffers(1, &m_ebo);
    if (m_vbo) glDeleteBuffers(1, &m_vbo);
    if (m_vao) glDeleteVertexArrays(1, &m_vao);

    m_vao = m_vbo = m_ebo = 0; // R�initialisation des IDs
    m_indexCount = 0;
}
