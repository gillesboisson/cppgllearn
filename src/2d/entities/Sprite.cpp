//
// Created by Gilles Boisson on 2019-05-29.
//

#include "Sprite.h"


Sprite::Sprite(SubTexture *subTexture):QuadA(new glm::vec2[4]) {
    setSubTexture(subTexture);
}


SubTexture *Sprite::getSubTexture() const {
    return _subTexture;
}


void Sprite::setSubTexture(SubTexture *subTexture) {
    if(_subTexture != subTexture) {
        _subTexture = subTexture;
        _subTexture->updateQuadVertices(this->_uvs,this->_positions);
        this->transform.setSize(glm::vec2(_subTexture->getWidth(),_subTexture->getHeight()));


    }
}


Sprite::~Sprite() {
    delete[] this->_uvs;
}



void Sprite::prepareBatch(void *batch) {
    auto texture = this->_subTexture->getTexture();
    ((SpriteBatch*) batch)->hasSameTextureOrEnd(&texture);
    QuadA::prepareBatch(batch);
}


