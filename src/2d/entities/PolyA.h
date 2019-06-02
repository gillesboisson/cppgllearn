//
// Created by Gilles Boisson on 2019-05-29.
//

#ifndef CPP_LEARN_POLYA_H
#define CPP_LEARN_POLYA_H

#include "../core/Entity2D.h"

class PolyA : public Entity2D{
protected:
    PolyA();
    void set(uint32_t nbPoints, uint16_t nbIndices, glm::vec2 *points, glm::vec2 *uvs, uint16_t *indices);

    uint32_t _nbPoints;
    uint16_t _nbIndices;

    glm::vec2* _positions;
    glm::vec2* _uvs;
    uint16_t* _indices;

    void pushGeom(SpriteBatch *batch) override;
    virtual void pushVertices(SpriteVertex *pVertex, uint16_t *pInt, uint16_t offset);

public:
    PolyA(uint32_t nbPoints,uint16_t nbIndices,glm::vec2*  positions,glm::vec2* uvs,uint16_t* indices);



    void copyIndices(uint16_t *pInt, uint16_t offset);

};


#endif //CPP_LEARN_POLYA_H
