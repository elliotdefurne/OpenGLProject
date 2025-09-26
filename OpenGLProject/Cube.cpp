#include "Cube.h"

// Constructeur du cube
Cube::Cube(glm::vec3 center, float edge, Shader* shader, Texture* texture)
    : m_center(center), m_edge(edge), m_shader(shader), m_texture(texture)
{
    // Coordonnées du centre
    float x = center[0];
    float y = center[1];
    float z = center[2];

    // Moitié de la longueur d’arête (sert à placer les sommets autour du centre)
    float halfEdge = m_edge / 2.0f;

    // Initialisation des composants
    m_mesh = new Mesh();                 // Maillage (VBO, VAO, EBO)
    m_transformation = new Transformation(); // Matrice de transformation (translation, rotation, scale)

    // Définition des 24 sommets du cube
    // Chaque face a ses 4 sommets (positions + normales (ici nulles) + coordonnées UV)
    m_vertices = {
        // Face avant (Z+)
        Vertex(x - halfEdge, y - halfEdge, z + halfEdge, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f),
        Vertex(x + halfEdge, y - halfEdge, z + halfEdge, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f),
        Vertex(x + halfEdge, y + halfEdge, z + halfEdge, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f),
        Vertex(x - halfEdge, y + halfEdge, z + halfEdge, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f),

        // Face arrière (Z-)
        Vertex(x - halfEdge, y - halfEdge, z - halfEdge, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f),
        Vertex(x + halfEdge, y - halfEdge, z - halfEdge, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f),
        Vertex(x + halfEdge, y + halfEdge, z - halfEdge, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f),
        Vertex(x - halfEdge, y + halfEdge, z - halfEdge, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f),

        // Face gauche (X-)
        Vertex(x - halfEdge, y - halfEdge, z - halfEdge, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f),
        Vertex(x - halfEdge, y - halfEdge, z + halfEdge, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f),
        Vertex(x - halfEdge, y + halfEdge, z + halfEdge, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f),
        Vertex(x - halfEdge, y + halfEdge, z - halfEdge, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f),

        // Face droite (X+)
        Vertex(x + halfEdge, y - halfEdge, z - halfEdge, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f),
        Vertex(x + halfEdge, y - halfEdge, z + halfEdge, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f),
        Vertex(x + halfEdge, y + halfEdge, z + halfEdge, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f),
        Vertex(x + halfEdge, y + halfEdge, z - halfEdge, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f),

        // Face du bas (Y-)
        Vertex(x - halfEdge, y - halfEdge, z - halfEdge, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f),
        Vertex(x + halfEdge, y - halfEdge, z - halfEdge, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f),
        Vertex(x + halfEdge, y - halfEdge, z + halfEdge, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f),
        Vertex(x - halfEdge, y - halfEdge, z + halfEdge, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f),

        // Face du haut (Y+)
        Vertex(x - halfEdge, y + halfEdge, z - halfEdge, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f),
        Vertex(x + halfEdge, y + halfEdge, z - halfEdge, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f),
        Vertex(x + halfEdge, y + halfEdge, z + halfEdge, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f),
        Vertex(x - halfEdge, y + halfEdge, z + halfEdge, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f)
    };

    // Indices -> définissent l’ordre des sommets pour former des triangles
    // Chaque face est composée de 2 triangles -> 6 indices
    m_indices = {
        0, 1, 2,   2, 3, 0,     // Face avant
        4, 5, 6,   6, 7, 4,     // Face arrière
        8, 9, 10,  10, 11, 8,   // Face gauche
        12, 13, 14, 14, 15, 12, // Face droite
        16, 17, 18, 18, 19, 16, // Face bas
        20, 21, 22, 22, 23, 20  // Face haut
    };
}

// Destructeur -> libère la mémoire allouée
Cube::~Cube() {
    m_vertices.clear();       // Nettoie le vecteur de sommets
    m_indices.clear();        // Nettoie le vecteur d’indices
    delete m_mesh;            // Libère le mesh
    delete m_transformation;  // Libère la transformation
}

// Met à jour le maillage du cube
void Cube::update()
{
    // Charge les sommets, indices et texture dans le Mesh (GPU)
    m_mesh->load(m_vertices, m_indices, m_texture);
}

// Dessine le cube à l’écran
void Cube::draw() {
    m_shader->clearUniformLocations();                  // Réinitialise les uniformes du shader
    m_shader->setModel(m_transformation->getMatrix());  // Envoie la matrice modèle au shader
    m_shader->use();                                    // Active le shader
    m_shader->setTexture("ourTexture", m_texture->getID()); // Associe la texture
    m_mesh->draw();                                     // Dessine le maillage (appel OpenGL)
}