#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <Windows.h>

class Mouse
{
public:
	Mouse();
	~Mouse();
    glfwSetCursorPosCallback(window, mouse_callback);
	void mouse_callback(GLFWwindow* window, double xpos, double ypos);
private:
    const float m_sensitivity = 0.1f;
    float m_yaw = -90.0f;
};

Mouse::Mouse()
{
}

Mouse::~Mouse()
{
}

void Mouse::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    m_yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);
}