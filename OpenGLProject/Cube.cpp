#include "Cube.h"

Cube::Cube(glm::vec3 center, int radius, Shader* shader, Texture* texture) : m_center(center), m_radius(radius), m_shader(shader), m_texture(texture) {
    float x = center[0];
    float y = center[1];
    float z = center[2];
    float halfRadius = m_radius / 2.0f;

    m_mesh = new Mesh();
	m_transformation = new Transformation();

    m_vertices = {
        // Face avant
        Vertex(x - halfRadius, y - halfRadius, z + halfRadius, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f),
        Vertex(x + halfRadius, y - halfRadius, z + halfRadius, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f),
        Vertex(x + halfRadius, y + halfRadius, z + halfRadius, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f),
        Vertex(x - halfRadius, y + halfRadius, z + halfRadius, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f),
        // Face arrière
        Vertex(x - halfRadius, y - halfRadius, z - halfRadius, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f),
        Vertex(x + halfRadius, y - halfRadius, z - halfRadius, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f),
        Vertex(x + halfRadius, y + halfRadius, z - halfRadius, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f),
        Vertex(x - halfRadius, y + halfRadius, z - halfRadius, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f),
        // Face gauche
        Vertex(x - halfRadius, y - halfRadius, z - halfRadius, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f),
        Vertex(x - halfRadius, y - halfRadius, z + halfRadius, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f),
        Vertex(x - halfRadius, y + halfRadius, z + halfRadius, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f),
        Vertex(x - halfRadius, y + halfRadius, z - halfRadius, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f),
        // Face droite
        Vertex(x + halfRadius, y - halfRadius, z - halfRadius, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f),
        Vertex(x + halfRadius, y - halfRadius, z + halfRadius, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f),
        Vertex(x + halfRadius, y + halfRadius, z + halfRadius, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f),
        Vertex(x + halfRadius, y + halfRadius, z - halfRadius, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f),
        // Face du bas
        Vertex(x - halfRadius, y - halfRadius, z - halfRadius, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f),
        Vertex(x + halfRadius, y - halfRadius, z - halfRadius, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f),
        Vertex(x + halfRadius, y - halfRadius, z + halfRadius, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f),
        Vertex(x - halfRadius, y - halfRadius, z + halfRadius, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f),
        // Face du haut
        Vertex(x - halfRadius, y + halfRadius, z - halfRadius, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f),
        Vertex(x + halfRadius, y + halfRadius, z - halfRadius, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f),
        Vertex(x + halfRadius, y + halfRadius, z + halfRadius, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f),
        Vertex(x - halfRadius, y + halfRadius, z + halfRadius, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f)
    };

    // Ordre des sommets à dessiner (2 triangles par face)
    m_indices = {
        0, 1, 2,   2, 3, 0,     // Face avant
        4, 5, 6,   6, 7, 4,     // Face arrière
        8, 9, 10,  10, 11, 8,   // Face gauche
        12, 13, 14, 14, 15, 12, // Face droite
        16, 17, 18, 18, 19, 16, // Face bas
        20, 21, 22, 22, 23, 20  // Face haut
    };
}

Cube::~Cube() {
    m_vertices.clear();
    m_indices.clear();
}

void Cube::update()
{
    m_mesh->load(m_vertices, m_indices, m_texture);
}

void Cube::draw() {
	m_shader->clearUniformLocations();
    m_shader->setModel(m_transformation->getMatrix());
    m_shader->use();
    m_shader->setTexture("ourTexture", m_texture->getID());
    m_mesh->draw();
}