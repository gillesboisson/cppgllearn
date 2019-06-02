//
// Created by Gilles Boisson on 2019-05-29.
//

#ifndef CPP_LEARN_QUADA_H
#define CPP_LEARN_QUADA_H

#include "PolyA.h"

template<class BatchT>
class QuadA :public PolyA<BatchT>{

    static glm::vec2 Pos[4];
    static uint16_t Indices[6];

public:
    QuadA(glm::vec2* uvs);

};



#endif //CPP_LEARN_QUADA_H
