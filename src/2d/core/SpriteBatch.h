//
// Created by Gilles Boisson on 2019-05-28.
//

#ifndef CPP_LEARN_SPRITEBATCH_H
#define CPP_LEARN_SPRITEBATCH_H

#include "SpriteBatchA.h"
#include "../materials/SpriteMaterial.h"





//using SpriteBatch = GLBatchA<SpriteVertex>;

class SpriteBatch : public SpriteBatchA<SpriteVertex>{
protected:
    GLVao* createVao() override;




public:
    SpriteBatch(GLRenderer* renderer,
    Camera *camera,
        uint32_t maxSize = 24000,
        uint16_t maxIndicesSize = 24000
    );

};




//void SpriteBatch::hasSameTextureOrEnd(GLTexture *texture){
//    if(texture != _currentTexture){
//        if(_currentTexture != nullptr && _verticesSize > 0) end();
//        _currentTexture = texture;
//        if(texture != nullptr) {
//            ((SpriteMaterial*)_material)->setTexture(texture);
//        }
//    }
//}

#endif //CPP_LEARN_SPRITEBATCH_H
