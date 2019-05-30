//
// Created by Gilles Boisson on 2019-05-29.
//

#include "Quad.h"


glm::vec2 Quad::Pos[] = {
    glm::vec2(0,0),
    glm::vec2(1,0),
    glm::vec2(0,1),
    glm::vec2(1,1),
};

uint16_t Quad::Indices[] = {
    0,1,2,
    1,3,2
};

Quad::Quad(glm::vec2* uvs):PolyA(4,6,Pos,uvs,Indices) {

}

