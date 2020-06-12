#pragma once

#include <GL/glew.h>

#include "Light.h"

class DirectionalLight : public Light {
public:
    DirectionalLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat ambientIntensity, GLfloat xDirection,
                     GLfloat yDirection, GLfloat zDirection, GLfloat diffuseIntensity);

    void UseLight(GLfloat ambientIntensityLocation, GLfloat colorLocation, GLfloat directionLocation,
                  GLfloat diffuseIntensityLocation) const;

private:
    glm::vec3 direction{};
};


