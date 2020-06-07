#pragma ide diagnostic ignored "hicpp-signed-bitwise"
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

void CreateShaders(std::vector<Shader*>* shaderList) {
    auto *shader1 = new Shader();
    shader1->CreateFromFiles("Resources/Shaders/vertex.glsl", "Resources/Shaders/fragment.glsl");
    shaderList->push_back(shader1);
}

void CreateObjects(std::vector<Mesh*>* meshList) {
    unsigned int indices[] = {
        0, 3, 1,
        1, 3, 2,
        2, 3, 0,
        0, 1, 2
    };

    GLfloat vertices[] = {
        -1.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 1.0f,
        1.0f, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f
    };

    Mesh* obj1 = new Mesh();
    obj1->CreateMesh(vertices, indices, 12, 12);
    meshList->push_back(obj1);


    Mesh* obj2 = new Mesh();
    obj2->CreateMesh(vertices, indices, 12, 12);
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

    // Window loop
    while(!window.getShouldClose()) {
        // get user input
        glfwPollEvents();

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
        model = glm::translate(model, glm::vec3(-triOffset, 0.7f, -2.5f));
        model = glm::scale(model, glm::vec3(0.4, 0.4, 1.0));

        // clear the window
        glClearColor(0.2f, 0.0f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // draw
        shaderList[0]->UseShader();
        glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
        meshList[0]->RenderMesh();

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(triOffset, -0.7f, -2.5f));
        model = glm::scale(model, glm::vec3(0.4, 0.4, 1.0));

        glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
        meshList[1]->RenderMesh();

        glUseProgram(0);

        window.swapBuffers();
    }

    return 0;
}
