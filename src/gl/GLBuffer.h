//
// Created by Gilles Boisson on 2019-05-11.
//

#ifndef CPP_LEARN_GLBUFFER_H
#define CPP_LEARN_GLBUFFER_H

#include <glad/glad.h>

class GLBuffer {

    GLuint _glId{};
    GLenum _target{};
    GLenum _usage{};
    GLvoid *_data{};
    GLsizeiptr _dataSize{};

public:

    GLBuffer();
    ~GLBuffer();

    GLBuffer(GLenum target,GLenum usage);
    GLBuffer(GLenum target,GLenum usage,GLvoid *data,GLsizeiptr size);
    GLBuffer(GLenum target, GLenum usage,GLsizeiptr size);

    void gen();
    void init(GLenum target,GLenum usage);
    void init(GLenum target,GLenum usage,GLvoid *data,GLsizeiptr size);

    void bind() const;
    void bindBase(GLenum target,GLuint index) const;
    void bindBase(GLuint index) const;
    void bindRange(GLuint index,GLintptr offset,GLsizeiptr size) const;

    void uploadData(GLsizeiptr size,GLvoid* data,GLenum usage) const;
    void uploadData(GLsizeiptr size,GLvoid* data) const ;

    void allocate(GLsizeiptr size,GLenum usage);
    void allocate(GLsizeiptr size);
    void uploadData() const;

    void uploadSubData(GLintptr offset,GLsizeiptr size,GLvoid* data) const;
    void uploadSubData(GLintptr offset,GLsizeiptr size) const;
    void uploadSubData(GLintptr offset) const;

    void dispose();

    GLuint getGlId() const;

    GLenum getTarget() const;

    GLenum getUsage() const;

    const void *getData() const;

    GLsizeiptr getDataSize() const;

    void init(GLenum target, GLenum usage, GLsizeiptr size);
};


#endif //CPP_LEARN_GLBUFFER_H
