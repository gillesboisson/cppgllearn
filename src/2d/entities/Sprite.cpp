//
// Created by Gilles Boisson on 2019-05-29.
//

#include "Sprite.h"

Sprite::Sprite(SubTexture *texture):Quad(new glm::vec2[4]) {

}

SubTexture *Sprite::getSubTexture() const {
    return _subTexture;
}

void Sprite::setSubTexture(SubTexture *subTexture) {
    if(_subTexture != subTexture) {
        _subTexture = subTexture;
        _subTexture->copyUvs(_uvs);
        _transform.setSize(glm::vec2(_subTexture->getWidth(),_subTexture->getHeight()));
    }
}

Sprite::~Sprite() {
    delete[] _uvs;
}


