//
// Created by Gilles Boisson on 2019-04-26.
//

#include "GLTransform.h"

glm::vec3 GLTransform::getScale() const {
    return _scale;
}

glm::vec3 GLTransform::getPosition() const{
    return _position;
}

void GLTransform::scale(float s) {
    _scale.x = _scale.y = _scale.z = s;
    _dirtyMat = true;
}

void GLTransform::scale(float x, float y, float z) {
    _scale.x = x;
    _scale.y = y;
    _scale.z = z;
    _dirtyMat = true;
}

void GLTransform::position(float x, float y, float z) {
    _position.x = x;
    _position.y = y;
    _position.z = z;
    _dirtyMat = true;
}

void GLTransform::translate(float x, float y, float z) {
    _position.x += x;
    _position.y += y;
    _position.z += z;
    _dirtyMat = true;
}

void GLTransform::eulerAngle(float x, float y, float z) {
    _rotation = angleAxis(x,VX) * angleAxis(y,VY) * angleAxis(z,VZ);
    _dirtyMat = true;

}

void GLTransform::rotateAroundAxis(float angle, glm::vec3 axis) {
    _rotation *= angleAxis(angle,axis);
    _dirtyMat = true;
}

void GLTransform::setRotation(glm::quat rotationQuat) {
    _rotation = rotationQuat;
    _dirtyMat = true;
}

void GLTransform::updateLocalMat(bool forceUpdate) {
    if(_dirtyMat || forceUpdate){
        rotMat = glm::mat4_cast(_rotation);
        localMat = glm::mat4();

        localMat = glm::translate(localMat,_invPos ? -_position : _position);
        localMat *= rotMat;
        localMat = glm::scale(localMat,_scale);

        _dirtyMat = false;
    }
}



void GLTransform::applyWorldMat(const glm::mat4 & parentMat, glm::mat4 *worldMat) {
    updateLocalMat(false);
    *worldMat = parentMat * localMat;
}

bool GLTransform::isInvPos() const {
    return _invPos;
}

void GLTransform::setInvPos(bool invPos) {
    GLTransform::_invPos = invPos;
}

glm::mat4 GLTransform::getRotMat() {
    updateLocalMat(false);
    return rotMat;
}

glm::quat GLTransform::getRotation() {
    return _rotation;
}

void GLTransform::translate(const glm::vec3 & trans) {
    _position += trans;
}




