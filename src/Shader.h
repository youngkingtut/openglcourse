#pragma once

#include <cstdio>
#include <string>
#include <iostream>
#include <fstream>

#include <GL/glew.h>

class Shader {
public:
    Shader();

    void CreateFromString(const char* vertexCode, const char* fragmentCode);
    void CreateFromFiles(const char* vertexLocation, const char* fragmentLocation);

    GLuint GetProjectionLocation() const;
    GLuint GetModelLocation() const;

    void UseShader() const;
    void ClearShader();

    ~Shader();
private:
    GLuint shaderID;
    GLuint uniformProjection;
    GLuint uniformModel;

    void CompileShader(const char* vertexCode, const char* fragmentCode);
    static void AddShader(GLuint program, const char* shaderCode, GLenum shaderType);
    static std::string ReadFile(const char* fileLocation);
};
