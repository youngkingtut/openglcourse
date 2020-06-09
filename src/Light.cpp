#include "Light.h"

Light::Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat ambientIntensity) {
    this->color = glm::vec3(red, green, blue);
    this->ambientIntensity = ambientIntensity;
}

void Light::UseLight(GLfloat ambientIntensityLocation, GLfloat ambientColorLocation) const {
    glUniform3f(ambientColorLocation, color.x, color.y, color.z);
    glUniform1f(ambientIntensityLocation, ambientIntensity);
}
