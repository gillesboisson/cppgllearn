//
// Created by Gilles Boisson on 2019-05-01.
//

#ifndef CPP_LEARN_GLBATCH_H
#define CPP_LEARN_GLBATCH_H

#include <iostream>
#include <vector>
#include <glad/glad.h>

#include "./GLVao.h"

template<typename VerticesT>
class GLBatchA {


protected:
    VerticesT *_verticesData;
    uint16_t *_indicesData;

    uint32_t _maxVerticesSize;
    uint32_t _verticesSize;


    uint16_t _maxIndicesSize;
    uint16_t _indicesSize;
    GLuint _vbo;

    GLuint _ibo;
    GLVao* _vao;
    uint16_t _vaoId;




    virtual GLVao* createVao() = 0;
    virtual void complete() = 0;


public:

    explicit GLBatchA(uint32_t maxSize, uint16_t maxIndicesSize);
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

    void init();

    virtual void dispose();


    void end();
    void reset();



};

template<typename VerticesT>
void GLBatchA<VerticesT>::init() {

    if (_verticesData != nullptr) dispose();



    glGenBuffers(1, &_vbo);
    glGenBuffers(1, &_ibo);
    _vao = createVao();
    _vaoId = _vao->getGLId();

    _verticesData = new VerticesT[_maxVerticesSize];
    _indicesData = new uint16_t[_maxIndicesSize];
}




template<typename VerticesT>
GLBatchA<VerticesT>::GLBatchA(const uint32_t maxSize, const uint16_t maxIndicesSize) {
    _maxVerticesSize = maxSize;
    _maxIndicesSize = maxIndicesSize;
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
void GLBatchA<VerticesT>::end() {

    glBindVertexArray(_vaoId);
    auto sV = sizeof(VerticesT) * _verticesSize;
    auto sI = sizeof(uint16_t) * _indicesSize;

    auto v1 = _indicesData[0];
    auto v2 = _indicesData[1];
    auto v3 = _indicesData[2];

    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, sV, _verticesData, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vao->getIndexBufferGlId());
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sI, _indicesData, GL_DYNAMIC_DRAW);

    complete();
    reset();
}

template<typename VerticesT>
void GLBatchA<VerticesT>::dispose() {

    if(_verticesData != nullptr) {
        delete[] _verticesData;
        _verticesData = nullptr;

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


#endif //CPP_LEARN_GLBATCH_H
