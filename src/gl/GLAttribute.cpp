//
// Created by Gilles Boisson on 2019-05-05.
//

#include "GLAttribute.h"

GLAttribute::GLAttribute() = default;

GLAttribute::GLAttribute(uint32_t location, GLint size, GLenum type, GLBuffer* vbo, GLsizei stride, GLboolean normalize,
                         const void* pointer) {
    set(location,size,type,vbo,stride,normalize,pointer);
}

void GLAttribute::deleteVbo(){
    if(_vbo != nullptr) {
        delete _vbo;
        _vbo = nullptr;
    }
}

uint32_t GLAttribute::getLocation() const {
    return _location;
}

GLint GLAttribute::getSize() const {
    return _size;
}

GLenum GLAttribute::getType() const {
    return _type;
}

GLboolean GLAttribute::getNormalize() const {
    return _normalize;
}

GLsizei GLAttribute::getStride() const {
    return _stride;
}

GLBuffer* GLAttribute::getVbo() const {
    return _vbo;
}

const void *GLAttribute::getPointer() const {
    return _pointer;
}

void GLAttribute::set(
    uint32_t location,
    GLint size,
    GLenum type,
    GLBuffer* vbo,
    GLsizei stride,
    GLboolean normalize,
    const void* pointer) {
    _location = location;
    _size = size;
    _type = type;
    _vbo = vbo;
    _stride = stride;
    _normalize = normalize;
    _pointer = pointer;
}
