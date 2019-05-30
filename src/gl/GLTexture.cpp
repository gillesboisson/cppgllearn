//
// Created by Gilles Boisson on 2019-04-26.
//
#include <iostream>

#include "GLTexture.h"
#include "GLHelper.h"

const char *cubeMapNames[] = {"pos-x",
                              "neg-x",
                              "pos-y",
                              "neg-y",
                              "pos-z",
                              "neg-z"
                            };

void GLTexture::loadTexture2d(const char *imagePath,bool flipTextureV) {
    gen();

    if(flipTextureV) {
        stbi_set_flip_vertically_on_load(true);
    }else{
        stbi_set_flip_vertically_on_load(false);

    }
    int nrChannels;
    unsigned char *data = stbi_load(imagePath, &_width, &_height, &nrChannels, 0);

    _format = nrChannels > 3 ? GL_RGBA : GL_RGB;
    _target = GL_TEXTURE_2D;
    _type = GL_UNSIGNED_BYTE;

    initLinearTexture();

    if (data)
    {
        glBindTexture(_target,_glId);
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

void GLTexture::loadTextureCubeMap(const char *baseImagePath,const char *fileExtension) {
    gen();
    stbi_set_flip_vertically_on_load(true);
    int nrChannels;

    char *imagePath = new char[100];
    _target = GL_TEXTURE_CUBE_MAP;
    _type = GL_UNSIGNED_BYTE;

    glBindTexture(_target,_glId);

    for (int i = 0; i < 6; ++i) {

        sprintf(imagePath,"%s-%s.%s",baseImagePath,cubeMapNames[i],fileExtension);
        printf("Load cubemap face %s\n",imagePath);
        unsigned char *data = stbi_load(imagePath, &_width, &_height, &nrChannels, 0);

        if (data) {
            if (i == 0) {
                _format = nrChannels > 3 ? GL_RGBA : GL_RGB;
            }

            glTexImage2D(
                GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                0, _format, _width, _height, 0, _format, _type, data
            );
        }else{
            std::cout << "Failed to load texture " << imagePath << std::endl;
        }

        stbi_image_free(data);
    }

    glTexParameteri(_target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(_target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(_target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(_target, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    glBindTexture(_target,0);

    delete[] imagePath;


}

void GLTexture::initLinearTexture() {
    glBindTexture(_target, _glId);
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
    glBindTexture(_target, _glId);
}


void GLTexture::activate(unsigned int index) const{
    glBindTexture(GL_TEXTURE_2D,_glId);
    glActiveTexture(GL_TEXTURE0 + index); // activate the texture unit first before binding texture

}

void GLTexture::dispose(){
    glDeleteTextures(1,&_glId);
}

void GLTexture::initEmptyTexture2d(GLenum format, GLenum target, GLenum type, int width, int height) {
    gen();
    _target = target;
    _format = format;
    _type = type;
    _width = width;
    _height = height;

    glBindTexture(_target, _glId);
    glTexParameteri(_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(_target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(_target, 0, _format, _width, _height, 0,_format, _type, nullptr);
    glBindTexture(_target, 0);

#ifdef DEBUG_GL
    GLPrintErrors("GLTexture :: initEmpty");
#endif
}

void GLTexture::gen() {
    if(_glId == 0) glGenTextures(1,&_glId);


}

int GLTexture::getWidth() const {
    return _width;
}

int GLTexture::getHeight() const {
    return _height;
}

GLuint GLTexture::getGLId() const {
    return _glId;
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

GLTexture::~GLTexture(){
    dispose();
}
