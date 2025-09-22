#pragma once
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/fwd.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Renderer.h"
#include "constants.h"

namespace direction {
	enum {
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT,
		UP,
		DOWN
	};
}

class Entity
{
public:
	Entity(Renderer* renderer);
	~Entity();
	void virtual update();
	void virtual draw();

	glm::vec3 getPosition() const { return m_position; }
	glm::vec3 getTarget() const { return m_target; }
protected:
	glm::vec3 m_target;
	glm::vec3 m_position;
	Renderer* m_renderer;
};