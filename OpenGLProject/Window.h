#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window {
public:
    Window(int width, int height, const char* title);
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

    void pollEvents() const;
    void swapBuffers() const;
    bool init();
};

