#include "Mesh.h"

/**
 * @class Mesh
 * @brief Represente un maillage 3D (ensemble de sommets et d'indices) pret a etre dessine avec OpenGL.
 *
 * Un maillage (mesh) contient :
 * - Des sommets (positions, couleurs, coordonnees de texture)
 * - Une liste d'indices (qui definissent quels sommets forment des triangles)
 * - Une texture associee
 *
 * Cette classe encapsule les objets GPU suivants :
 * - VAO (Vertex Array Object) : memorise la configuration des attributs de sommets
 * - VBO (Vertex Buffer Object) : contient les donnees de tous les sommets
 * - EBO (Element Buffer Object) : contient les indices pour reutiliser les sommets sans duplication
 */

 /**
  * @brief Constructeur par defaut de Mesh.
  *
  * Initialise le pointeur de texture a nullptr.
  * Les identifiants VAO/VBO/EBO seront generes plus tard dans load().
  */
Mesh::Mesh() : m_texture(nullptr) {
    // Rien a faire ici : les IDs seront initialises dans load()
}

/**
 * @brief Destructeur de Mesh.
 *
 * Appelle destroy() pour s'assurer que toutes les ressources GPU
 * (VAO, VBO, EBO) sont correctement liberees lors de la destruction de l'objet.
 *
 * Important : en C++, les destructeurs sont appeles automatiquement
 * quand un objet sort de sa portee (stack) ou est supprime (heap).
 */
Mesh::~Mesh() {
    destroy();
}

/**
 * @brief Charge les donnees du maillage dans la memoire GPU.
 *
 * Etapes principales :
 * 1. Stocke la texture passee en parametre.
 * 2. Cree les buffers GPU (VAO, VBO, EBO) avec glGen*().
 * 3. Copie les donnees CPU (vertices et indices) vers la VRAM avec glBufferData().
 * 4. Definit le "layout" des sommets, c'est-a-dire comment OpenGL lit les donnees :
 *    - Attribut 0 -> Position (3 floats : x, y, z)
 *    - Attribut 1 -> Couleur (3 floats : r, g, b)
 *    - Attribut 2 -> Coordonnees de texture (2 floats : s, t)
 *
 * @param vertices Vecteur de sommets (std::vector<Vertex>), contient les positions/couleurs/UV.
 * @param indices Vecteur d'indices (std::vector<unsigned int>), determine quels sommets forment des triangles.
 * @param texture Pointeur vers la Texture associee (Texture*).
 *
 * Exemple : pour dessiner un cube, on passe 24 sommets (6 faces * 4 sommets) + 36 indices (6 faces * 2 triangles * 3 indices).
 */
void Mesh::load(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, Texture* texture) {
    m_texture = texture;
    m_indexCount = static_cast<GLsizei>(indices.size());

    // Creation des objets OpenGL
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);
    glGenBuffers(1, &m_ebo);

    glBindVertexArray(m_vao);

    // Chargement des sommets dans la memoire GPU
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    // Chargement des indices dans la memoire GPU
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    // Definition du layout memoire pour chaque attribut du Vertex
    // Position (x, y, z)
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

    // Couleur (r, g, b)
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));

    // Coordonnees de texture (s, t)
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(6 * sizeof(float)));

    glBindVertexArray(0); // Debind pour eviter des erreurs plus tard
}

/**
 * @brief Dessine le maillage a l'ecran.
 *
 * Processus :
 * - Active la texture associee (glBindTexture).
 * - Active le VAO (qui contient le VBO + EBO + layout deja configures).
 * - Appelle glDrawElements pour dessiner les triangles.
 *
 * Ici, on utilise glDrawElements (et pas glDrawArrays) car on a un EBO (indices).
 */
void Mesh::draw() const {
    glBindTexture(GL_TEXTURE_2D, m_texture->getID());
    glBindVertexArray(m_vao);
    glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}

/**
 * @brief Libere manuellement les ressources GPU utilisees par ce Mesh.
 *
 * - Supprime le VBO (vertex buffer)
 * - Supprime l'EBO (element buffer)
 * - Supprime le VAO (vertex array)
 *
 * Apres suppression, les identifiants sont remis a 0 pour eviter tout usage accidentel.
 *
 * Important : OpenGL ne libere pas automatiquement la memoire GPU !
 * Il faut toujours supprimer manuellement les buffers qu'on a crees.
 */
void Mesh::destroy() {
    if (m_ebo) glDeleteBuffers(1, &m_ebo);
    if (m_vbo) glDeleteBuffers(1, &m_vbo);
    if (m_vao) glDeleteVertexArrays(1, &m_vao);

    m_vao = m_vbo = m_ebo = 0;
    m_indexCount = 0;
}
