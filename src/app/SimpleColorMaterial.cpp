//
// Created by Gilles Boisson on 2019-05-19.
//

#include "SimpleColorMaterial.h"

SimpleColorMaterial::SimpleColorMaterial(GLRenderer *renderer):GLMaterialA(renderer->getShader("fixColor")) {
    _colorU = _shader->getUniformLocation("color");
}

void SimpleColorMaterial::bindGeomUniforms(glm::mat4 worldMat, Camera *camera) {

}

void SimpleColorMaterial::bindMatUniforms() {
    _shader->setUniformVec4v(_colorU,_color);
}

const glm::vec4 &SimpleColorMaterial::getColor() const {
    return _color;
}

void SimpleColorMaterial::setColor(const glm::vec4 &color) {
    _color = color;
}


