#pragma once
#include <glm/glm.hpp>


class Direction
{
public:
	Direction(float yaw = 0.0f, float pitch = 0.0f);
	void addDelta(double deltaX, double deltaY);
	glm::vec3 getDirectionVector();
	glm::vec3 rotateRight90KeepY() {
		glm::vec3 v = getDirectionVector();
		return glm::vec3(-v.z, 0, v.x);
	}
private:
	double m_yaw;   // Rotation autour de l'axe Y (gauche-droite)
	double m_pitch; // Rotation autour de l'axe X (haut-bas)
};

