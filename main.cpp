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
GLuint SHADER;
GLuint uniformModel;

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
    "uniform mat4 model;\n"
    "void main() {\n"
    "   gl_Position = model * vec4(position, 1.0);\n"
    "}";

// Fragment Shader
static const char* fragmentShader =
    "#version 330\n"
    "out vec4 color;\n"
    "void main() {\n"
    "   color = vec4(0.0, 0.2, 0.9, 1.0);\n"
    "}";


void CreateTriangle() {
    GLfloat vertices[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f
    };

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    {
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    glBindVertexArray(0);
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

    // Setup viewport size
    glViewport(0, 0, bufferWidth, bufferHeight);


    CreateTriangle();
    CompileShaders();

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
        model = glm::translate(model, glm::vec3(triOffset, 0.0f, 0.0f));
        model = glm::rotate(model, curAngle * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(model, glm::vec3(triOffset, triOffset, 0.0));


        // clear the window
        glClearColor(0.2f, 0.0f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw
        glUseProgram(SHADER);
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        {
            glDrawArrays(GL_TRIANGLES, 0, 3);
        }
        glBindVertexArray(0);
        glUseProgram(0);

        glfwSwapBuffers(window);
    }

    return 0;
}