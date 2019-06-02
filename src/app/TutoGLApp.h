//
// Created by Gilles Boisson on 2019-04-30.
//

#ifndef CPP_LEARN_TUTOGLAPP_H
#define CPP_LEARN_TUTOGLAPP_H


#include "../gl/GLFWAppA.h"
#include "../core/Camera.h"
#include "../2d/core/Stage2D.h"
#include "../2d/core/TextureAtlas.h"
#include "../2d/entities/Sprite.h"
#include "../2d/entities/TileGrid.h"


class TutoGLApp : public GLFWAppA {
protected:
    Camera2D *_cam;
    Stage2D *_stage;
    TextureAtlas *_atlas;
    EntityGroup2D *_group1;
    EntityGroup2D *_group2;
    Sprite *_sprite1;
    Sprite *_sprite2;
    TileGrid *_grid;


public:
    TutoGLApp();

    void afterRendererInit() override;
    void beforeQuit() override;
    void update(double frameInterval,float frameSpeed) override;
    void initRenderer() override ;

    GLBuffer *vPBuffer;


    float _angle;
};


#endif //CPP_LEARN_TUTOGLAPP_H
