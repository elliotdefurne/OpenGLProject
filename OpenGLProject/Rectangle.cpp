#include "Rectangle.h"
#include <glad/glad.h>
#include <iostream>

Rectangle::Rectangle(float x, float y, float width, float height)
    : m_x(x), m_y(y), m_width(width), m_height(height) {
}

void Rectangle::move(float dx, float dy) {
    m_x += dx;
    m_y += dy;
}

void Rectangle::draw() const {
    glBegin(GL_QUADS);
        glVertex2f(m_x, m_y);
        glVertex2f(m_x + m_width, m_y);
        glVertex2f(m_x + m_width, m_y + m_height);
        glVertex2f(m_x, m_y + m_height);
    glEnd();
}