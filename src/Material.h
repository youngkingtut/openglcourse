#pragma once

#include <GL/glew.h>


class Material {
public:
    Material(GLfloat specularIntensity, GLfloat shininess);
    void UseMaterial(GLuint specularIntensityLocation, GLuint shininessLocation);

private:
    GLfloat specularIntensity;
    GLfloat shininess;
};
