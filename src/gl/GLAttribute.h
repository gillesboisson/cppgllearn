//
// Created by Gilles Boisson on 2019-05-05.
//

#ifndef CPP_LEARN_GLATTRIBUTE_H
#define CPP_LEARN_GLATTRIBUTE_H

#include <glad/glad.h>
#include "GLBuffer.h"


class GLAttribute {
public:

    uint32_t _location;

    uint32_t getLocation() const;

    GLint getSize() const;

    GLenum getType() const;

    GLboolean getNormalize() const;

    GLsizei getStride() const;

    GLBuffer* getVbo() const;

    const void *getPointer() const;

    GLint _size;
    GLenum _type;
    GLboolean _normalize;
    GLsizei _stride;
    GLBuffer* _vbo;
    const void* _pointer;

    GLAttribute();
    GLAttribute(uint32_t location, GLint size, GLenum type,GLBuffer* vbo,GLsizei stride,GLboolean normalize,const void* pointer);
    void set(uint32_t location, GLint size, GLenum type,GLBuffer* vbo,GLsizei stride,GLboolean normalize,const void* pointer);

    void deleteVbo();
};


#endif //CPP_LEARN_GLATTRIBUTE_H
