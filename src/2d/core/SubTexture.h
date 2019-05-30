//
// Created by Gilles Boisson on 2019-05-29.
//

#ifndef CPP_LEARN_SUBTEXTURE_H
#define CPP_LEARN_SUBTEXTURE_H


#include <glm/glm.hpp>
#include "../../gl/GLTexture.h"

class SubTexture {
protected:
    uint32_t _left;
    uint32_t _top;
    uint32_t _right;
    uint32_t _bottom;
    uint32_t _width;
    uint32_t _height;
    GLTexture* _texture;
public:
    SubTexture(GLTexture* texture,uint32_t x,uint32_t y,uint32_t width,uint32_t height);
    void copyUvs(float* uvs);

public:
    uint32_t getLeft() const;

    void setLeft(uint32_t left);

    uint32_t getTop() const;

    void setTop(uint32_t top);

    uint32_t getRight() const;

    void setRight(uint32_t right);

    uint32_t getBottom() const;

    void setBottom(uint32_t bottom);

    GLTexture *getTexture() const;

    void setTexture(GLTexture *texture);

    void copyUvs(glm::vec2 *uvs);

    uint32_t getWidth() const;

    uint32_t getHeight() const;

    void updateQuadVertices(glm::vec2 *uvs, glm::vec2 *points);
};


#endif //CPP_LEARN_SUBTEXTURE_H
