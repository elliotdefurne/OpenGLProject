#pragma once

#include <glad/glad.h>                  // ou <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/glm.hpp>              

class Shader;

class Shape {
public:
    Shape(Shader* shader, float x = 0.0f, float y = 0.0f, float width = 1.0f, float height = 1.0f);
    virtual ~Shape();
    virtual void setupBuffers() = 0;
	virtual void draw() = 0;

    void setPosition(float x, float y);
    void setSize(float width, float height);
    void setColor(float r, float g, float b);
    void setRotation(float angle);

protected:
    GLuint m_VAO, m_VBO, m_EBO;
    Shader* m_shader;
    glm::vec3 m_position;
    glm::vec3 m_color;
    glm::vec2 m_size;
    float m_rotation;
};

