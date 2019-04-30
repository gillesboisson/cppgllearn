//
// Created by Gilles Boisson on 2019-04-27.
//

#ifndef CPP_LEARN_CAMERA_H
#define CPP_LEARN_CAMERA_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "./Node.h"

using namespace std;
using namespace glm;

class Camera: public Node{
    mat4 _projection = mat4(1.0f);
    mat4 _invWorldMat = mat4(1.0f);


public:
    void initOrtho(float left = -1, float right = 1, float bottom = -1, float top = 1, float near = 0.0001,
                   float far = 100);
    void init2D(float width, float height, float near = 0.0001, float far = 100);

    void initPerspective(float fov, float ratio, float near = 0.0001, float far = 100);
    void updateMVP(mat4 *mvpMat, mat4 *modelTransformMat);

    static Camera camPerspective(float fov, float ratio, float near = 0.0001, float far = 100);
    static Camera cam2D(float width, float height, float near = 0.0001, float far = 100);
    static Camera camOrtho(float left = -1, float right = 1, float bottom = -1, float top = 1, float near = 0.0001,
                           float far = 100);

    Camera();

    void updateWorldMat(mat4 *parentMat, bool updateChildren) override;


};


#endif //CPP_LEARN_CAMERA_H
