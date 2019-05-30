//
// Created by Gilles Boisson on 2019-05-29.
//

#ifndef CPP_LEARN_STAGE2D_H
#define CPP_LEARN_STAGE2D_H

#include "EntityGroup2D.h"
#include "Camera2D.h"

class Stage2D :public EntityGroup2D {
protected:
    Stage2D(GLRenderer *renderer, SpriteBatch *batch, uint32_t width, uint32_t height);

    SpriteBatch *_batch;
    uint32_t _width;
    uint32_t _height;
    GLRenderer *_renderer;
    Camera2D *_camera;

    void initBase(GLRenderer *renderer, uint32_t width, uint32_t height);


public:
    Stage2D(GLRenderer *renderer,uint32_t width,uint32_t height);
    ~Stage2D();

};


#endif //CPP_LEARN_STAGE2D_H
