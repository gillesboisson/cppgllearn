//
// Created by Gilles Boisson on 2019-05-28.
//

#include "GLTransform2D.h"

GLTransform2D::GLTransform2D() {
    reset();
}

void GLTransform2D::reset(){
    _position   = glm::vec2(0);
    _pivot      = glm::vec2(0);
    _scale      = glm::vec2(1);
    _size       = glm::vec2(0);


    // rotation helpers
    _rotation   = 0;
    _depth      = 0;
    _dirtyMat = true;
    _dirtyRot = false;

    _rs = glm::vec2(1,0);
    _rc = glm::vec2(0,1);

}

const glm::vec2 &GLTransform2D::getPosition() const {
    return _position;
}

void GLTransform2D::setPosition(const glm::vec2 &position) {
    _position = position;
}

const glm::vec2 &GLTransform2D::getScale() const {
    return _scale;
}

void GLTransform2D::setScale(const glm::vec2 &scale) {
    _scale = scale;
}

const glm::vec2 &GLTransform2D::getSize() const {
    return _size;
}

void GLTransform2D::setSize(const glm::vec2 &size) {
    _size = size;
}

const glm::vec2 &GLTransform2D::getPivot() const {
    return _pivot;
}

void GLTransform2D::setPivot(const glm::vec2 &pivot) {
    _pivot = pivot;
}

float GLTransform2D::getRotation() const {
    return _rotation;
}

void GLTransform2D::setRotation(float rotation) {
    if(rotation != _rotation){
        _rotation = rotation;
        _dirtyMat = true;
        _dirtyRot = true;
    }
}

float GLTransform2D::getDepth() const {
    return _depth;
}

void GLTransform2D::setDepth(float depth) {
   _depth = depth;
}


void GLTransform2D::updateRot() {

    _dirtyRot = false;

    _rc.x = cos(_rotation);
    _rs.x = sin(_rotation);
    _rc.y = -_rs.y;
    _rs.y = _rc.x;

}

void GLTransform2D::updateLayout() {

}
void GLTransform2D::updateLocalMat() {
    if(_dirtyRot) updateRot();

    _mat = glm::mat3x2();

    _mat[0][0] = _rc.x * _scale.x;
    _mat[0][1] = _rs.x * _scale.x;
    _mat[1][0] = _rc.y * _scale.y;
    _mat[1][1] = _rs.y * _scale.y;

    updateLayout();

    glm::vec2 pivot = glm::vec2 (
        _size.x != 0 ? _size.x * _pivot.x : _pivot.x,
        _size.y != 0 ? _size.y * _pivot.y : _pivot.y
    );

    _mat[2][0] = _position.x - (pivot.x * _mat[0][0]) + (pivot.y * _mat[1][0]);
    _mat[2][1] = _position.y - (pivot.x * _mat[0][1]) + (pivot.y * _mat[1][1]);

}

void GLTransform2D::updateWorldMat(glm::mat3x2 *wm,const glm::mat3x2 &pm) {
    updateLocalMat();

    wm[0][0][0] = (_mat[0][0] * pm[0][0]) + (_mat[0][1] * pm[1][0]);
    wm[0][0][1] = (_mat[0][0] * pm[0][1]) + (_mat[0][1] * pm[1][1]);
    wm[0][1][0] = (_mat[0][1] * pm[0][0]) + (_mat[1][1] * pm[1][0]);
    wm[0][1][1] = (_mat[1][0] * pm[0][1]) + (_mat[1][1] * pm[1][1]);
    wm[0][2][0] = (_mat[2][0] * pm[0][0]) + (_mat[2][1] * pm[0][1]) + pm[2][0];
    wm[0][2][1] = (_mat[2][0] * pm[0][1]) + (_mat[2][1] * pm[1][1]) + pm[2][1];


}

void GLTransform2D::updateWorldMat(glm::mat3x2 *worldMat) {
    updateWorldMat(worldMat,glm::mat3x2());
}
