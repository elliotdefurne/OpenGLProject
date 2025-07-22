#pragma once

#include <vector>
#include <glad/glad.h>     // Ou GLEW selon ton projet
#include "Vertex.h"        // Assure-toi que Vertex est bien défini (position, couleur, etc.)

class Mesh {
public:
    Mesh();
    ~Mesh();

    void load(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
    void draw() const;
    void destroy();

private:
    GLuint m_vao = 0;
    GLuint m_vbo = 0;
    GLuint m_ebo = 0;
    GLsizei m_indexCount = 0;
};