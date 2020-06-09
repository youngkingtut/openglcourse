#include "Texture.h"

Texture::Texture(std::string fileLocation) {
    this->fileLocation = std::move(fileLocation);
}

Texture::~Texture() {
    ClearTexture();
}

void Texture::LoadTexture() {
    unsigned char* texData = stbi_load(fileLocation.c_str(), &width, &height, &bitDepth, 0);
    if(!texData) {
        std::cerr << "Failed to find texture at " << fileLocation << std::endl;
        exit(1);
    }

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(texData);
}

void Texture::UseTexture() const {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture::ClearTexture() {
    if(textureID != 0) {
        glDeleteTextures(1, &textureID);
        textureID = 0;
        width = 0;
        height = 0;
        bitDepth = 0;
        fileLocation = nullptr;
    }
}