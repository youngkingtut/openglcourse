#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

class Light {
public:
    Light() = default;
    Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat ambientIntensity, GLfloat diffuseIntensity);

protected:
    glm::vec3 color{};
    GLfloat ambientIntensity{};
    GLfloat diffuseIntensity{};
};


