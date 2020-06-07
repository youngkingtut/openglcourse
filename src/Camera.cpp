#include "Camera.h"

Camera::Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch) {
    position = startPosition;
    worldUp = startUp;
    yaw = startYaw;
    pitch = startPitch;
    front = glm::vec3(0.0f, 0.0f, -1.0f);

    update();
}

void Camera::update() {
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(front);

    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}

void Camera::keyControl(const bool* keys, const GLfloat deltaTime) {
    GLfloat velocity = moveSpeed * deltaTime;

    if(keys[GLFW_KEY_W]) {
        position += front * velocity;
    }
    if(keys[GLFW_KEY_S]) {
        position -= front * velocity;
    }
    if(keys[GLFW_KEY_A]) {
        position -= right * velocity;
    }
    if(keys[GLFW_KEY_D]) {
        position += right * velocity;
    }
    if(keys[GLFW_KEY_SPACE]) {
        position += up * velocity;
    }
    if(keys[GLFW_KEY_LEFT_CONTROL]) {
        position -= up * velocity;
    }
}

void Camera::mouseControl(GLfloat xChange, GLfloat yChange) {
    xChange *= turnSpeed;
    yChange *= turnSpeed;

    yaw += xChange;
    pitch += yChange;

    if(pitch > 89.0) {
        pitch = 89.0;
    }

    if(pitch < -89.0) {
        pitch = -89.0;
    }

    update();
}

glm::mat4 Camera::calculateViewMatrix() {
    return glm::lookAt(position, position + front, up);
}
