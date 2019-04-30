//
// Created by Gilles Boisson on 2019-04-26.
//


#ifndef CPP_LEARN_GLTRANSFORM_H
#define CPP_LEARN_GLTRANSFORM_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>

#include "GLTransformA.h"

using namespace glm;

const vec3 VX(1.0f,0.0f,0.0f);
const vec3 VY(0.0f,1.0f,0.0f);
const vec3 VZ(0.0f,0.0f,1.0f);


class GLTransform : public GLTransformA {
    vec3 _position;
    vec3 _scale = vec3(1.0f);
    quat _rotation;
    bool _dirtyMat = true;
    bool _invPos = false;

protected:

    void updateLocalMat(bool forceUpdate) override;





public:
    bool isInvPos() const;
    void setInvPos(bool invPos);

    vec3 getScale() const;
    vec3 getPosition() const;
    void setRotation(quat rotationQuat);
    quat getRotation();

    void scale(float s);
    void scale(float x, float y, float z);
    void position(float x, float y, float z);

    mat4 getRotMat();

    void eulerAngle(float x, float y, float z);
    void rotateAroundAxis(float angle, vec3 axis);

    void applyWorldMat(const mat4 & parentMat, mat4 *worldMat);


    void translate(float x, float y, float z);
    void translate(const vec3 &trans);
};


#endif //CPP_LEARN_GLTRANSFORM_H
