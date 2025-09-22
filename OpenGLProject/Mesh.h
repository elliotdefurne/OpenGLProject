#pragma once

#include <vector>
#include <glad/glad.h>
#include "Vertex.h"
#include "Texture.h"

class Mesh {
public:
    Mesh();
    ~Mesh();

    void load(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, Texture* texture);
    void draw() const;

    inline Texture* getTexture() const { return m_texture; };

private:
    GLuint m_vao = 0;
    GLuint m_vbo = 0;
    GLuint m_ebo = 0;
    GLsizei m_indexCount = 0;
	Texture* m_texture;

    void destroy();
};