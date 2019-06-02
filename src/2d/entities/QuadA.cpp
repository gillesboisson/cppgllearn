//
// Created by Gilles Boisson on 2019-05-29.
//

#include "QuadA.h"

template<class BatchT>
glm::vec2 QuadA<BatchT>::Pos[] = {
    glm::vec2(0,0),
    glm::vec2(1,0),
    glm::vec2(0,1),
    glm::vec2(1,1),
};

template<class BatchT>
uint16_t QuadA<BatchT>::Indices[] = {
    0,1,2,
    1,3,2
};

template<class BatchT>
QuadA<BatchT>::QuadA(glm::vec2* uvs):PolyA<BatchT>(4,6,Pos,uvs,Indices) {}


template<>
QuadA<SpriteBatch>::QuadA(glm::vec2* uvs):PolyA<SpriteBatch>(4,6,Pos,uvs,Indices) {}
