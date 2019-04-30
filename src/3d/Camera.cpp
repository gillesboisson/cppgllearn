//
// Created by Gilles Boisson on 2019-04-27.
//

#include "Camera.h"

void Camera::initOrtho(float left, float right, float bottom, float top, float near, float far) {
    _projection = glm::ortho(left,right,bottom,top,near,far);
}

void Camera::init2D(float width, float height, float near, float far) {
    _projection = glm::ortho(0.0f,width,0.0f,-height,near,far);
}

void Camera:: initPerspective(float fov, float ratio, float near, float far){
    _projection = glm::perspective(fov,ratio,near,far);
}

void Camera::updateMVP(glm::mat4 *mvpMat, glm::mat4 *modelTransformMat) {
    *mvpMat = _projection * _invWorldMat * *modelTransformMat;
}

Camera::Camera():Node() {
    transform.setInvPos(true);
}


Camera Camera::camPerspective(float fov, float ratio, float near, float far) {
    auto cam = Camera();
    cam.initPerspective(fov, ratio, near, far);

    return cam;
}

Camera Camera::cam2D(float width, float height, float near, float far) {
    auto cam = Camera();
    cam.init2D(width, height, near, far);
    return cam;
}

Camera Camera::camOrtho(float left, float right, float bottom, float top, float near, float far) {
    auto cam = Camera();
    cam.initOrtho(left, right, bottom, top, near, far);
    return cam;
}

void Camera::updateWorldMat(glm::mat4 *parentMat, bool updateChildren) {
    Node::updateWorldMat(parentMat, updateChildren);
    _invWorldMat = inverse(_worldMat);
}






