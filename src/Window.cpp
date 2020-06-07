#include "Window.h"

Window::Window(): Window(800, 600) {}

Window::Window(GLint windowWidth, GLint windowHeight) {
    width = windowWidth;
    height = windowHeight;
    bufferHeight = 0;
    bufferWidth = 0;
    window = nullptr;
}

void Window::initialize() {
    // Initialize GLFW
    if(!glfwInit()) {
        std::cerr << "GLFW failed to initialize";
        glfwTerminate();
        exit(1);
    }

    // Setup GLFW window properties
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    window = glfwCreateWindow(width, height, "udemy", nullptr, nullptr);
    if(!window) {
        std::cerr << "GLFW failed to create window";
        glfwTerminate();
        exit(1);
    }

    // Get Buffer size information
    glfwGetFramebufferSize(window, &bufferWidth, &bufferHeight);

    // Set context for GLEW to use
    glfwMakeContextCurrent(window);

    // Initialize GLEW (using experimental features)
    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK) {
        std::cerr << "GLEW failed to initialize.";
        glfwDestroyWindow(window);
        glfwTerminate();
        exit(1);
    }

    // GL Settings
    glEnable(GL_DEPTH_TEST);

    // Setup viewport size
    glViewport(0, 0, bufferWidth, bufferHeight);
}

Window::~Window() {
    glfwDestroyWindow(window);
}
