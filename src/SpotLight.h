#pragma once

#include "PointLight.h"

class SpotLight :  public PointLight {
public:
    SpotLight() = default;

    SpotLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity, GLfloat dIntensity,
              GLfloat xPos, GLfloat yPos, GLfloat zPos, GLfloat con, GLfloat lin, GLfloat exp,
              GLfloat xDir, GLfloat yDir, GLfloat zDir, GLfloat edge);

    void UseLight(GLuint ambientIntensityLocation, GLuint colorLocation, GLuint diffuseIntensityLocation,
                  GLuint positionLocation, GLuint constantLocation, GLuint linearLocation,
                  GLuint exponentLocation, GLuint directionLocation, GLuint edgeLocation) const;

    void SetFlash(glm::vec3 pos, glm::vec3 dir);

private:
    glm::vec3 direction{};
    GLfloat edge{};
    GLfloat processedEdge{};


};


