#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 target)
    : Position(position),
    m_cameraPos(position),
    m_cameraTarget(target),
    m_cameraUp(glm::vec3(0.0f, 1.0f, 0.0f)),
    m_renderer(nullptr)
{
    // Autres initialisations si besoin
}

void Camera::ProcessKeyboard(int direction) {
    float velocity = 2.5f * m_renderer->getDeltaTime();
    if (direction == 0) // FORWARD
        Position += m_Front * velocity;
    if (direction == 1) // BACKWARD
        Position -= m_Front * velocity;
    if (direction == 2) // LEFT
        Position -= m_Right * velocity;
    if (direction == 3) // RIGHT
        Position += m_Right * velocity;
}

glm::mat4 Camera::GetViewMatrix() {
    return glm::lookAt(m_cameraPos, m_cameraTarget, m_cameraUp);
}