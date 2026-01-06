#include "Shape.h"

Shape::Shape(Shader* shader, float x, float y, float width, float height) : m_shader(shader), m_position(x,y,0),m_VAO(NULL), m_VBO(NULL), m_EBO(NULL) {
}

Shape::~Shape() {
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
    glDeleteBuffers(1, &m_EBO);
}


void Shape::setPosition(float x, float y) {
    m_position = glm::vec3(x, y, 0.0f);
}

void Shape::setSize(float width, float height) {
    m_size = glm::vec2(width, height);
}

void Shape::setColor(float r, float g, float b) {
    m_color = glm::vec3(r, g, b);
}

void Shape::setRotation(float angle) {
    m_rotation = angle;
}