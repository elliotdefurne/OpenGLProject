#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Camera.h"

class Window {
public:
    Window(int width, int height, const char* title, Camera* camera);
    ~Window();

    void update() const;

    GLFWwindow* getGLFWwindow() const;
    bool getShouldClose() const;
    int getWidth() const;
    int getHeight() const;

private:
    int m_width;
    int m_height;
    const char* m_title;
    GLFWwindow* m_window;
	Camera* m_camera;
    void pollEvents() const;
    void swapBuffers() const;
    bool init();
};

