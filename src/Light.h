#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

class Light {
public:
    Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat ambientIntensity);
    void UseLight(GLfloat ambientIntensityLocation, GLfloat ambientColorLocation) const;

private:
    glm::vec3 color{1.0f, 1.0f, 1.0f};
    GLfloat ambientIntensity{1.0f};
};


