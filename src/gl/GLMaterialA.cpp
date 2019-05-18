//
// Created by Gilles Boisson on 2019-05-18.
//

#include "GLMaterialA.h"

void GLMaterialA::render(GLMesh *mesh, GLTransform *transform, Camera *camera) {
    render(mesh,transform->getLocalMat(),camera);
}


GLShader *GLMaterialA::getActiveShader() const {
    return _shader;
}

void GLMaterialA::render(GLMesh *mesh,glm::mat4 mat, Camera *camera){
    bindGeomUniforms(mat, camera);
    mesh->draw();


}

GLMaterialA::GLMaterialA(GLShader *shader) {
    _shader = shader;
}
