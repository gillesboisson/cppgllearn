#include "GLVao.h"
 
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>



GLuint GLVao::getGLId(){
    return _glId;
}



void GLVao::init(GLAttribute *attributes, int nbAttributes){
    _nbAttributes = nbAttributes;
    _attributes = attributes;
    gen();
    activate();
}
void GLVao::init(GLAttribute *attributes, int nbAttributes, GLBuffer *indexBuffer){
    _indexBuffer = indexBuffer;
    init(attributes, nbAttributes);
}

void GLVao::bind(){
    glBindVertexArray(_glId);
}
void GLVao::gen(){
	glGenVertexArrays(1, &_glId);
    
}


void GLVao::activate(){
    GLAttribute *attr = _attributes;
    glBindVertexArray(_glId);
    for(int i=0; i < _nbAttributes ; i++,attr++){
        attr->activate();
        if(attr->hasDivisor()) _hasDivisor = true;
    }
    if(_indexBuffer != nullptr){
        _indexBuffer->bind();
    }
    glBindVertexArray(0);

}
void GLVao::dispose(bool destroyBuffers){
    glDeleteVertexArrays(1, &_glId);



    if(destroyBuffers){
        std::vector<GLBuffer*> buffers;
        for (int i = 0; i < _nbAttributes; ++i) {
            auto attrVbo = _attributes[i].getVbo();

            if(std::find(buffers.begin(), buffers.end(),attrVbo) != buffers.end()) {
                buffers.push_back(attrVbo);
            }
        }

        for(auto & buffer : buffers){
            delete buffer;
        }
    }



    if(destroyBuffers && _indexBuffer != nullptr){
        _indexBuffer->dispose();
    }

    delete[] _attributes;
    _attributes = nullptr;
    _nbAttributes = 0;

}

void GLVao::init(GLAttribute *attributes, int nbAttributes,  GLBuffer *indexBuffer, GLenum indType) {
    init(attributes, nbAttributes, indexBuffer);
    _indType = indType;
}

GLenum GLVao::getIndType() const {
    return _indType;

}
GLVao::~GLVao() {
    dispose();
}

GLBuffer* GLVao::getIndexBuffer() const {
    return _indexBuffer;
}

bool GLVao::hasDivisor() const {
    return _hasDivisor;
}

