//
// Created by Gilles Boisson on 2019-04-27.
//

#ifndef CPP_LEARN_GLTRANSFORMA_H
#define CPP_LEARN_GLTRANSFORMA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


class GLTransformA {
protected:
    glm::mat4 localMat = glm::mat4(1.0f);
    glm::mat4 rotMat = glm::mat4(1.0f);
    virtual void updateLocalMat(bool forceUpdate) = 0;
    void updateLocalMat();
public:
    glm::mat4 getLocalMat();


};


#endif //CPP_LEARN_GLTRANSFORMA_H
