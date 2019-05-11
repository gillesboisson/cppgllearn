//
// Created by Gilles Boisson on 2019-04-27.
//

#include "GLMesh.h"

GLMesh::GLMesh() {

}

GLMesh::GLMesh(uint32_t nbIndices,GLVao vao) {
    _vao = vao;
    _nbIndices = nbIndices;
}

GLMesh::GLMesh(uint32_t nbPoints,GLVao vao, GLenum renderType): GLMesh(nbPoints,vao) {
    _renderType = renderType;
}

GLenum GLMesh::getRenderType() {
    return _renderType;
}

const GLVao &GLMesh::getVao() const {
    return _vao;
}

uint32_t GLMesh::getNbPoints() const {
    return _nbIndices;
}

void GLMesh::draw() {
    _vao.bind();
    draw(_nbIndices);
}

void GLMesh::draw(uint32_t nbIndices) {
    if(_vao.getIndexBufferGlId() != 0) {
        glDrawElements(_renderType, nbIndices, _vao.getIndType(), nullptr);
    }else{
        glDrawArrays(_renderType,0,nbIndices);
    }
}
