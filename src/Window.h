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

    bool* getKeys() { return keys; }
    GLfloat getXChange();
    GLfloat getYChange();

    bool getShouldClose() const { return glfwWindowShouldClose(window); }
    void swapBuffers() { glfwSwapBuffers(window); }

    ~Window();
private:
    GLFWwindow* window{nullptr};

    GLint width;
    GLint height;
    GLint bufferWidth{0};
    GLint bufferHeight{0};

    bool keys[1024] = {false};

    GLfloat lastX{0};
    GLfloat lastY{0};
    GLfloat xChange{0};
    GLfloat yChange{0};

    bool mouseFirstMove{true};

    void createCallbacks();
    static void handleKeys(GLFWwindow* window, int key, int code, int action, int mode);
    static void handleMouse(GLFWwindow* window, double xPosition, double yPosition);
};
