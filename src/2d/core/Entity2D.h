//
// Created by Gilles Boisson on 2019-05-28.
//

#ifndef CPP_LEARN_ENTITY2D_H
#define CPP_LEARN_ENTITY2D_H

#include <glm/glm.hpp>
#include "GLTransform2D.h"

#include "SpriteBatch.h"

class EntityGroup2D;

class Entity2D {
protected:

    glm::vec4 _color;
    glm::mat3x2 _worldMat;
    EntityGroup2D *_parent;

    void updateGeom(const glm::mat3x2 &parentMat);
    virtual void pushGeom(SpriteBatch *batch);

public:
    GLTransform2D _transform;

    Entity2D();


    virtual void reset();

    float getAlpha();

    void getAlpha(float alpha);

    glm::vec3 getColor();

    void getColor(glm::vec3 color);




    void push(SpriteBatch *batch, const glm::mat3x2 &parentMat);


};


#endif //CPP_LEARN_ENTITY2D_H
