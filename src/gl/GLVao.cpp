#include "GLVao.h"
 
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

GLAttribute CreateGLAttribute(uint32_t location, GLint size, GLenum type,GLuint vbo,GLsizei stride,GLboolean normalize,const GLvoid * pointer){
    GLAttribute attr;

    attr.location = location;
    attr.size = size;
    attr.type = type;
    attr.normalize = normalize;
    attr.stride = stride;
    attr.location = location;
    attr.vbo = vbo;
    attr.pointer = pointer;

    return attr;
}

void ActivateGLAttribute(GLAttribute* attr){
    glBindBuffer(GL_ARRAY_BUFFER, attr->vbo);
	glEnableVertexAttribArray(attr->location);
	glVertexAttribPointer(attr->location, attr->size, attr->type, attr->normalize, attr->stride, attr->pointer);
}

GLuint GLVao::getVao(){
    return _vao;
}

GLuint GLVao::getIndVbo(){
    return _indVbo;
}

void GLVao::init(GLAttribute *attributes, int nbAttributes){
    _nbAttributes = nbAttributes;
    _attributes = attributes;
    gen();
    activate();
}
void GLVao::init(GLAttribute *attributes, int nbAttributes, GLuint indVbo){
    _indVbo = indVbo;
    init(attributes, nbAttributes);
}

void GLVao::bind(){
    glBindVertexArray(_vao);
}
void GLVao::gen(){
	glGenVertexArrays(1, &_vao);
    
}


void GLVao::activate(){
    GLAttribute *attr = _attributes;
    bind();
    for(int i=0; i < _nbAttributes ; i++){
        std::cout << "attr " << i;
        ActivateGLAttribute(attr++);
    }
    if(_indVbo != 0){
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,_indVbo);
    }
}
void GLVao::dispose(){
    glDeleteVertexArrays(1, &_vao);
}

void GLVao::init(GLAttribute *attributes, int nbAttributes, GLuint indVbo, GLenum indType) {
    init(attributes, nbAttributes, indVbo);
    _indType = indType;
}

GLenum GLVao::GetIndType() const {
    return _indType;
}
