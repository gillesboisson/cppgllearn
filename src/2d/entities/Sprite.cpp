//
// Created by Gilles Boisson on 2019-05-29.
//

#include "Sprite.h"

Sprite::Sprite(SubTexture *subTexture):Quad(new glm::vec2[4]) {
    setSubTexture(subTexture);
}

SubTexture *Sprite::getSubTexture() const {
    return _subTexture;
}

void Sprite::setSubTexture(SubTexture *subTexture) {
    if(_subTexture != subTexture) {
        _subTexture = subTexture;
        _subTexture->updateQuadVertices(_uvs,_positions);
        transform.setSize(glm::vec2(_subTexture->getWidth(),_subTexture->getHeight()));

    }
}

Sprite::~Sprite() {
    delete[] _uvs;
}


void Sprite::prepareBatch(SpriteBatch *batch) {
    batch->hasSameTextureOrEnd(_subTexture->getTexture());
}


