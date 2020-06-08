#pragma once

#include <cmath>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
    Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch);
    ~Camera() = default;

    glm::mat4 calculateViewMatrix();

    void keyControl(const bool* keys, GLfloat deltaTime);
    void mouseControl(GLfloat xChange, GLfloat yChange);

private:
    glm::vec3 position{0};
    glm::vec3 front{0};
    glm::vec3 up{0};
    glm::vec3 right{0};
    glm::vec3 worldUp{0};

    GLfloat yaw{0};
    GLfloat pitch{0};

    GLfloat moveSpeed{2};
    GLfloat turnSpeed{0.1};

    void update();
};
