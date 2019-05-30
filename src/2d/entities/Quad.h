//
// Created by Gilles Boisson on 2019-05-29.
//

#ifndef CPP_LEARN_QUAD_H
#define CPP_LEARN_QUAD_H

#include "PolyA.h"

class Quad :public PolyA{

    static glm::vec2 Pos[4];
    static uint16_t Indices[6];

public:
    Quad(glm::vec2* uvs);

};


#endif //CPP_LEARN_QUAD_H
