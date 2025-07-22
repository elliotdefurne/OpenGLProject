#pragma once
#include "Vertex.h"
#include <array>

class Triangle
{
public:
	Triangle(const Vertex& v0, const Vertex& v1, const Vertex& v2) : m_vertices({ v0, v1, v2 }) {}
	Triangle(const std::array<Vertex, 3>& vertices) : m_vertices(vertices) {}
	~Triangle() = default;

	const std::array<Vertex, 3>& getVertices() const { return m_vertices; }
private:
	std::array<Vertex, 3> m_vertices;
};