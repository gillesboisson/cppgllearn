//
// Created by Gilles Boisson on 2019-05-29.
//

#include "Camera2D.h"

Camera2D::Camera2D(float x, float y, float width, float height) {
    _width = width;
    _height = height;
    _x = x;
    _y = y;
    update2DProjection();
}

void Camera2D::update2DProjection() {
    init2D(_width, _height, 0.0001, 1);
}

void Camera2D::resize(float width,float height) {
    _width = width;
    _height = height;
    update2DProjection();
}


float Camera2D::getX() const {
    return _x;
}

void Camera2D::setX(float x) {
    _x = x;
}

float Camera2D::getY() const {
    return _y;
}

void Camera2D::setY(float y) {
    _y = y;
}

float Camera2D::getWidth() const {
    return _width;
}

void Camera2D::setWidth(float width) {
    _width = width;
    update2DProjection();
}


float Camera2D::getHeight() const {
    return _height;
}

void Camera2D::setHeight(float height) {
    _height = height;
    update2DProjection();

}



