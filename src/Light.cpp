#include "Light.h"

Light::Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat ambientIntensity, GLfloat diffuseIntensity) {
    this->color = glm::vec3(red, green, blue);
    this->ambientIntensity = ambientIntensity;
    this->diffuseIntensity = diffuseIntensity;
}
