#include "Shader.h"

Shader::Shader() {
    shaderID = 0;
    uniformProjection = 0;
    uniformModel = 0;
    uniformView = 0;
    pointLightCount = 0;
}

void Shader::CreateFromString(const char *vertexCode, const char *fragmentCode) {
    CompileShader(vertexCode, fragmentCode);
}

void Shader::CreateFromFiles(const char *vertexLocation, const char *fragmentLocation) {
    CreateFromString(ReadFile(vertexLocation).c_str(), ReadFile(fragmentLocation).c_str());
}

void Shader::CompileShader(const char *vertexCode, const char *fragmentCode) {
    shaderID = glCreateProgram();

    if (!shaderID) {
        std::cerr << "Error creating shader program" << std::endl;
        exit(1);
    }

    AddShader(shaderID, vertexCode, GL_VERTEX_SHADER);
    AddShader(shaderID, fragmentCode, GL_FRAGMENT_SHADER);

    GLint result = 0;
    GLchar errorLog[1024] = {0};

    glLinkProgram(shaderID);
    glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
    if (!result) {
        glGetProgramInfoLog(shaderID, sizeof(errorLog), nullptr, errorLog);
        std::cerr << "Error linking program: " << errorLog << std::endl;
        exit(1);
    }

    uniformModel = glGetUniformLocation(shaderID, "model");
    uniformProjection = glGetUniformLocation(shaderID, "projection");
    uniformView = glGetUniformLocation(shaderID, "view");
    uniformDirectionalLight.uniformColor = glGetUniformLocation(shaderID, "directionalLight.base.color");
    uniformDirectionalLight.uniformAmbientIntensity = glGetUniformLocation(shaderID,
                                                                           "directionalLight.base.ambientIntensity");
    uniformDirectionalLight.uniformDirection = glGetUniformLocation(shaderID, "directionalLight.direction");
    uniformDirectionalLight.uniformDiffuseIntensity = glGetUniformLocation(shaderID,
                                                                           "directionalLight.base.diffuseIntensity");
    uniformEyePosition = glGetUniformLocation(shaderID, "eyePosition");
    uniformShininess = glGetUniformLocation(shaderID, "material.shininess");
    uniformSpecularIntensity = glGetUniformLocation(shaderID, "material.specularIntensity");
    uniformPointLightCount = glGetUniformLocation(shaderID, "pointLightCount");

    for (auto i = 0; i < MAX_POINT_LIGHTS; i++) {
        char locBuff[100] = {'\0'};

        snprintf(locBuff, sizeof(locBuff), "pointLights[%d].base.color", i);
        uniformPointLight[i].uniformColor = glGetUniformLocation(shaderID, locBuff);
        snprintf(locBuff, sizeof(locBuff), "pointLights[%d].base.ambientIntensity", i);
        uniformPointLight[i].uniformAmbientIntensity = glGetUniformLocation(shaderID, locBuff);
        snprintf(locBuff, sizeof(locBuff), "pointLights[%d].base.diffuseIntensity", i);
        uniformPointLight[i].uniformDiffuseIntensity = glGetUniformLocation(shaderID, locBuff);
        snprintf(locBuff, sizeof(locBuff), "pointLights[%d].position", i);
        uniformPointLight[i].uniformPosition = glGetUniformLocation(shaderID, locBuff);
        snprintf(locBuff, sizeof(locBuff), "pointLights[%d].constant", i);
        uniformPointLight[i].uniformConstant = glGetUniformLocation(shaderID, locBuff);
        snprintf(locBuff, sizeof(locBuff), "pointLights[%d].linear", i);
        uniformPointLight[i].uniformLinear = glGetUniformLocation(shaderID, locBuff);
        snprintf(locBuff, sizeof(locBuff), "pointLights[%d].exponent", i);
        uniformPointLight[i].uniformExponent = glGetUniformLocation(shaderID, locBuff);

    }

}

void Shader::AddShader(GLuint program, const char *shaderCode, GLenum shaderType) {
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderCode, nullptr);
    glCompileShader(shader);

    GLint result = 0;
    GLchar errorLog[1024] = {0};

    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
    if (!result) {
        glGetShaderInfoLog(shader, sizeof(errorLog), nullptr, errorLog);
        std::cerr << "Error compiling " << shaderType << ": " << errorLog << std::endl;
    }

    glAttachShader(program, shader);
}

void Shader::UseShader() const {
    glUseProgram(shaderID);
}

void Shader::ClearShader() {
    if (shaderID != 0) {
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

    if (!fileStream.is_open()) {
        std::cerr << "Failed to read " << fileLocation << std::endl;
        exit(1);
    }

    std::string line;
    while (!fileStream.eof()) {
        std::getline(fileStream, line);
        content.append(line + "\n");
    }

    fileStream.close();
    return content;
}

void Shader::SetDirectionalLight(DirectionalLight *dLight) const {
    dLight->UseLight(uniformDirectionalLight.uniformAmbientIntensity, uniformDirectionalLight.uniformColor,
                     uniformDirectionalLight.uniformDirection, uniformDirectionalLight.uniformDiffuseIntensity);
}

void Shader::SetPointLights(PointLight *pLight, unsigned int lightCount) {
    if (lightCount > MAX_POINT_LIGHTS) {
        lightCount = MAX_POINT_LIGHTS;
    }

    glUniform1i(uniformPointLightCount, lightCount);

    for (auto i = 0; i < lightCount; i++) {
        pLight[i].UseLight(uniformPointLight[i].uniformAmbientIntensity, uniformPointLight[i].uniformColor,
                           uniformPointLight[i].uniformDiffuseIntensity,
                           uniformPointLight[i].uniformPosition, uniformPointLight[i].uniformConstant,
                           uniformPointLight[i].uniformLinear, uniformPointLight[i].uniformExponent);
    }
}
