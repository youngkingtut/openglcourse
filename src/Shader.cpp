#include "Shader.h"

Shader::Shader() {
    shaderID = 0;
    uniformProjection = 0;
    uniformModel = 0;
    uniformView = 0;
}

void Shader::CreateFromString(const char *vertexCode, const char *fragmentCode) {
    CompileShader(vertexCode, fragmentCode);
}

void Shader::CreateFromFiles(const char *vertexLocation, const char *fragmentLocation) {
    CreateFromString(ReadFile(vertexLocation).c_str(), ReadFile(fragmentLocation).c_str());
}

void Shader::CompileShader(const char *vertexCode, const char *fragmentCode) {
    shaderID = glCreateProgram();

    if(!shaderID) {
        std::cerr << "Error creating shader program" << std::endl;
        exit(1);
    }

    AddShader(shaderID, vertexCode, GL_VERTEX_SHADER);
    AddShader(shaderID, fragmentCode, GL_FRAGMENT_SHADER);

    GLint result = 0;
    GLchar errorLog[1024] = { 0 };

    glLinkProgram(shaderID);
    glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
    if(!result) {
        glGetProgramInfoLog(shaderID, sizeof(errorLog), nullptr, errorLog);
        std::cerr << "Error linking program: " << errorLog << std::endl;
        exit(1);
    }

    uniformModel = glGetUniformLocation(shaderID, "model");
    uniformProjection = glGetUniformLocation(shaderID, "projection");
    uniformView = glGetUniformLocation(shaderID, "view");
}

void Shader::AddShader(GLuint program, const char *shaderCode, GLenum shaderType) {
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderCode, nullptr);
    glCompileShader(shader);

    GLint result = 0;
    GLchar errorLog[1024] = { 0 };

    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
    if(!result) {
        glGetShaderInfoLog(shader, sizeof(errorLog), nullptr, errorLog);
        std::cerr << "Error compiling " << shaderType << ": " << errorLog << std::endl;
    }

    glAttachShader(program, shader);
}

void Shader::UseShader() const {
    glUseProgram(shaderID);
}

void Shader::ClearShader() {
    if(shaderID != 0) {
        glDeleteProgram(shaderID);
        shaderID = 0;
    }

    uniformModel = 0;
    uniformProjection = 0;
}

Shader::~Shader() {
    ClearShader();
}

std::string Shader::ReadFile(const char *fileLocation) {
    std::string content;
    std::ifstream fileStream(fileLocation, std::ios::in);

    if(!fileStream.is_open()) {
        std::cerr << "Failed to read " << fileLocation << std::endl;
        exit(1);
    }

    std::string line;
    while(!fileStream.eof()) {
        std::getline(fileStream, line);
        content.append(line + "\n");
    }

    fileStream.close();
    return content;
}
