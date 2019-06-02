//
// Created by Gilles Boisson on 2019-05-29.
//

#include "SpriteMaterial.h"
#include "SpriteShader.h"

SpriteMaterial::SpriteMaterial(GLRenderer *renderer,uint16_t nbTexture):GLMaterialA(renderer->getShader("sprite")) {
    init(nbTexture);
}

SpriteMaterial::SpriteMaterial(GLShader* shader,uint16_t nbTexture) : GLMaterialA(shader) {
    init(nbTexture);
}

void SpriteMaterial::init(uint16_t nbTexture){
    _nbTexture = nbTexture;
    _texture = new GLTexture*[nbTexture];
}

SpriteMaterial::~SpriteMaterial(){
    delete[] _texture;
}

void SpriteMaterial::bindCommonUniforms() {

}

void SpriteMaterial::bindModelUniforms(glm::mat4 *worldMat, Camera *camera) {
    for (int i = 0; i < _nbTexture; ++i) {
        _texture[0]->bind();

    }
    ((SpriteShader*)_shader)->updateCameraUniform(camera);
}

GLTexture *SpriteMaterial::getTexture(uint32_t textureIndex) const {
    return _texture[textureIndex];
}

void SpriteMaterial::setTexture(GLTexture *texture,uint32_t textureIndex) {
    _texture[textureIndex] = texture;
}
