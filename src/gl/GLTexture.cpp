//
// Created by Gilles Boisson on 2019-04-26.
//
#include <iostream>

#include "GLTexture.h"
#include "GLHelper.h"



void GLTexture::loadTexture2d(const char *imagePath) {
    gen();


    stbi_set_flip_vertically_on_load(true);
    int nrChannels;
    unsigned char *data = stbi_load(imagePath, &_width, &_height, &nrChannels, 0);

    _format = nrChannels > 3 ? GL_RGBA : GL_RGB;
    _target = GL_TEXTURE_2D;
    _type = GL_UNSIGNED_BYTE;

    initLinearTexture();

    if (data)
    {
        glBindTexture(_target,_texture);
        glTexImage2D(_target, 0, _format, _width, _height, 0,_format, _type, data);
        glGenerateMipmap(_target);
        glBindTexture(_target,0);
    }
    else
    {
        std::cout << "Failed to load texture " << imagePath << std::endl;
    }

#ifdef DEBUG_GL
    GLPrintErrors("GLTexture :: loadTexture2d");
#endif
    stbi_image_free(data);

}

void GLTexture::initLinearTexture() {
    glBindTexture(_target, _texture);
    glTexParameteri(_target, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(_target, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    glTexParameteri(_target, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glBindTexture(_target, 0);

#ifdef DEBUG_GL
    GLPrintErrors("GLTexture :: initLinearTexture");
#endif
}

void GLTexture::bind() const{
    glBindTexture(_target, _texture);
}


void GLTexture::activate(unsigned int index) const{
    glBindTexture(GL_TEXTURE_2D,_texture);
    glActiveTexture(GL_TEXTURE0 + index); // activate the texture unit first before binding texture

}

void GLTexture::dispose(){
    glDeleteTextures(1,&_texture);
}

void GLTexture::initEmpty(GLenum format, GLenum target, GLenum type, int width, int height) {
    gen();
    _target = target;
    _format = format;
    _type = type;
    _width = width;
    _height = height;

    glBindTexture(_target, _texture);
    glTexParameteri(_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(_target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(_target, 0, _format, _width, _height, 0,_format, _type, nullptr);
    glBindTexture(_target, 0);

#ifdef DEBUG_GL
    GLPrintErrors("GLTexture :: initEmpty");
#endif
}

void GLTexture::gen() {
    if(_texture == 0) glGenTextures(1,&_texture);


}

int GLTexture::getWidth() const {
    return _width;
}

int GLTexture::getHeight() const {
    return _height;
}

GLuint GLTexture::getGLId() const {
    return _texture;
}

GLenum GLTexture::getType() const {
    return _type;
}

GLenum GLTexture::getTarget() const {
    return _target;
}

GLenum GLTexture::getFormat() const {
    return _format;
}

