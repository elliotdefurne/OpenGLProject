#pragma once
class Vertex
{
public:
	Vertex(float x, float y, float z);
	~Vertex();

	float getX() const { return m_x; }
	float getY() const { return m_y; }
	float getZ() const { return m_z; }
private:
	float m_x, m_y, m_z; // Coordinates of the vertex
};