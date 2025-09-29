#include "Cube.h"

#include "Vertex.h"   // Structure d'un sommet (position, couleur, texture�)
#include "Mesh.h"     // Classe pour gerer les buffers OpenGL et dessiner
#include "Shader.h"   // Classe pour les shaders OpenGL
#include "Texture.h"  // Classe pour les textures
#include "Transformation.h" // Classe pour position, rotation et scale


// Constructeur du cube
Cube::Cube(glm::vec3 center, float edge, Shader* shader, Texture* texture)
    : m_center(center), m_edge(edge), m_shader(shader), m_texture(texture)
{
    // Coordonn�es du centre du cube
    float x = center[0];
    float y = center[1];
    float z = center[2];

    // Moiti� de la taille du cube (sert � placer les sommets autour du centre)
    float halfEdge = m_edge / 2.0f;

    // Cr�ation des composants n�cessaires
    m_mesh = new Mesh();                     // Le "maillage" (contient les infos pour OpenGL)
    m_transformation = new Transformation(); // Permet de d�placer/faire tourner/agrandir l�objet

    // D�finition des sommets du cube
    // Chaque face a 4 sommets, et comme un cube a 6 faces -> 24 sommets en tout
    // Chaque sommet a : position (x,y,z), normale (ici mise � 0 pour l�instant), coordonn�es UV
    m_vertices = {
        // Face avant (Z+)
        Vertex(x - halfEdge, y - halfEdge, z + halfEdge, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f),
        Vertex(x + halfEdge, y - halfEdge, z + halfEdge, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f),
        Vertex(x + halfEdge, y + halfEdge, z + halfEdge, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f),
        Vertex(x - halfEdge, y + halfEdge, z + halfEdge, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f),

        // Face arri�re (Z-)
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

    // Indices : disent dans quel ordre relier les sommets pour former les triangles
    // Chaque face du cube = 2 triangles = 6 indices
    m_indices = {
        0, 1, 2,   2, 3, 0,     // Face avant
        4, 5, 6,   6, 7, 4,     // Face arri�re
        8, 9, 10,  10, 11, 8,   // Face gauche
        12, 13, 14, 14, 15, 12, // Face droite
        16, 17, 18, 18, 19, 16, // Face du bas
        20, 21, 22, 22, 23, 20  // Face du haut
    };
    m_mesh->load(m_vertices, m_indices, m_texture);
}

// Destructeur -> appel� quand on d�truit l�objet Cube
// Lib�re la m�moire utilis�e
Cube::~Cube() {
    m_vertices.clear();       // Vide la liste de sommets
    m_indices.clear();        // Vide la liste d�indices
    delete m_mesh;            // D�truit le mesh
    delete m_transformation;  // D�truit la transformation
}

inline Texture* Cube::getTexture() const {
    return m_mesh->getTexture();
}

// Pr�pare le cube pour �tre affich� (envoie les donn�es au GPU)
void Cube::update()
{
   
}

// Dessine le cube � l��cran
void Cube::draw() {
    m_shader->clearUniformLocations();                          // Nettoie les anciens r�glages du shader
    m_shader->setModel(m_transformation->getMatrix());          // Envoie la matrice "mod�le" (position/rotation/scale)
    m_shader->use();                                            // Active le shader
    m_shader->setTexture("ourTexture", m_texture->getID());     // Associe la texture au shader
    m_shader->setVec3("lightColor", 1.0f, 1.0f, 1.0f);          // Associe la couleur au shader
    m_mesh->draw();                                             // Demande � OpenGL de dessiner le maillage
}
