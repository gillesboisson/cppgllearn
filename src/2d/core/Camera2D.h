//
// Created by Gilles Boisson on 2019-05-29.
//

#ifndef CPP_LEARN_CAMERA2D_H
#define CPP_LEARN_CAMERA2D_H


#include "../../3d/Camera.h"

class Camera2D : public Camera{
protected:
    float _x;
    float _y;
    float _width;
    float _height;

public:

    Camera2D(float x,float y,float width,float height);

    float getX() const;

    void setX(float x);

    float getY() const;

    void setY(float y);

    float getWidth() const;

    void setWidth(float width);

    float getHeight() const;

    void setHeight(float height);

    void update2DProjection();

    void resize(float width, float height);
};


#endif //CPP_LEARN_CAMERA2D_H
