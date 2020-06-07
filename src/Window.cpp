#include "Window.h"

Window::Window(): Window(800, 600) {}

Window::Window(GLint windowWidth, GLint windowHeight) {
    width = windowWidth;
    height = windowHeight;
}

Window::~Window() {
    glfwDestroyWindow(window);
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

    // Handle key and mouse input
    createCallbacks();
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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

    glfwSetWindowUserPointer(window, this);
}

void Window::createCallbacks() {
    glfwSetKeyCallback(window, handleKeys);
    glfwSetCursorPosCallback(window, handleMouse);
}

void Window::handleKeys(GLFWwindow *window, int key, int code, int action, int mode) {
    auto theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    if(key >= 0 && key < 1024) {
        if(action == GLFW_PRESS) {
            theWindow->keys[key] = true;
        } else if (action == GLFW_RELEASE) {
            theWindow->keys[key] = false;
        }
    }
}

void Window::handleMouse(GLFWwindow *window, double xPosition, double yPosition) {
    auto theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

    if(theWindow->mouseFirstMove) {
        theWindow->lastX = xPosition;
        theWindow->lastY = yPosition;
        theWindow->mouseFirstMove = false;
    }

    theWindow->xChange = xPosition - theWindow->lastX;
    theWindow->yChange = theWindow->lastY - yPosition;

    theWindow->lastX = xPosition;
    theWindow->lastY = yPosition;
}

GLfloat Window::getXChange() {
    GLfloat temp = xChange;
    xChange = 0;
    return temp;
}

GLfloat Window::getYChange() {
    GLfloat temp = yChange;
    yChange = 0;
    return temp;
}
