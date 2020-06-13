#pragma once

#include <cstdio>
#include <string>
#include <iostream>
#include <fstream>

#include <GL/glew.h>

#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "CommonValues.h"

class Shader {
public:
    Shader();

    void CreateFromString(const char* vertexCode, const char* fragmentCode);
    void CreateFromFiles(const char* vertexLocation, const char* fragmentLocation);

    GLuint GetProjectionLocation() const { return uniformProjection; }
    GLuint GetModelLocation() const { return uniformModel; }
    GLuint GetViewLocation() const { return uniformView; }
    GLuint GetEyePosition() const { return uniformEyePosition; }
    GLuint GetSpecularIntensity() const { return uniformSpecularIntensity; }
    GLuint GetShininess() const { return uniformShininess; }

    void SetDirectionalLight(DirectionalLight* dLight) const;
    void SetPointLights(PointLight* pLight, unsigned int lightCount);
    void SetSpotLights(SpotLight* sLight, unsigned int lightCount);

    void UseShader() const;
    void ClearShader();

    ~Shader();
private:
    GLuint shaderID{};
    GLuint uniformProjection{};
    GLuint uniformModel{};
    GLuint uniformView{};
    GLuint uniformEyePosition{};
    GLuint uniformSpecularIntensity{};
    GLuint uniformShininess{};
    GLuint uniformPointLightCount{};
    GLuint uniformSpotLightCount{};

    struct {
        GLuint uniformColor{};
        GLuint uniformAmbientIntensity{};
        GLuint uniformDiffuseIntensity{};
        GLuint uniformDirection{};
    } uniformDirectionalLight;

    struct {
        GLuint uniformColor{};
        GLuint uniformAmbientIntensity{};
        GLuint uniformDiffuseIntensity{};

        GLuint uniformPosition{};
        GLuint uniformConstant{};
        GLuint uniformLinear{};
        GLuint uniformExponent{};
    } uniformPointLight[MAX_POINT_LIGHTS];

    struct {
        GLuint uniformColor{};
        GLuint uniformAmbientIntensity{};
        GLuint uniformDiffuseIntensity{};

        GLuint uniformPosition{};
        GLuint uniformConstant{};
        GLuint uniformLinear{};
        GLuint uniformExponent{};

        GLuint uniformDirection{};
        GLuint uniformEdge{};
    } uniformSpotLight[MAX_SPOT_LIGHTS] ;

    void CompileShader(const char* vertexCode, const char* fragmentCode);
    static void AddShader(GLuint program, const char* shaderCode, GLenum shaderType);
    static std::string ReadFile(const char* fileLocation);
};
