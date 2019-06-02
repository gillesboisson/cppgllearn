//
// Created by Gilles Boisson on 2019-06-02.
//

#ifndef CPP_LEARN_SPRITEBATCHA_H
#define CPP_LEARN_SPRITEBATCHA_H

#include "glm/glm.hpp"
#include "../../core/BatchA.h"
#include "../materials/SpriteMaterial.h"


struct SpriteVertex{
    glm::vec3 pos;
    glm::vec2 uv;
    glm::vec4 color;
} typedef SpriteVertex;

template<typename SpriteVertexT>
class SpriteBatchA : public BatchA<SpriteVertexT>{
protected:
//    GLVao* createVao() override;
    GLTexture **_currentTextures;
    uint16_t _nbTexture;



public:
    SpriteBatchA(GLRenderer* renderer,
    Camera *camera,
        GLMaterialA* material,
        uint16_t nbTexture,
        uint32_t maxSize = 24000,
        uint16_t maxIndicesSize = 24000
    );

    ~SpriteBatchA();

    void hasSameTextureOrEnd(GLTexture ** textures);

    void reset();
};


template<typename SpriteVertexT>
SpriteBatchA<SpriteVertexT>::SpriteBatchA(GLRenderer* renderer,
                                          Camera *camera,
                                          GLMaterialA* material,
                                          uint16_t nbTexture,
                                          uint32_t maxSize,
                                          uint16_t maxIndicesSize) : BatchA<SpriteVertexT>(
    maxSize,
    maxIndicesSize,
    material,
    GL_TRIANGLES,
    renderer,
    camera
){
    _nbTexture = nbTexture;

    _currentTextures = new GLTexture*[nbTexture];

}

template<typename SpriteVertexT>
void SpriteBatchA<SpriteVertexT>::reset(){
    BatchA<SpriteVertexT>::reset();
    for (int i = 0; i < _nbTexture; ++i) {
        _currentTextures[i] = nullptr;
    }

}

template<typename SpriteVertexT>
SpriteBatchA<SpriteVertexT>::~SpriteBatchA(){
    delete[] _currentTextures;
}

template<typename SpriteVertexT>
void SpriteBatchA<SpriteVertexT>::hasSameTextureOrEnd(GLTexture **textures) {

    GLTexture *currentTexture;
    GLTexture *texture;

    bool textureSwapped = false;

    for (int i = 0; i < _nbTexture; ++i) {
        currentTexture = _currentTextures[i];
        texture = textures[i];

        if (texture != currentTexture) {
            if (currentTexture != nullptr && BatchA<SpriteVertexT>::_verticesSize > 0) textureSwapped = true;
            _currentTextures[i] = texture;

            if (texture != nullptr) {
                ((SpriteMaterial *) BatchA<SpriteVertexT>::_material)->setTexture(texture,i);
            }
        }


    }
}

#endif //CPP_LEARN_SPRITEBATCHA_H
