//
// Created by Gilles Boisson on 2019-05-28.
//

#include "GLTransform2D.h"

#include <glm/gtx/matrix_transform_2d.hpp>

GLTransform2D::GLTransform2D() {
    reset();
    _fastTransform = false;

}

void GLTransform2D::reset(){
    _position   = glm::vec2(0);
    _pivot      = glm::vec2(0);
    _scale      = glm::vec2(1);
    _size       = glm::vec2(0);


    // rotation helpers
    _rotation   = 0;
    _depth      = 0.5;
    _dirtyRot = true;
    _dirtyMat = true;


    _rs = glm::vec2(1,0);
    _rc = glm::vec2(0,1);

}



const glm::vec2 &GLTransform2D::getPosition() const {
    return _position;
}


void GLTransform2D::setPosition(float x,float y) {
    _position.x = x;
    _position.y = y;
    _dirtyMat = true;
}

void GLTransform2D::setPosition(const glm::vec2 &position) {
    _dirtyMat = true;
    _position = position;
}

const glm::vec2 &GLTransform2D::getScale() const {
    return _scale;
}

void GLTransform2D::setScale(const glm::vec2 &scale) {
    _dirtyMat = true;
    _scale = scale;
}

void GLTransform2D::setScale(float x,float y) {
    _scale.x = x;
    _scale.y = y;
    _dirtyMat = true;
}

void GLTransform2D::setScale(float scale) {
    _scale.x = scale;
    _scale.y = scale;
    _dirtyMat = true;
}

const glm::vec2 &GLTransform2D::getSize() const {
    return _size;
}

void GLTransform2D::setSize(const glm::vec2 &size) {
    _dirtyMat = true;
    _size = size;
}

void GLTransform2D::setSize(float x, float y) {
    _size.x = x;
    _size.y = y;
    _dirtyMat = true;
}

const glm::vec2 &GLTransform2D::getPivot() const {
    return _pivot;
}

void GLTransform2D::setPivot(const glm::vec2 &pivot) {
    _pivot = pivot;
}

void GLTransform2D::setPivot(float x,float y) {
    _pivot.x = x;
    _pivot.y = y;
    _dirtyMat = true;
}

float GLTransform2D::getRotation() const {
    return _rotation;
}

void GLTransform2D::setRotation(float rotation) {
    if(rotation != _rotation){
        _rotation = rotation;
        _dirtyRot = true;
        _dirtyMat = true;
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
    _rc.y = -_rs.x;
    _rs.y = _rc.x;



}

void GLTransform2D::updateLayout() {

}
void GLTransform2D::updateLocalMat() {

    if(_dirtyMat) {
        _dirtyMat = false;
        _mat = glm::mat3(1);
        if(!_fastTransform) {
            if (_dirtyRot) updateRot();

            glm::vec2 pivot = glm::vec2(
                _size.x != 0 ? _size.x * _pivot.x : _pivot.x,
                _size.y != 0 ? _size.y * _pivot.y : _pivot.y
            );

            _mat = glm::translate(_mat, (pivot * _scale) + _position);
            _mat = glm::rotate(_mat, _rotation);

            _mat = glm::scale(_mat, _scale);

            _mat = glm::translate(_mat, -pivot);

        }else{
            _mat[2][0] = _position.x;
            _mat[2][1] = _position.y;
        }
    }

}

void GLTransform2D::updateWorldMat(glm::mat3 *wm, const glm::mat3 &pm) {
    updateLocalMat();
    if(!_fastTransform) {
        *wm = pm * _mat;
    }else{
        (*wm)[2][0] = pm[2][0] + _mat[2][0];
        (*wm)[2][1] = pm[2][1] + _mat[2][1];
    }

}

void GLTransform2D::updateWorldMat(glm::mat3 *worldMat) {
    updateWorldMat(worldMat,glm::mat3(1));
}

bool GLTransform2D::isFastTransform() const {
    return _fastTransform;
}

void GLTransform2D::setFastTransform(bool fastTransform) {
    _fastTransform = fastTransform;
}
