//
// Created by Gilles Boisson on 2019-05-05.
//

#include "FBStack.h"




FBStack::FBStack(const uint16_t stackSize) : _stackSize(stackSize) {
    _stack = new FBStackData[stackSize];
    reset();
}


FBStack::~FBStack() {
    delete[] _stack;
}

void FBStack::reset(){
    _current = _stack;
    _stackInd = 0;
}

FBStackData * FBStack::push(
    GLFrameBuffer *fbo,
    GLint x,
    GLint y,
    GLsizei width,
    GLsizei height) {
    auto ind = _stackInd++;
    if(ind < _stackSize){
        _current = _stack + ind;

        *_current = {fbo,x,y,width,height};
        bindCurrent();

    }else{
        printf("FBStack :: Stack limit reached ");
        _current = nullptr;
    }

    return _current;
}

FBStackData *FBStack::replace(GLFrameBuffer *fbo, GLint x, GLint y, GLsizei width, GLsizei height) {
    if(_current != nullptr){
        *_current = {fbo,x,y,width,height};
        bindCurrent();
    }else{
        printf("FBStack :: No current stack");
    }

    return _current;
}

FBStackData *FBStack::pop() {
    if(_stackInd != 0) _stackInd--;

    _current = _stack + _stackInd;
    bindCurrent();
    return _current;
}


void FBStack::bindCurrent() {
    if(_current->fbo == nullptr) {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }else{
        glBindFramebuffer(GL_FRAMEBUFFER,_current->fbo->getGLId());
    }

    glViewport(_current->x,_current->y,_current->width,_current->height);

}

FBStackData *FBStack::push(GLFrameBuffer *fbo) {
    return push(fbo,0,0,fbo->getWidth(),fbo->getHeight());
}

FBStackData *FBStack::replace(GLFrameBuffer *fbo) {
    return replace(fbo,0,0,fbo->getWidth(),fbo->getHeight());
}

FBStackData *FBStack::push(GLint x, GLint y, GLsizei width, GLsizei height) {
    return push(nullptr,x,y,width,height);
}

FBStackData *FBStack::replace(GLint x, GLint y, GLsizei width, GLsizei height) {
    return replace(nullptr,x,y,width,height);
}




