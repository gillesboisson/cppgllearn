//
// Created by Gilles Boisson on 2019-05-29.
//

#ifndef CPP_LEARN_SPRITESHADER_H
#define CPP_LEARN_SPRITESHADER_H

#include "../../gl/GLShader.h"
#include "../../gl/GLRenderer.h"

class SpriteShader :GLShader{
public:
    static SpriteShader* init(GLRenderer* renderer);
    SpriteShader();
    void updateCameraUniform(Camera* camera);

    uint32_t _vpLocation;
};


#endif //CPP_LEARN_SPRITESHADER_H
