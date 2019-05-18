//
// Created by Gilles Boisson on 2019-05-18.
//

#include "SimpleLightMaterial.h"

void SimpleLightMaterial::bindGeomUniforms(glm::mat4 worldMat, Camera *camera) {
    _transformU.m = worldMat;
    camera->updateMVP(&_transformU.mvp,&worldMat);
    _transformU.rot = glm::inverse(glm::transpose(_transformU.m));
    _transformUB->uploadSubData(0,sizeof(TransformU),&_transformU);
    _shader->setUniformVec3v(_camPosUI,camera->transform.getPosition());
}

void SimpleLightMaterial::bindMatUniforms() {
    _lightUB->uploadSubData(0,sizeof(PointLightU),_light);
}

SimpleLightMaterial::SimpleLightMaterial(GLShader* shader,GLBuffer *transformUB, GLBuffer *lightUB, PointLightU *light):GLMaterialA(shader) {
    _transformUB = transformUB;
    _lightUB = lightUB;
    _light = light;
    _camPosUI = shader->getUniformLocation("camPosition");
}
