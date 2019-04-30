//
// Created by Gilles Boisson on 2019-04-26.
//


#ifndef CPP_LEARN_GLTRANSFORM_H
#define CPP_LEARN_GLTRANSFORM_H

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include "GLTransformA.h"



const glm::vec3 VX(1.0f,0.0f,0.0f);
const glm::vec3 VY(0.0f,1.0f,0.0f);
const glm::vec3 VZ(0.0f,0.0f,1.0f);


class GLTransform : public GLTransformA {
    glm::vec3 _position;
    glm::vec3 _scale = glm::vec3(1.0f);
    glm::quat _rotation;
    bool _dirtyMat = true;
    bool _invPos = false;

protected:

    void updateLocalMat(bool forceUpdate) override;





public:
    bool isInvPos() const;
    void setInvPos(bool invPos);

    glm::vec3 getScale() const;
    glm::vec3 getPosition() const;
    void setRotation(glm::quat rotationQuat);
    glm::quat getRotation();

    void scale(float s);
    void scale(float x, float y, float z);
    void position(float x, float y, float z);

    glm::mat4 getRotMat();

    void eulerAngle(float x, float y, float z);
    void rotateAroundAxis(float angle, glm::vec3 axis);

    void applyWorldMat(const glm::mat4 & parentMat, glm::mat4 *worldMat);


    void translate(float x, float y, float z);
    void translate(const glm::vec3 &trans);
};


#endif //CPP_LEARN_GLTRANSFORM_H
