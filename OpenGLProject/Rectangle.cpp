#include "Rectangle.h"
#include "Shader.h"
#include "Mesh.h"
#include "Vertex.h"

Rectangle::Rectangle(Shader* shader, float x, float y, float width, float height, glm::vec3 color)
    : Shape(shader, x, y, width, height) {
	setColor(color.r, color.g, color.b);
    setupBuffers();
}

Rectangle::~Rectangle() {
	delete m_mesh;
}

void Rectangle::draw() {
    m_shader->use();

    // Créer la matrice de transformation
    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::translate(transform, m_position);
    transform = glm::rotate(transform, glm::radians(m_rotation), glm::vec3(0.0f, 0.0f, 1.0f));
    transform = glm::scale(transform, glm::vec3(m_size.x, m_size.y, 1.0f));

    // Envoyer les uniforms
	m_shader->setMat4("transform", transform);

	m_shader->setVec3("color", m_color);

	m_mesh->draw();
}

void Rectangle::setupBuffers() {
    auto vertices = {
        // Positions
        Vertex(-m_size.x/2, -m_size.y/2, 0.0f, m_color.r, m_color.g, m_color.b),
        Vertex(m_size.x/2, -m_size.y/2, 0.0f , m_color.r, m_color.g, m_color.b),
        Vertex(m_size.x / 2,  m_size.y / 2, 0.0f , m_color.r, m_color.g, m_color.b),
        Vertex(-m_size.x / 2,  m_size.y / 2, 0.0f , m_color.r, m_color.g, m_color.b)
    };

    std::vector<unsigned int> indices = {
        0, 1, 2,
        2, 3, 0
    };

	m_mesh = new Mesh();

    m_mesh->load(vertices, indices, std::vector<Texture*>(), 0b0010);
}