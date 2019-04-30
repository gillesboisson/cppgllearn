//
// Created by Gilles Boisson on 2019-04-27.
//

#include "GLTransformA.h"

glm::mat4 GLTransformA::getLocalMat() {
    updateLocalMat();
    return localMat;
}

void GLTransformA::updateLocalMat() {
    updateLocalMat(false);
}
