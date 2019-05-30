//
// Created by Gilles Boisson on 2019-05-28.
//

#ifndef CPP_LEARN_SPRITEBATCH_H
#define CPP_LEARN_SPRITEBATCH_H

#include "../../core/BatchA.h"
#include "glm/glm.hpp"

struct SpriteVertex{
    glm::vec3 pos;
    glm::vec2 uv;
    glm::vec4 color;
} typedef SpriteVertex;



//using SpriteBatch = GLBatchA<SpriteVertex>;

class SpriteBatch : public BatchA<SpriteVertex>{
protected:
    GLVao* createVao() override;
    GLTexture *_currentTexture;



public:
    SpriteBatch(GLRenderer* renderer,
        Camera *camera,
        uint32_t maxSize = 24000,
        uint16_t maxIndicesSize = 24000
            );

    virtual void reset() override;

    void hasSameTextureOrEnd(GLTexture *texture);
};


#endif //CPP_LEARN_SPRITEBATCH_H
