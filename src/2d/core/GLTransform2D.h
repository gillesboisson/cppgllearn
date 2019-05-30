//
// Created by Gilles Boisson on 2019-05-28.
//

#ifndef CPP_LEARN_GLTRANSFORM2D_H
#define CPP_LEARN_GLTRANSFORM2D_H

#include <glm/glm.hpp>

class GLTransform2D {
protected:
    glm::vec2 _position;
    glm::vec2 _scale;
    glm::vec2 _size;
    glm::vec2 _pivot;
    float _depth;
    float _rotation;

    glm::mat3 _mat;
    bool _dirtyRot;
    bool _dirtyMat;

    glm::vec2 _rs;
    glm::vec2 _rc;



public:
    GLTransform2D();

    void reset();

    // Accessors
public:

    void updateRot();
    void updateLocalMat();
    void updateLayout();
    void updateWorldMat(glm::mat3 *wm, const glm::mat3 &pm);
    void updateWorldMat(glm::mat3 *worldMat);


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
};


#endif //CPP_LEARN_GLTRANSFORM2D_H
