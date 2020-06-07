#pragma once

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>


class Window {
public:
    Window();
    Window(GLint windowWidth, GLint windowHeight);

    void initialize();

    GLint getBufferWidth() const { return bufferWidth; }
    GLint getBufferHeight() const { return bufferHeight; }

    bool getShouldClose() const { return glfwWindowShouldClose(window); }
    void swapBuffers() { glfwSwapBuffers(window); }

    ~Window();
private:
    GLFWwindow* window;
    GLint width;
    GLint height;
    GLint bufferWidth;
    GLint bufferHeight;
};


