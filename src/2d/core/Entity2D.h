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
    glm::mat3 _worldMat;
    EntityGroup2D *_parent;

    void updateGeom(const glm::mat3 &parentMat);
    virtual void prepareBatch(void* batch) = 0;
//    virtual void updateGeom(const glm::mat3 &parentMat);
//
//    virtual void pushGeom(void *batch);
//
//    virtual void prepareBatch(void *batch);

public:
    GLTransform2D transform;

    Entity2D();
    ~Entity2D();


    virtual void reset();


    virtual void push(void *batch, const glm::mat3 &parentMat);

    // accessors

    float getAlpha();

    void getAlpha(float alpha);

    glm::vec3 getColor();

    void getColor(glm::vec3 color);

    // transform accessors

    const glm::vec2 &getPosition() const;

    void setPosition(const glm::vec2 &position);

    const glm::vec2 &getScale() const;

    void setScale(const glm::vec2 &scale);

    const glm::vec2 &getPivot() const;

    void setPivot(const glm::vec2 &pivot);

    float getRotation() const;

    void setRotation(float rotation);

    float getDepth() const;

    void setDepth(float depth);

    const glm::vec2 &getSize() const;

    void setSize(const glm::vec2 &size);

    void setPosition(float x, float y);

    void setScale(float x, float y);

    void setScale(float scale);

    void setSize(float x, float y);

    void setPivot(float x, float y);

    bool isFastTransform() const;

    virtual void setFastTransform(bool fastTransform);



};

//template<class BatchT>
//void Entity2D::push(BatchT *batch, const glm::mat3 &parentMat){
//    updateGeom(parentMat);
//    prepareBatch(batch);
//    //pushGeom(batch);
//}
//
//
//void Entity2D::pushGeom(void* batch){}
//
//
//void Entity2D::prepareBatch(void* batch){}



#endif //CPP_LEARN_ENTITY2D_H
