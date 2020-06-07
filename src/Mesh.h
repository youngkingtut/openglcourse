#pragma once

#include <GL/glew.h>

class Mesh {
public:
    Mesh();

    void CreateMesh(GLfloat* vertices, unsigned int* elements, unsigned int numOfVertices, unsigned int numOfElements);
    void RenderMesh();
    void ClearMesh();

    ~Mesh();
private:
    GLuint VAO;
    GLuint VBO;
    GLuint EBO;
    GLsizei elementCount;
};


