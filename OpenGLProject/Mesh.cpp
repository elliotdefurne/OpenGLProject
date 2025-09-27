#include "Mesh.h"

/**
 * @class Mesh
 * @brief Repr�sente un maillage 3D pr�t � �tre dessin� avec OpenGL.
 *
 * Un maillage contient :
 * - Des sommets (positions, couleurs, coordonn�es de texture)
 * - Une liste d'indices (qui d�finissent quels sommets forment des triangles)
 * - Une texture associ�e
 *
 * Cette classe encapsule les objets GPU suivants :
 * - VAO (Vertex Array Object) : m�morise la configuration des attributs de sommets
 * - VBO (Vertex Buffer Object) : contient les donn�es de tous les sommets
 * - EBO (Element Buffer Object) : contient les indices pour r�utiliser les m�mes sommets
 */

 /**
  * @brief Constructeur par d�faut de Mesh
  *
  * Initialise le pointeur de texture � nullptr.
  * Les identifiants VAO/VBO/EBO seront g�n�r�s plus tard dans load().
  */
Mesh::Mesh() : m_texture(nullptr) {
    // Rien � faire ici : les IDs seront initialis�s dans load()
}

/**
 * @brief Destructeur de Mesh
 *
 * Appelle destroy() pour lib�rer correctement toutes les ressources GPU
 * (VAO, VBO, EBO) lors de la destruction de l'objet.
 *
 * Important : en C++, les destructeurs sont appel�s automatiquement
 * quand un objet sort de sa port�e (stack) ou est supprim� (heap).
 */
Mesh::~Mesh() {
    destroy(); // Lib�ration des ressources GPU
}

/**
 * @brief Charge les donn�es du maillage dans la m�moire GPU
 *
 * �tapes principales :
 * 1. Stocke la texture pass�e en param�tre
 * 2. Cr�e les buffers GPU (VAO, VBO, EBO)
 * 3. Copie les donn�es CPU (vertices et indices) vers la VRAM
 * 4. D�finit le "layout" des sommets pour OpenGL :
 *    - Attribut 0 -> Position (x, y, z)
 *    - Attribut 1 -> Couleur (r, g, b)
 *    - Attribut 2 -> Coordonn�es de texture (s, t)
 *
 * @param vertices Vecteur de sommets (positions, couleurs, UV)
 * @param indices Vecteur d'indices pour former les triangles
 * @param texture Pointeur vers la texture associ�e
 */
void Mesh::load(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, Texture* texture) {
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
}

/**
 * @brief Dessine le maillage � l'�cran
 *
 * Processus :
 * - Active la texture associ�e
 * - Active le VAO (qui contient VBO + EBO + layout)
 * - Appelle glDrawElements pour dessiner les triangles
 *
 * Utilise glDrawElements car le maillage poss�de un EBO (indices)
 */
void Mesh::draw() const {
    glBindTexture(GL_TEXTURE_2D, m_texture->getID()); // Active la texture
    glBindVertexArray(m_vao);                        // Bind du VAO
    glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, nullptr); // Dessin
    glBindVertexArray(0);                             // D�bind
}

/**
 * @brief Lib�re manuellement les ressources GPU utilis�es par le Mesh
 *
 * - Supprime le VBO
 * - Supprime l'EBO
 * - Supprime le VAO
 *
 * Apr�s suppression, les identifiants sont remis � 0 pour �viter tout usage accidentel
 *
 * Important : OpenGL ne lib�re pas automatiquement la m�moire GPU
 */
void Mesh::destroy() {
    if (m_ebo) glDeleteBuffers(1, &m_ebo);
    if (m_vbo) glDeleteBuffers(1, &m_vbo);
    if (m_vao) glDeleteVertexArrays(1, &m_vao);

    m_vao = m_vbo = m_ebo = 0; // R�initialisation des IDs
    m_indexCount = 0;
}
