#include "DirectionalLight.h"


DirectionalLight::DirectionalLight(
    GLfloat red,
    GLfloat green,
    GLfloat blue,
    GLfloat ambientIntensity,
    GLfloat xDirection,
    GLfloat yDirection,
    GLfloat zDirection,
    GLfloat diffuseIntensity
) : Light(red, green, blue, ambientIntensity, diffuseIntensity) {
    this->direction = glm::vec3(xDirection, yDirection, zDirection);
}

void DirectionalLight::UseLight(GLfloat ambientIntensityLocation, GLfloat colorLocation, GLfloat directionLocation,
                                GLfloat diffuseIntensityLocation) const {
    glUniform3f(colorLocation, color.x, color.y, color.z);
    glUniform1f(ambientIntensityLocation, ambientIntensity);
    glUniform3f(directionLocation, direction.x, direction.y, direction.z);
    glUniform1f(diffuseIntensityLocation, diffuseIntensity);
}
