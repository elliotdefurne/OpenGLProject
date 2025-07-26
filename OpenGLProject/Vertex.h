#pragma once
class Vertex
{
public:
	Vertex(float x, float y, float z): m_x(x), m_y(y), m_z(z), m_r(1.0f), m_g(1.0f), m_b(1.0f) {}
	Vertex(float x, float y, float z, float r, float g, float b) : m_x(x), m_y(y), m_z(z), m_r(r), m_g(g), m_b(b) {}
	~Vertex() = default;

	float getX() const { return m_x; }
	float getY() const { return m_y; }
	float getZ() const { return m_z; }
	float getR() const { return m_r; }
	float getG() const { return m_g; }
	float getB() const { return m_b; }
private:
	float m_x, m_y, m_z, m_r, m_g, m_b; // Coordinates & colors of the vertex
};