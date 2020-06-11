#include "Material.h"

Material::Material(GLfloat specularIntensity, GLfloat shininess) {
    this->specularIntensity = specularIntensity;
    this->shininess = shininess;
}

void Material::UseMaterial(GLuint specularIntensityLocation, GLuint shininessLocation) {
    glUniform1f(specularIntensityLocation, specularIntensity);
    glUniform1f(shininessLocation, shininess);
}
