//
// Created by Gilles Boisson on 2019-05-29.
//

#include "PolyA.h"

PolyA::PolyA() {
    //set(0,0, nullptr,nullptr,nullptr);
}

PolyA::PolyA(uint32_t nbPoints,uint16_t nbIndices,glm::vec2*  points,glm::vec2* uvs,uint16_t* indices) {
    set(nbPoints,nbIndices,points,uvs,indices);
}

void PolyA::set(uint32_t nbPoints,uint16_t nbIndices,glm::vec2*  points,glm::vec2* uvs,uint16_t* indices){
    _nbPoints = nbPoints;
    _nbIndices = nbIndices;
    _positions = points;
    _indices = indices;
    _uvs = uvs;
}

void PolyA::pushGeom(SpriteBatch *batch) {
//    Entity2D::pushGeom(batch);
    SpriteVertex* vertices;
    uint16_t *indices;
    uint16_t indicesOffset = batch->pull(&vertices,&indices,_nbPoints,_nbIndices);

    pushVertices(vertices,indices,indicesOffset);

}

void PolyA::copyIndices(uint16_t *pInt, uint16_t offset){
    for (int i = 0; i < _nbIndices; ++i) {
        pInt[i] = _indices[i] + offset;
    }
}

void PolyA::pushVertices(SpriteVertex *pVertex, uint16_t *pInt, uint16_t offset) {
    for (int i = 0; i < _nbPoints; ++i) {
        glm::vec2 pt = _worldMat * glm::vec3(_positions[i],1);
        pVertex[i].pos = glm::vec3(pt,transform.getDepth());
        pVertex[i].color = _color;
        pVertex[i].uv = _uvs[i];
    }

    copyIndices(pInt,offset);
}


