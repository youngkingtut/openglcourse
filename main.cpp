#pragma clang diagnostic push
#pragma ide diagnostic ignored "hicpp-signed-bitwise"
#include <iostream>
#include <string.h>
#include <cmath>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Window dimensions
const GLint WIDTH = 800;
const GLint HEIGHT = 600;

GLuint VAO;
GLuint VBO;
GLuint EBO;
GLuint SHADER;
GLuint uniformModel;
GLuint uniformProjection;

bool xDirection = true;
float triOffset = 0.0f;
float triMaxOffset = 0.8f;
float triIncrement = 0.03;
float curAngle = 0.0f;
const float toRadians = 3.14f / 180.0f;


// Vertex Shader
static const char* vertexShader =
    "#version 330\n"
    "layout(location = 0) in vec3 position;\n"
    "out vec4 vertexColor;\n"
    "uniform mat4 model;\n"
    "uniform mat4 projection;\n"
    "void main() {\n"
    "   gl_Position = projection * model * vec4(position, 1.0);"
    "   vertexColor = vec4(clamp(position.xy, 0.0f, 1.0f), 0.5f, 1.0f);\n"
    "}";

// Fragment Shader
static const char* fragmentShader =
    "#version 330\n"
    "in vec4 vertexColor;"
    "out vec4 color;\n"
    "void main() {\n"
    "   color = vertexColor;\n"
    "}";


void CreateTriangle() {
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

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    {
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
        glEnableVertexAttribArray(0);


    }
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void AddShaders(GLuint program, const char* shaderCode, GLenum shaderType) {
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

int CompileShaders() {
    SHADER = glCreateProgram();

    if(!SHADER) {
        std::cerr << "Error creating shader program" << std::endl;
        return 1;
    }

    AddShaders(SHADER, vertexShader, GL_VERTEX_SHADER);
    AddShaders(SHADER, fragmentShader, GL_FRAGMENT_SHADER);

    GLint result = 0;
    GLchar errorLog[1024] = { 0 };

    glLinkProgram(SHADER);
    glGetProgramiv(SHADER, GL_LINK_STATUS, &result);
    if(!result) {
        glGetProgramInfoLog(SHADER, sizeof(errorLog), nullptr, errorLog);
        std::cerr << "Error linking program: " << errorLog << std::endl;
        return 1;
    }

    uniformModel = glGetUniformLocation(SHADER, "model");
    uniformProjection = glGetUniformLocation(SHADER, "projection");

    return 0;
}

int main() {
    // Initialize GLFW
    if(!glfwInit()) {
        std::cerr << "GLFW failed to initialize";
        glfwTerminate();
        return 1;
    }

    // Setup GLFW window properties
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "udemy", nullptr, nullptr);
    if(!window) {
        std::cerr << "GLFW failed to create window";
        glfwTerminate();
        return 1;
    }

    // Get Buffer size information
    int bufferWidth;
    int bufferHeight;
    glfwGetFramebufferSize(window, &bufferWidth, &bufferHeight);

    // Set context for GLEW to use
    glfwMakeContextCurrent(window);

    // Initialize GLEW (using experimental features)
    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK) {
        std::cerr << "GLEW failed to initialize.";
        glfwDestroyWindow(window);
        glfwTerminate();
        return 1;
    }

    // GL Settings
    glEnable(GL_DEPTH_TEST);

    // Setup viewport size
    glViewport(0, 0, bufferWidth, bufferHeight);


    CreateTriangle();
    CompileShaders();

    glm::mat4 projection = glm::perspective(45.0f, (GLfloat)bufferWidth / (GLfloat)bufferHeight, 0.1f, 100.0f);

    // Window loop
    while(!glfwWindowShouldClose(window)) {
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
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
        model = glm::rotate(model, curAngle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.4, 0.4, 1.0));

        // clear the window
        glClearColor(0.2f, 0.0f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // draw
        glUseProgram(SHADER);
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        glBindVertexArray(VAO);
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, nullptr);
        }
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        glUseProgram(0);

        glfwSwapBuffers(window);
    }

    return 0;
}
