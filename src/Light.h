#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

class Light {
public:
    Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat ambientIntensity,
          GLfloat xDirection, GLfloat yDirection, GLfloat zDirection, GLfloat diffuseIntensity);
    void UseLight(GLfloat ambientIntensityLocation, GLfloat colorLocation, GLfloat directionLocation, GLfloat diffuseIntensityLocation) const;

private:
    glm::vec3 color{1.0f, 1.0f, 1.0f};
    GLfloat ambientIntensity{1.0f};

    glm::vec3 direction{0.0f, 1.0f, 0.0f};
    GLfloat diffuseIntensity{1.0f};
};


