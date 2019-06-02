#include "SpriteBatch.h"



SpriteBatch::SpriteBatch(GLRenderer* renderer,Camera *camera,uint32_t maxSize, uint16_t maxIndicesSize)
    : SpriteBatchA(renderer,camera,new SpriteMaterial(renderer,1),1,maxSize,maxIndicesSize) {
    initVao();
}


GLVao *SpriteBatch::createVao() {
    auto vao = new GLVao();

    auto attributes = new GLAttribute[3];
    attributes[0].set(Position,3,GL_FLOAT,_vbo,sizeof(SpriteVertex),GL_FALSE,(GLvoid*) 0);
    attributes[1].set(Uv,2,GL_FLOAT,_vbo,sizeof(SpriteVertex),GL_FALSE,(GLvoid*) (sizeof(float) * 3));
    attributes[2].set(Color,4,GL_FLOAT,_vbo,sizeof(SpriteVertex),GL_FALSE,(GLvoid*) (sizeof(float) * 5));

    vao->init(attributes,3,_ibo);
    return vao;
}