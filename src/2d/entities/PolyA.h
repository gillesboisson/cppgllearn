//
// Created by Gilles Boisson on 2019-05-29.
//

#ifndef CPP_LEARN_POLYA_H
#define CPP_LEARN_POLYA_H

#include "../core/Entity2D.h"


template<class BatchT>
class PolyA : public Entity2D{
protected:
    PolyA();
    void set(uint32_t nbPoints, uint16_t nbIndices, glm::vec2 *points, glm::vec2 *uvs, uint16_t *indices);

    uint32_t _nbPoints;
    uint16_t _nbIndices;

    glm::vec2* _positions;
    glm::vec2* _uvs;
    uint16_t* _indices;

    void prepareBatch(void *batch) override;
    void pushVertices(void *pVertex, uint16_t *pInt, uint16_t offset);

public:
    PolyA(uint32_t nbPoints,uint16_t nbIndices,glm::vec2*  positions,glm::vec2* uvs,uint16_t* indices);



    void copyIndices(uint16_t *pInt, uint16_t offset);

};

template<class BatchT>
PolyA<BatchT>::PolyA() {
    set(0,0, nullptr,nullptr,nullptr);
}

template<class BatchT>
PolyA<BatchT>::PolyA(uint32_t nbPoints,uint16_t nbIndices,glm::vec2*  points,glm::vec2* uvs,uint16_t* indices) {
    set(nbPoints,nbIndices,points,uvs,indices);
}
template<class BatchT>
void PolyA<BatchT>::set(uint32_t nbPoints,uint16_t nbIndices,glm::vec2*  points,glm::vec2* uvs,uint16_t* indices){
    _nbPoints = nbPoints;
    _nbIndices = nbIndices;
    _positions = points;
    _indices = indices;
    _uvs = uvs;
}

template<class BatchT>
void PolyA<BatchT>::copyIndices(uint16_t *pInt, uint16_t offset){
    for (int i = 0; i < _nbIndices; ++i) {
        pInt[i] = _indices[i] + offset;
    }
}

template<>
inline void PolyA<SpriteBatch>::pushVertices(void *pVertex, uint16_t *pInt, uint16_t offset) {
    SpriteVertex* spriteV = (SpriteVertex*) pVertex;
    for (int i = 0; i < _nbPoints; ++i) {
        glm::vec2 pt = _worldMat * glm::vec3(_positions[i],1);
        spriteV[i].pos = glm::vec3(pt,transform.getDepth());
        spriteV[i].color = _color;
        spriteV[i].uv = _uvs[i];
    }

    copyIndices(pInt,offset);
}

template<>
inline void PolyA<SpriteBatch>::prepareBatch(void *batch) {

    SpriteVertex* vertices;
    uint16_t *indices;
    uint16_t indicesOffset = ((SpriteBatch*)batch)->pull(&vertices,&indices,_nbPoints,_nbIndices);

    pushVertices(vertices,indices,indicesOffset);
}



#endif //CPP_LEARN_POLYA_H
