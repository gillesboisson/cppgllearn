//
// Created by Gilles Boisson on 2019-05-30.
//

#include "Rect.h"

Rect::Rect():Rect(0,0,0,0) {}

Rect::Rect(float x, float y, float width, float height) {
   set(x,y,width,height);
}



Rect::Rect(glm::vec2 position, float width, float height):Rect(position.x, position.y, width, height){
}

void Rect::set(float x, float y, float width, float height){
    _left = x;
    _top = y;
    _right = x + width;
    _bottom = y + height;
}

float Rect::getLeft() const {
    return _left;
}

void Rect::setLeft(float left) {
    _left = left;
}

float Rect::getRight() const {
    return _right;
}

void Rect::setRight(float right) {
    _right = right;
}

float Rect::getTop() const {
    return _top;
}

void Rect::setTop(float top) {
    _top = top;
}

float Rect::getBottom() const {
    return _bottom;
}

void Rect::setBottom(float bottom) {
    _bottom = bottom;
}

void Rect::resize(float width,float height) {
    _right = _left + width;
    _bottom = _top + height;
}

// dynamic props

float Rect::getX() const {
    return _left;
}

void Rect::setX(float x) {
    _right += x - _left;
    _left = x;
}

float Rect::getY() const {
    return _top;
}

void Rect::setY(float y) {
    _bottom += y - _top;
    _top = y;
}

float Rect::getWidth() const {
    return _right - _left;
}

void Rect::setWidth(float width) {
    _right = _left + width;
}


float Rect::getHeight() const {
    return _bottom - _top;
}

void Rect::setHeight(float height) {
    _bottom = _top + height;
}

glm::vec2 Rect::getPosition() const{
    return glm::vec2(_left,_top);
}

void Rect::setPosition(const glm::vec2 &position){
    _right += position.x - _left;
    _left = position.x;
    _bottom += position.y - _top;
    _top = position.y;
}

bool Rect::hitRect(const Rect &rect) const {
    return _left < rect._right
           && _right > rect._left
           && _top < rect._bottom
           && _bottom > rect._top;
}

bool Rect::contain(const Rect &rect) const {
    return _left <= rect._left
           && _right > rect._right
           && _top <= rect._top
           && _bottom > rect._bottom;
}

void Rect::set(const Rect &rect) {
    _left = rect._left;
    _right = rect._right;
    _top = rect._top;
    _bottom = rect._bottom;

}

void Rect::add(const Rect &rect, bool setIfEmpty) {

    if (setIfEmpty &&
        _left == 0 &&
        _top == 0 &&
        _right == 0 &&
        _bottom == 0
        ) {
        set(rect);
        return;
    }

    if (_left > rect._left) _left = rect._left;
    if (_top > rect._top) _top = rect._top;
    if (_right < rect._right) _right = rect._right;
    if (_bottom < rect._bottom) _bottom = rect._bottom;
}

void Rect::clamp(const Rect &rect) {
    if (_left < rect._left) _left = rect._left;
    if (_top < rect._top) _top = rect._top;
    if (_right > rect._right) _right = rect._right;
    if (_bottom > rect._bottom) _bottom = rect._bottom;

}

bool Rect::containPoint(float x, float y) const{
    return _left <= x
           && _right > x
           && _top <= y
           && _bottom > y;
}

bool Rect::containPoint(const glm::vec2 &point) const {
    return containPoint(point.x,point.y);
}

Rect* Rect::fit(Rect *rect) const {

    float rWidth = rect->getWidth();
    float rHeight = rect->getHeight();

    if (rWidth > getWidth() || rHeight > getHeight()) return nullptr;


    if (rect->_left < _left) {
        rect->setX(_left);
    }

    if (rect->_right > _right) {
        rect->setX(_right - rWidth);
    }

    if (rect->_top < _top) {
        rect->setY(_top);
    }

    if (rect->_bottom > _bottom) {
        rect->setY(_bottom - rHeight);
    }

    return rect;
}


Rect* Rect::clone() const {
    return new Rect(getX(),getY(),getWidth(),getHeight());
}