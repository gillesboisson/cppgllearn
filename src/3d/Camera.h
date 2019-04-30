//
// Created by Gilles Boisson on 2019-04-27.
//

#ifndef CPP_LEARN_CAMERA_H
#define CPP_LEARN_CAMERA_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "./Node.h"


class Camera: public Node{
    glm::mat4 _projection = glm::mat4(1.0f);
    glm::mat4 _invWorldMat = glm::mat4(1.0f);


public:
    void initOrtho(float left = -1, float right = 1, float bottom = -1, float top = 1, float near = 0.0001,
                   float far = 100);
    void init2D(float width, float height, float near = 0.0001, float far = 100);

    void initPerspective(float fov, float ratio, float near = 0.0001, float far = 100);
    void updateMVP(glm::mat4 *mvpMat, glm::mat4 *modelTransformMat);

    static Camera camPerspective(float fov, float ratio, float near = 0.0001, float far = 100);
    static Camera cam2D(float width, float height, float near = 0.0001, float far = 100);
    static Camera camOrtho(float left = -1, float right = 1, float bottom = -1, float top = 1, float near = 0.0001,
                           float far = 100);

    Camera();

    void updateWorldMat(glm::mat4 *parentMat, bool updateChildren) override;


};


#endif //CPP_LEARN_CAMERA_H
