//
// Created by Gilles Boisson on 2019-05-29.
//

#include "SpriteMaterial.h"
#include "SpriteShader.h"

SpriteMaterial::SpriteMaterial(GLRenderer *renderer):GLMaterialA(renderer->getShader("sprite")) {

}

SpriteMaterial::SpriteMaterial(GLShader *shader) : GLMaterialA(shader) {

}

void SpriteMaterial::bindCommonUniforms() {

}

void SpriteMaterial::bindModelUniforms(glm::mat4 *worldMat, Camera *camera) {
    _texture->bind();
    ((SpriteShader*)_shader)->updateCameraUniform(camera);
}

GLTexture *SpriteMaterial::getTexture() const {
    return _texture;
}

void SpriteMaterial::setTexture(GLTexture *texture) {
    _texture = texture;
}
