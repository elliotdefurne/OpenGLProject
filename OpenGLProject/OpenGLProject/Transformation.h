#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Transformation {
public:
	Transformation(glm::vec3 rotationAxes = glm::vec3(0.0f,0.0f,0.0f), float rotationDegrees = 0, glm::vec3 scale=glm::vec3(1.0f, 1.0f, 1.0f))
		: m_trans(glm::mat4(1.0f)) {
		m_trans = glm::rotate(m_trans, glm::radians(rotationDegrees), rotationAxes);
		m_trans = glm::scale(m_trans, scale);
	};

	~Transformation() = default;

	inline glm::mat4 getMatrix() const { return m_trans; };
private:
	glm::mat4 m_trans;
};