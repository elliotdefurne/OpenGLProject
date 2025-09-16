#pragma once
#include <glm/glm.hpp>
#include <vector>

#include "Vertex.h"
#include "Mesh.h"
#include "Shader.h"

class Cube
{
public:
    Cube(glm::vec3 center, int radius, Shader* shader, Texture* texture);
    ~Cube();
    void update();
	void draw();
private:
    Mesh* m_mesh;
    Texture* m_texture;
	Shader* m_shader;
	Transformation* m_transformation;

    std::vector<Vertex> m_vertices;
    std::vector<unsigned int> m_indices;
	glm::vec3 m_center;

	int m_radius;
};

