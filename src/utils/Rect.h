//
// Created by Gilles Boisson on 2019-05-30.
//

#ifndef CPP_LEARN_RECT_H
#define CPP_LEARN_RECT_H

#include <glm/glm.hpp>

class Rect {

protected:
    float _left;
    float _right;
    float _top;
    float _bottom;

public:
    explicit Rect(float x,float y,float width,float height);
    explicit Rect(glm::vec2 position,float width,float height);

    float getLeft() const;

    void setLeft(float left);

    float getRight() const;

    void setRight(float right);

    float getTop() const;

    void setTop(float top);

    float getBottom() const;

    void setBottom(float bottom);

    void setX(float x);

    float getX() const;

    float getY() const;

    void setY(float y);

    float getWidth() const;

    void setWidth(float width);

    float getHeight() const;

    void setHeight(float height);

    bool hitRect(const Rect &rect) const;

    bool contain(const Rect &rect) const;

    void set(const Rect &rect);

    void add(const Rect &rect, bool setIfEmpty = true);

    void clamp(const Rect &rect);

    bool containPoint(float x, float y) const;

    bool containPoint(const glm::vec2 &point) const;

    Rect *fit(Rect *rect);

    Rect *fit(Rect *rect) const;

    Rect *clone() const;
};


#endif //CPP_LEARN_RECT_H
