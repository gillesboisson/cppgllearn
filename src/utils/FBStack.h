//
// Created by Gilles Boisson on 2019-05-05.
//

#ifndef CPP_LEARN_FBSTACK_H
#define CPP_LEARN_FBSTACK_H

#include "../gl/GLFrameBuffer.h"

struct FBStackData {
    GLFrameBuffer* fbo;
    GLint x;
    GLint y;
    GLsizei width;
    GLsizei height;
};

class FBStack {
    FBStackData* _stack;
    FBStackData* _current;
    uint16_t _stackInd;
    const uint16_t _stackSize;




    void bindCurrent();

public:

    FBStack(uint16_t stackSize);
    ~FBStack();

    FBStackData *push(GLFrameBuffer *fbo, GLint x, GLint y, GLsizei width, GLsizei height);
    FBStackData *replace(GLFrameBuffer *fbo, GLint x, GLint y, GLsizei width, GLsizei height);
    FBStackData *pop();


    FBStackData *push(GLFrameBuffer *fbo);
    FBStackData *replace(GLFrameBuffer*fbo);

    FBStackData *push(GLint x, GLint y, GLsizei width, GLsizei height);
    FBStackData *replace(GLint x, GLint y, GLsizei width, GLsizei height);



    void reset();



};


#endif //CPP_LEARN_FBSTACK_H
