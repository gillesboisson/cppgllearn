//
// Created by Gilles Boisson on 2019-05-29.
//

#ifndef CPP_LEARN_SPRITE_H
#define CPP_LEARN_SPRITE_H

#include "QuadA.h"
#include "../core/SubTexture.h"


class Sprite : public QuadA<SpriteBatch>{
protected:

    SubTexture* _subTexture;
    void prepareBatch(void *batch) override;

    //float _uvs[8];

public:
    Sprite(SubTexture* texture);
    ~Sprite();

    SubTexture *getSubTexture() const;

    void setSubTexture(SubTexture *subTexture);

};


#endif //CPP_LEARN_SPRITE_H
