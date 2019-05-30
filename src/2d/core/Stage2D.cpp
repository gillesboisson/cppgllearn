//
// Created by Gilles Boisson on 2019-05-29.
//

#include "Stage2D.h"

Stage2D::Stage2D(GLRenderer *renderer,uint32_t width,uint32_t height) {
    initBase(renderer,width,height);

    _batch = new SpriteBatch(_renderer,_camera);
}

Stage2D::Stage2D(GLRenderer *renderer,SpriteBatch* batch,uint32_t width,uint32_t height) {

    initBase(renderer,width,height);

}


Stage2D::~Stage2D() {

    delete _camera;
    delete _batch;
}

void Stage2D::initBase(GLRenderer *renderer,uint32_t width,uint32_t height){
    _width = width;
    _height = height;
    _renderer = renderer;
    _camera = new Camera2D(0,0,width,height);
}