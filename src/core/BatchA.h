//
// Created by Gilles Boisson on 2019-05-30.
//

#ifndef CPP_LEARN_BATCH_H
#define CPP_LEARN_BATCH_H


#include "../gl/GLBatchA.h"

template<typename VerticesT>
class BatchA :public GLBatchA<VerticesT>{
protected:

    Camera *_camera;

public:
    BatchA(
        uint32_t maxSize,
        uint16_t maxIndicesSize,
        GLMaterialA *material,
        GLenum renderType,
        GLRenderer* renderer,
        Camera *camera
        );
    virtual void draw();
};


template<typename VerticesT>
BatchA<VerticesT>::BatchA(
    uint32_t maxSize,
    uint16_t maxIndicesSize,
    GLMaterialA *material,
    GLenum renderType,
    GLRenderer* renderer,
    Camera *camera
    ): GLBatchA<VerticesT>(maxSize,maxIndicesSize,material,renderType,renderer){
        _camera = camera;

    }


template<typename VerticesT>
void BatchA<VerticesT>::draw(){
    BatchA<VerticesT>::_renderer->prepare(BatchA<VerticesT>::_material,BatchA<VerticesT>::_vao,_camera);
    BatchA<VerticesT>::glDraw();
};

#endif //CPP_LEARN_BATCH_H
