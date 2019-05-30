//
// Created by Gilles Boisson on 2019-05-29.
//

#include "SpriteShader.h"

SpriteShader* SpriteShader::init(GLRenderer *renderer) {
    auto shader = new SpriteShader();
    renderer->registerShader("sprite",shader);
    return shader;
}

SpriteShader::SpriteShader():GLShader("./assets/shaders/sprite.vert","./assets/shaders/sprite.frag"){
    useProgram();
    _vpLocation = getUniformLocation("vp");
}

void SpriteShader::updateCameraUniform(Camera *camera) {
    setUniformMat4v(_vpLocation,camera->getVP());
}

