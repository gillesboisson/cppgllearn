//
// Created by Gilles Boisson on 2019-04-26.
//

#ifndef CPP_LEARN_GLTEXTURE_H
#define CPP_LEARN_GLTEXTURE_H

#include <glad/glad.h>

#include "stb_image.h"

class GLTexture {
    int width;
    int height;
    int nrChannels;
    unsigned int texture0;
    void initLinearTexture();
public:
    void LoadTexture(const char* imagePath);
    void Bind();

    void Activate(unsigned int index = 0);

    unsigned int GetTexture();


};


#endif //CPP_LEARN_GLTEXTURE_H
