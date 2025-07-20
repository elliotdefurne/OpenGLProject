#pragma once
#include <GLFW/glfw3.h>

class InputManager {
public:
    explicit InputManager(GLFWwindow* window);

    bool isKeyPressed(int key) const;

private:
    GLFWwindow* m_window;
};

