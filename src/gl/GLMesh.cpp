//
// Created by Gilles Boisson on 2019-04-27.
//

#include "GLMesh.h"

GLMesh::GLMesh() {

}

GLMesh::GLMesh(uint32_t nbPoints,const GLVao vao) {
    _vao = vao;
    _nbPoints = nbPoints;
}

GLMesh::GLMesh(uint32_t nbPoints,const GLVao vao, GLenum renderType): GLMesh(nbPoints,vao) {
    _renderType = renderType;
}

GLenum GLMesh::getRenderType() {
    return _renderType;
}

const GLVao &GLMesh::getVao() const {
    return _vao;
}

uint32_t GLMesh::getNbPoints() const {
    return _nbPoints;
}

void GLMesh::draw() {
    _vao.bind();
    draw(_nbPoints);
}

void GLMesh::draw(uint32_t nbPoints) {
    if(_vao.getIndexVboGLId() != 0) {
        glDrawElements(_renderType, nbPoints, _vao.getIndType(), nullptr);
    }else{
        glDrawArrays(_renderType,0,nbPoints);
    }
}
