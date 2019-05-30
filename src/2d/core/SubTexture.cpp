//
// Created by Gilles Boisson on 2019-05-29.
//

#include "SubTexture.h"

SubTexture::SubTexture(GLTexture* texture,uint32_t x,uint32_t y,uint32_t width,uint32_t height) {
    _texture = texture;
    _left = x;
    _top = y;
    _right = width + x;
    _bottom = height + y;
    _width = width;
    _height = height;
}



void SubTexture::copyUvs(float *uvs) {
    uvs[0] = uvs[4] = (float)_left / _texture->getWidth();
    uvs[1] = uvs[3] = (float)_top / _texture->getHeight();
    uvs[5] = uvs[7] = (float)_right / _texture->getWidth();
    uvs[4] = uvs[6] = (float)_bottom / _texture->getHeight();
}

void SubTexture::copyUvs(glm::vec2 *uvs) {
    uvs[0][0] = uvs[2][0] = (float)_left / _texture->getWidth();
    uvs[0][1] = uvs[1][1] = (float)_top / _texture->getHeight();
    uvs[1][0] = uvs[3][0] = (float)_right / _texture->getWidth();
    uvs[2][1] = uvs[3][1] = (float)_bottom / _texture->getHeight();
}

void SubTexture::updateQuadVertices(glm::vec2 *uvs,glm::vec2 *points) {

//    points[0][0] = points[2][0] = 0;
//    points[0][1] = points[1][1] = 0;

    uvs[0][0] = uvs[2][0] = (float)_left / _texture->getWidth();
    uvs[0][1] = uvs[1][1] = (float)_top / _texture->getHeight();
    uvs[1][0] = uvs[3][0] = (float)_right / _texture->getWidth();
    uvs[2][1] = uvs[3][1] = (float)_bottom / _texture->getHeight();

    points[1][0] = points[3][0] = _width;
    points[2][1] = points[3][1] =_height;
}

uint32_t SubTexture::getLeft() const {
    return _left;
}

void SubTexture::setLeft(uint32_t left) {
    _left = left;
}

uint32_t SubTexture::getTop() const {
    return _top;
}

void SubTexture::setTop(uint32_t top) {
    _top = top;
}

uint32_t SubTexture::getRight() const {
    return _right;
}

void SubTexture::setRight(uint32_t right) {
    _right = right;
}

uint32_t SubTexture::getBottom() const {
    return _bottom;
}

void SubTexture::setBottom(uint32_t bottom) {
    _bottom = bottom;
}

GLTexture *SubTexture::getTexture() const {
    return _texture;
}

void SubTexture::setTexture(GLTexture *texture) {
    _texture = texture;
}

uint32_t SubTexture::getWidth() const {
    return _width;
}

uint32_t SubTexture::getHeight() const {
    return _height;
}
