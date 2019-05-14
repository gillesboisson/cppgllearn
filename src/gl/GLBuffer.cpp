//
// Created by Gilles Boisson on 2019-05-11.
//

#include <cstdio>
#include "GLBuffer.h"

void GLBuffer::gen() {
    glGenBuffers(1,&_glId);
    printf("gen buffer id %d %04X %04X \n",_glId,_target,_usage);
}

void GLBuffer::init(GLenum target, GLenum usage) {
    printf("init buffer %d \n",_glId);

    _target = target;
    _usage = usage;
    if(_glId == 0) gen();
}

void GLBuffer::init(GLenum target, GLenum usage, GLsizeiptr size) {
    init(target,usage);
    allocate(size);
}


void GLBuffer::init(GLenum target, GLenum usage, GLvoid* data, GLsizeiptr size) {
    init(target,usage);
    _data = data;
    _dataSize = size;
    uploadData(size,data,usage);
}

void GLBuffer::uploadData(GLsizeiptr size, GLvoid *data, GLenum usage)  const{
    printf("buffer uploadData %s %i, \n",data,usage);
    glBindBuffer(_target, _glId);
    glBufferData(_target, size, data, usage);
    glBindBuffer(_target, 0);
}

void GLBuffer::uploadData(GLsizeiptr size, GLvoid *data)  const{
    uploadData(size, data,_usage);
}

void GLBuffer::allocate(GLsizeiptr size, GLenum usage) {
    _dataSize = size;
    uploadData(size, nullptr,usage);
}

void GLBuffer::allocate(GLsizeiptr size) {
    _dataSize = size;
    uploadData(size, nullptr,_usage);
}

void GLBuffer::uploadSubData(GLintptr offset, GLsizeiptr size, GLvoid *data)  const{
    glBindBuffer(_target, _glId);
    glBufferSubData(_target,offset,size,data);
}

void GLBuffer::uploadSubData(GLintptr offset, GLsizeiptr size)  const{
    uploadSubData(offset,size,_data);
}

void GLBuffer::uploadSubData(GLintptr offset)  const{
    uploadSubData(offset,_dataSize,_data);
}

void GLBuffer::dispose() {
    glDeleteBuffers(1,&_glId);
    _target = 0;
    _usage = 0;
    _data = nullptr;
    _dataSize = 0;
}

GLuint GLBuffer::getGlId() const {
    return _glId;
}

GLenum GLBuffer::getTarget() const {
    return _target;
}

GLenum GLBuffer::getUsage() const {
    return _usage;
}

const void *GLBuffer::getData() const {
    return _data;
}

GLsizeiptr GLBuffer::getDataSize() const {
    return _dataSize;
}

void GLBuffer::bind() const {
    glBindBuffer(_target,_glId);
}

GLBuffer::GLBuffer(){};

GLBuffer::GLBuffer(GLenum target, GLenum usage):GLBuffer() {

    init(target,usage);
}

GLBuffer::GLBuffer(GLenum target, GLenum usage,GLsizeiptr size):GLBuffer(){
    init(target,usage,size);
}

GLBuffer::GLBuffer(GLenum target, GLenum usage, GLvoid *data, GLsizeiptr size):GLBuffer(){
    init(target,usage,data,size);
}

void GLBuffer::uploadData() const {
    // assuming memory is already allocated, upload sub data is used for faster upload
    glBindBuffer(_target, _glId);
    glBufferSubData(_target,0,_dataSize,_data);
}

GLBuffer::~GLBuffer() {
    dispose();
}

void GLBuffer::bindBase(GLenum target,GLuint index) const {
    glBindBufferBase(target,index,_glId);
}

void GLBuffer::bindBase(GLuint index) const {
    glBindBufferBase(_target,index,_glId);
}

void GLBuffer::bindRange(GLuint index, GLintptr offset, GLsizeiptr size) const {
    glBindBufferRange(_target,index,_glId,offset,size);

}
