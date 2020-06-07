#include "Mesh.h"

Mesh::Mesh() {
    VAO = 0;
    VBO = 0;
    EBO = 0;
    elementCount = 0;
}

void Mesh::CreateMesh(GLfloat *vertices, unsigned int *elements, unsigned int numOfVertices, unsigned int numOfElements) {
    elementCount = numOfElements;

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    {
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements[0]) * numOfElements, elements, GL_STATIC_DRAW);

        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * numOfVertices, vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
    glBindVertexArray(0);
}

void Mesh::RenderMesh() const {
    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glDrawElements(GL_TRIANGLES, elementCount, GL_UNSIGNED_INT, nullptr);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Mesh::ClearMesh() {
    if(EBO != 0) {
        glDeleteBuffers(1, &EBO);
        EBO = 0;
    }

    if(VBO != 0) {
        glDeleteBuffers(1, &VBO);
        VBO = 0;
    }

    if(VAO != 0) {
        glDeleteVertexArrays(1, &VAO);
        VAO = 0;
    }

    elementCount = 0;
}

Mesh::~Mesh() {
    ClearMesh();
}
