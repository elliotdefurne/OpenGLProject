#include "Rectangle.h"
#include "Shader.h"

Rectangle::Rectangle(Shader* shader, float x, float y, float width, float height)
    : Shape(shader, x, y, width, height) {
    setupBuffers();
}

Rectangle::~Rectangle() {
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
    glDeleteBuffers(1, &m_EBO);
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
}

void Rectangle::setupBuffers() {
    float vertices[] = {
        // Positions
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);

    glBindVertexArray(m_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}