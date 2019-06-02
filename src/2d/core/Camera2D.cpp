//
// Created by Gilles Boisson on 2019-05-29.
//

#include "Camera2D.h"

Camera2D::Camera2D(float x, float y, float width, float height) :Camera(){

    _rect = Rect(x,y,width,height);

    update2DProjection();
}

void Camera2D::update2DProjection() {
    init2D(_rect.getWidth(), _rect.getHeight(), -1.000, 1.000);
}

void Camera2D::resize(float width,float height) {

    _rect.resize(width,height);


    update2DProjection();
}


float Camera2D::getX() const {
    return _rect.getX();
}

void Camera2D::setX(float x) {
    _rect.setX(x);
}

float Camera2D::getY() const {
    return _rect.getY();
}

void Camera2D::setY(float y) {
   _rect.setY(y);
}

float Camera2D::getWidth() const {
    return _rect.getWidth();
}

void Camera2D::setWidth(float width) {
    _rect.setWidth(width);
    update2DProjection();
}


float Camera2D::getHeight() const {
    return _rect.getHeight();
}

void Camera2D::setHeight(float height) {
    _rect.setHeight(height);
    update2DProjection();

}

const Rect &Camera2D::getRect() const {
    return _rect;
}

Rect *Camera2D::getRectPtr() {
    return &_rect;
}

void Camera2D::updateGeometry() {
    transform.position(-_rect.getX(),-_rect.getY(),0);
    Node::updateGeometry();
}





