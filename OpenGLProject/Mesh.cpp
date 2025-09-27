#include "Mesh.h"

/**
 * @class Mesh
 * @brief Représente un maillage 3D prêt à être dessiné avec OpenGL.
 *
 * Un maillage contient :
 * - Des sommets (positions, couleurs, coordonnées de texture)
 * - Une liste d'indices (qui définissent quels sommets forment des triangles)
 * - Une texture associée
 *
 * Cette classe encapsule les objets GPU suivants :
 * - VAO (Vertex Array Object) : mémorise la configuration des attributs de sommets
 * - VBO (Vertex Buffer Object) : contient les données de tous les sommets
 * - EBO (Element Buffer Object) : contient les indices pour réutiliser les mêmes sommets
 */

 /**
  * @brief Constructeur par défaut de Mesh
  *
  * Initialise le pointeur de texture à nullptr.
  * Les identifiants VAO/VBO/EBO seront générés plus tard dans load().
  */
Mesh::Mesh() : m_texture(nullptr) {
    // Rien à faire ici : les IDs seront initialisés dans load()
}

/**
 * @brief Destructeur de Mesh
 *
 * Appelle destroy() pour libérer correctement toutes les ressources GPU
 * (VAO, VBO, EBO) lors de la destruction de l'objet.
 *
 * Important : en C++, les destructeurs sont appelés automatiquement
 * quand un objet sort de sa portée (stack) ou est supprimé (heap).
 */
Mesh::~Mesh() {
    destroy(); // Libération des ressources GPU
}

/**
 * @brief Charge les données du maillage dans la mémoire GPU
 *
 * Étapes principales :
 * 1. Stocke la texture passée en paramètre
 * 2. Crée les buffers GPU (VAO, VBO, EBO)
 * 3. Copie les données CPU (vertices et indices) vers la VRAM
 * 4. Définit le "layout" des sommets pour OpenGL :
 *    - Attribut 0 -> Position (x, y, z)
 *    - Attribut 1 -> Couleur (r, g, b)
 *    - Attribut 2 -> Coordonnées de texture (s, t)
 *
 * @param vertices Vecteur de sommets (positions, couleurs, UV)
 * @param indices Vecteur d'indices pour former les triangles
 * @param texture Pointeur vers la texture associée
 */
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
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

    // Couleur (r, g, b)
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));

    // Coordonnées de texture (s, t)
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(6 * sizeof(float)));

    glBindVertexArray(0); // Débind pour éviter les erreurs plus tard
}

/**
 * @brief Dessine le maillage à l'écran
 *
 * Processus :
 * - Active la texture associée
 * - Active le VAO (qui contient VBO + EBO + layout)
 * - Appelle glDrawElements pour dessiner les triangles
 *
 * Utilise glDrawElements car le maillage possède un EBO (indices)
 */
void Mesh::draw() const {
    glBindTexture(GL_TEXTURE_2D, m_texture->getID()); // Active la texture
    glBindVertexArray(m_vao);                        // Bind du VAO
    glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, nullptr); // Dessin
    glBindVertexArray(0);                             // Débind
}

/**
 * @brief Libère manuellement les ressources GPU utilisées par le Mesh
 *
 * - Supprime le VBO
 * - Supprime l'EBO
 * - Supprime le VAO
 *
 * Après suppression, les identifiants sont remis à 0 pour éviter tout usage accidentel
 *
 * Important : OpenGL ne libère pas automatiquement la mémoire GPU
 */
void Mesh::destroy() {
    if (m_ebo) glDeleteBuffers(1, &m_ebo);
    if (m_vbo) glDeleteBuffers(1, &m_vbo);
    if (m_vao) glDeleteVertexArrays(1, &m_vao);

    m_vao = m_vbo = m_ebo = 0; // Réinitialisation des IDs
    m_indexCount = 0;
}
