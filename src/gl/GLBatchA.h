//
// Created by Gilles Boisson on 2019-05-01.
//

#ifndef CPP_LEARN_GLBATCH_H
#define CPP_LEARN_GLBATCH_H

#include <iostream>
#include <vector>
#include <glad/glad.h>

#include "./GLVao.h"
#include "./GLBuffer.h"
#include "./GLMaterialA.h"
#include "GLRenderer.h"

template<typename VerticesT>
class GLBatchA {


protected:
    VerticesT *_verticesData;
    uint16_t *_indicesData;

    uint32_t _maxVerticesSize;
    uint32_t _verticesSize;


    uint16_t _maxIndicesSize;
    uint16_t _indicesSize;
//    GLuint _vbo;
//    GLuint _ibo;

    GLBuffer* _vbo;
    GLBuffer* _ibo;

    GLVao* _vao;
    uint16_t _vaoId;


    GLMaterialA *_material;
    GLenum _renderType;
    GLRenderer *_renderer;

    virtual GLVao* createVao() = 0;
    virtual void complete();

    void glDraw();
    void initVao();


public:

    explicit GLBatchA(uint32_t maxSize, uint16_t maxIndicesSize,GLMaterialA *material,GLenum renderType,GLRenderer* renderer);
    ~GLBatchA();

    GLuint getVbo() const;

    GLuint getIbo() const;

    uint16_t pull(
        VerticesT **vertices,
        uint16_t **indices
        );

    uint16_t pull(
        VerticesT **vertices,
        uint16_t **indices,
        uint32_t vertCount,
        uint32_t indCount
    );

    virtual void dispose();


    void end();

    virtual void reset();

    GLMaterialA *getMaterial();
    virtual void draw();


    void begin();


};





template<typename VerticesT>
GLBatchA<VerticesT>::GLBatchA(const uint32_t maxSize, const uint16_t maxIndicesSize,GLMaterialA * material,GLenum renderType,GLRenderer* renderer) {
    _maxVerticesSize = maxSize;
    _maxIndicesSize = maxIndicesSize;
    _material = material;
    _renderType = renderType;
    _renderer = renderer;

    // init buffers;
    _verticesData = new VerticesT[_maxVerticesSize];
    _indicesData = new uint16_t[_maxIndicesSize];

    _vbo = new GLBuffer(GL_ARRAY_BUFFER,GL_DYNAMIC_DRAW,_maxVerticesSize * sizeof(VerticesT));
    _ibo = new GLBuffer(GL_ELEMENT_ARRAY_BUFFER,GL_DYNAMIC_DRAW,_maxIndicesSize * sizeof(uint16_t));

//    _vao = createVao();
//    _vaoId = _vao->getGLId();

}

template<typename VerticesT>
void GLBatchA<VerticesT>::initVao(){
    _vao = createVao();
    _vaoId = _vao->getGLId();
}
template<typename VerticesT>
GLBatchA<VerticesT>::~GLBatchA(){
    dispose();
}


template<typename VerticesT>
uint16_t GLBatchA<VerticesT>::pull(VerticesT **vertices, uint16_t **indices){
    return pull(vertices,indices,1,1);
}

template<typename VerticesT>
uint16_t GLBatchA<VerticesT>::pull(VerticesT **vertices, uint16_t **indices, uint32_t vertCount, uint32_t indCount) {
    uint32_t indV = 0;
    uint16_t indI = 0;

    if (
        _verticesSize + vertCount >= _maxVerticesSize ||
        _indicesSize + indCount >= _maxIndicesSize
        ) {
        end();
    } else {
        indV = _verticesSize;
        indI = _indicesSize;
    }

    _verticesSize += vertCount;
    _indicesSize += indCount;

    *vertices = _verticesData + indV;
    *indices = _indicesData + indI;

    return indV;
}

template<typename VerticesT>
void GLBatchA<VerticesT>::begin() {
    reset();
}

template<typename VerticesT>
void GLBatchA<VerticesT>::end() {

    _vbo->uploadSubData(0,_verticesSize * sizeof(VerticesT),_verticesData);
    _ibo->uploadSubData(0,_indicesSize * sizeof(uint16_t),_indicesData);


    complete();
    draw();
    reset();
}

template<typename VerticesT>
void GLBatchA<VerticesT>::dispose() {

    if(_verticesData != nullptr) {
        delete[] _verticesData;
        _verticesData = nullptr;

    }

    if(_vbo != nullptr) {
        _vbo->dispose();
        delete _vbo;
        _vbo = nullptr;
    }

    if(_ibo != nullptr) {
        _ibo->dispose();
        delete _ibo;
        _ibo = nullptr;
    }

    if(_vao != nullptr) {
        _vao->dispose();
        delete _vao;
        _vao = nullptr;
    }

    if(_verticesData != nullptr) {
        delete[] _indicesData;
        _indicesData = nullptr;
    }

}



template<typename VerticesT>
GLuint GLBatchA<VerticesT>::getVbo() const {
    return _vbo;
}

template<typename VerticesT>
GLuint GLBatchA<VerticesT>::getIbo() const {
    return _ibo;
}

template<typename VerticesT>
void GLBatchA<VerticesT>::reset() {
    _verticesSize = 0;
    _indicesSize = 0;
}

template<typename VerticesT>
void GLBatchA<VerticesT>::complete() {}

template<typename VerticesT>
GLMaterialA *GLBatchA<VerticesT>::getMaterial() {
    return _material;
}

template<typename VerticesT>
void GLBatchA<VerticesT>::draw() {

    _renderer->prepare(_material,_vao);
    glDraw();

}

template<typename VerticesT>
void GLBatchA<VerticesT>::glDraw() {
    if(_vao->getIndexBuffer() != nullptr) {
        glDrawElements(_renderType,_indicesSize, _vao->getIndType(), nullptr);
    }else{
        glDrawArrays(_renderType,0,_indicesSize);
    }
}


#endif //CPP_LEARN_GLBATCH_H
