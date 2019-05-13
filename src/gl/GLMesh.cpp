//
// Created by Gilles Boisson on 2019-04-27.
//

#include "GLMesh.h"



GLMesh::GLMesh(uint32_t nbIndices, GLenum renderType){
    _nbIndices = nbIndices;
    _renderType = renderType;
    _vao = new GLVao();

}

GLMesh::GLMesh(uint32_t nbIndices,GLVao* vao, GLenum renderType) {
    _nbIndices = nbIndices;
    _renderType = renderType;
    _vao = vao;
}

GLenum GLMesh::getRenderType() {
    return _renderType;
}


uint32_t GLMesh::getNbPoints() const {
    return _nbIndices;
}

void GLMesh::draw() {
    _vao->bind();
    draw(_nbIndices);
}

void GLMesh::draw(uint32_t nbIndices) {
    if(_vao->getIndexBuffer() != nullptr) {
        glDrawElements(_renderType, nbIndices, _vao->getIndType(), nullptr);
    }else{
        glDrawArrays(_renderType,0,nbIndices);
    }
}

void GLMesh::drawInstances(uint32_t nbInstances) {
    _vao->bind();
    if(_vao->getIndexBuffer() != nullptr) {
        glDrawElementsInstanced(_renderType, _nbIndices, _vao->getIndType(), nullptr,nbInstances);
    }else{
        glDrawArraysInstanced(_renderType,0,_nbIndices,nbInstances);
    }
}


GLMesh::~GLMesh() {
    dispose();
}

void GLMesh::dispose(bool disposeVao) {
    if(_vao != nullptr){
        delete _vao;
        _vao = nullptr;
    }
}

GLVao *GLMesh::getVao() const {
    return _vao;
}



