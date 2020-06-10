#pragma ide diagnostic ignored "hicpp-signed-bitwise"
#define STB_IMAGE_IMPLEMENTATION

#include <cmath>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Mesh.h"
#include "Shader.h"
#include "Window.h"
#include "Camera.h"
#include "Texture.h"
#include "Light.h"


void CreateShaders(std::vector<Shader*>* shaderList) {
    auto *shader1 = new Shader();
    shader1->CreateFromFiles("Resources/Shaders/vertex.glsl", "Resources/Shaders/fragment.glsl");
    shaderList->push_back(shader1);
}

void calcAverageNormals(const unsigned int* elements, unsigned int elementCount, GLfloat* vertices,
                        unsigned int vertexCount, unsigned vertexLength, unsigned normalOffset) {
    for(size_t i = 0; i < elementCount; i+=3) {
        unsigned int in0 = elements[i] * vertexLength;
        unsigned int in1 = elements[i + 1] * vertexLength;
        unsigned int in2 = elements[i + 2] * vertexLength;

        glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
        glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
        glm::vec3 normal = glm::normalize(glm::cross(v1, v2));

        in0 += normalOffset;
        in1 += normalOffset;
        in2 += normalOffset;

        vertices[in0] += normal.x;
        vertices[in0+1] += normal.y;
        vertices[in0+2] += normal.z;

        vertices[in1] += normal.x;
        vertices[in1+1] += normal.y;
        vertices[in1+2] += normal.z;

        vertices[in2] += normal.x;
        vertices[in2+1] += normal.y;
        vertices[in2+2] += normal.z;
    }

    for(size_t i = 0; i < vertexCount / vertexLength; i++) {
        unsigned int nOffset = (i * vertexLength) + normalOffset;
        glm::vec3 vec = glm::normalize(glm::vec3(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]));
        vertices[nOffset] = vec.x;
        vertices[nOffset+1] = vec.y;
        vertices[nOffset+2] = vec.z;
    }
}


void CreateObjects(std::vector<Mesh*>* meshList) {
    unsigned int elements[] = {
        0, 3, 1,
        1, 3, 2,
        2, 3, 0,
        0, 1, 2
    };

    GLfloat vertices[] = {
    //      x,     y,    z,    u,    v,   nx,   ny,   nz
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
         0.0f, -1.0f, 1.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
         1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
         0.0f,  1.0f, 0.0f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f
    };

    calcAverageNormals(elements, 12, vertices, 32, 8, 5);

    Mesh* obj1 = new Mesh();
    obj1->CreateMesh(vertices, elements, 32, 12);
    meshList->push_back(obj1);


    Mesh* obj2 = new Mesh();
    obj2->CreateMesh(vertices, elements, 32, 12);
    meshList->push_back(obj2);
}

int main() {
    bool xDirection = true;
    float triOffset = 0.0f;
    float triMaxOffset = 0.8f;
    float triIncrement = 0.03;
    float curAngle = 0.0f;

    std::vector<Mesh*> meshList;
    std::vector<Shader*> shaderList;

    auto window = Window();
    window.initialize();

    auto brickTexture = Texture("Resources/Textures/brick.png");
    brickTexture.LoadTexture();

    auto light = Light(1.0f, 1.0f, 1.0f, 0.2f, 2.0f, -1.0f, -2.0f, 1.0f);

    auto camera = Camera(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0), -90.0, 0);

    CreateObjects(&meshList);
    CreateShaders(&shaderList);

    glm::mat4 projection = glm::perspective(
        45.0f,
        (GLfloat)window.getBufferWidth() / (GLfloat)window.getBufferHeight(),
        0.1f,
        100.0f
        );
    GLuint modelLocation = shaderList[0]->GetModelLocation();
    GLuint projectionLocation = shaderList[0]->GetProjectionLocation();
    GLuint viewLocation = shaderList[0]->GetViewLocation();
    GLuint colorLocation = shaderList[0]->GetColorLocation();
    GLuint intensityLocation = shaderList[0]->GetAmbientIntensityLocation();
    GLuint directionLocation = shaderList[0]->GetDirectionLocation();
    GLuint diffuseIntensityLocation = shaderList[0]->GetDiffuseIntensityLocation();

    GLfloat deltaTime;
    GLfloat lastTime = glfwGetTime();

    // Window loop
    while(!window.getShouldClose()) {
        GLfloat now = glfwGetTime();
        deltaTime = now - lastTime;
        lastTime = now;

        // update user input
        glfwPollEvents();
        camera.keyControl(window.getKeys(), deltaTime);
        camera.mouseControl(window.getXChange(), window.getYChange());

        // Updating uniform
        if(xDirection) {
            triOffset += triIncrement;
        } else {
            triOffset -= triIncrement;
        }

        if(std::abs(triOffset) >= triMaxOffset) {
            xDirection = !xDirection;
        }

        curAngle += 1;

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.7f, -2.5f));
        model = glm::scale(model, glm::vec3(0.4, 0.4, 1.0));

        // clear the window
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // draw
        shaderList[0]->UseShader();

        light.UseLight(intensityLocation, colorLocation, directionLocation, diffuseIntensityLocation);

        glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
        brickTexture.UseTexture();

        glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
        meshList[0]->RenderMesh();

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -0.7f, -2.5f));
        model = glm::scale(model, glm::vec3(0.4, 0.4, 1.0));

        glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
        meshList[1]->RenderMesh();

        glUseProgram(0);

        window.swapBuffers();
    }

    return 0;
}
