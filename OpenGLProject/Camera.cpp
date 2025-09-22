#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 target):
    m_position(position),
    m_target(target),
    m_upVector(glm::vec3(0.0f, 1.0f, 0.0f)),
    m_renderer(nullptr)
{
    // Autres initialisations si besoin
}

void Camera::update(Entity* entity) {
    m_position = entity->getPosition();
    m_target = entity->getTarget();
}

glm::mat4 Camera::getViewMatrix() {
	std::cout << "Camera Position: (" << m_position.x << ", " << m_position.y << ", " << m_position.z << ")\n";
    return glm::lookAt(m_position, m_target, m_upVector);
}