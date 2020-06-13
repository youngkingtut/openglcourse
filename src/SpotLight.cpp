#include "SpotLight.h"

SpotLight::SpotLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity, GLfloat dIntensity, GLfloat xPos,
                     GLfloat yPos, GLfloat zPos, GLfloat con, GLfloat lin, GLfloat exp, GLfloat xDir, GLfloat yDir,
                     GLfloat zDir, GLfloat edge) : PointLight(red, green, blue, aIntensity, dIntensity, xPos, yPos,
                                                              zPos, con, lin, exp) {
    direction = glm::normalize(glm::vec3(xDir, yDir, zDir));
    this->edge = edge;
    processedEdge = cos(glm::radians(edge));
}

void SpotLight::UseLight(GLuint ambientIntensityLocation, GLuint colorLocation, GLuint diffuseIntensityLocation,
                         GLuint positionLocation, GLuint constantLocation, GLuint linearLocation,
                         GLuint exponentLocation, GLuint directionLocation, GLuint edgeLocation) const {
    glUniform3f(colorLocation, color.x, color.y, color.z);
    glUniform1f(ambientIntensityLocation, ambientIntensity);
    glUniform1f(diffuseIntensityLocation, diffuseIntensity);

    glUniform3f(positionLocation, position.x, position.y, position.z);
    glUniform1f(constantLocation, constant);
    glUniform1f(linearLocation, linear);
    glUniform1f(exponentLocation, exponent);

    glUniform3f(directionLocation, direction.x, direction.y, direction.z);
    glUniform1f(edgeLocation, processedEdge);
}

void SpotLight::SetFlash(glm::vec3 pos, glm::vec3 dir) {
    direction = dir;
    position = pos;
}
