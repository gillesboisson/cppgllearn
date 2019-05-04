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
    printf("Activate vao attr %d \n",attr->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, attr->vbo);
	glEnableVertexAttribArray(attr->location);
	glVertexAttribPointer(attr->location, attr->size, attr->type, attr->normalize, attr->stride, attr->pointer);
}

GLuint GLVao::getGLId(){
    return _vao;
}

GLuint GLVao::getIndexVboGLId(){
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
    glBindVertexArray(_vao);
    printf("Activate vao %d \n",_vao);
    for(int i=0; i < _nbAttributes ; i++){

        ActivateGLAttribute(attr++);
    }
    if(_indVbo != 0){
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,_indVbo);
    }
    glBindVertexArray(0);

}
void GLVao::dispose(bool destroyBuffers){
    glDeleteVertexArrays(1, &_vao);
    if(destroyBuffers){
        for (int i = 0; i < _nbAttributes; ++i) {
            glDeleteBuffers(1,&_attributes[i].vbo);
        }
    }
    if(destroyBuffers && _indVbo != 0){
        glDeleteBuffers(1,&_indVbo);
    }

    delete[] _attributes;
    _attributes = nullptr;
    _nbAttributes = 0;

}

void GLVao::init(GLAttribute *attributes, int nbAttributes, GLuint indVbo, GLenum indType) {

    init(attributes, nbAttributes, indVbo);
    _indType = indType;
}

GLenum GLVao::getIndType() const {
    return _indType;

}
