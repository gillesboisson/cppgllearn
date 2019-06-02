//
// Created by Gilles Boisson on 2019-05-29.
//

#ifndef CPP_LEARN_CAMERA2D_H
#define CPP_LEARN_CAMERA2D_H


#include "../../core/Camera.h"
#include "../../utils/Rect.h"

class Camera2D : public Camera{
protected:
    Rect _rect;
    using Camera::Camera;

public:

    void updateGeometry() override;

    explicit Camera2D(float x,float y,float width,float height);

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

    const Rect &getRect() const;

    Rect* getRectPtr();



};


#endif //CPP_LEARN_CAMERA2D_H
