#include "InputManager.h"

InputManager::InputManager(GLFWwindow* window) : m_window(window) {}

bool InputManager::isKeyPressed(int key) const {
    return glfwGetKey(m_window, key) == GLFW_PRESS;
}