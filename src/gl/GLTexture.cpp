//
// Created by Gilles Boisson on 2019-04-26.
//
#include <iostream>

#include "GLTexture.h"



void GLTexture::LoadTexture(const char *imagePath) {
    glGenTextures(1, &texture0);
    initLinearTexture();
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(imagePath, &width, &height, &nrChannels, 0);
    GLenum chanelE = nrChannels > 3 ? GL_RGBA : GL_RGB;
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, chanelE, width, height, 0,chanelE, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture " << imagePath << std::endl;
    }

    stbi_image_free(data);

}

void GLTexture::initLinearTexture() {
    Bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
}

void GLTexture::Bind() {
    glBindTexture(GL_TEXTURE_2D, texture0);
}

unsigned int GLTexture::getGLId() {
    return texture0;
}

void GLTexture::activate(unsigned int index) {
    glActiveTexture(GL_TEXTURE0 + index); // activate the texture unit first before binding texture
    Bind();
}

void GLTexture::dispose(){
    glDeleteTextures(1,&texture0);
}
