//
// Created by Gilles Boisson on 2019-05-29.
//

#ifndef CPP_LEARN_ENTITYGROUP2D_H
#define CPP_LEARN_ENTITYGROUP2D_H


#include <vector>

#include "Entity2D.h"

class EntityGroup2D : public Entity2D{
protected:
    std::vector<Entity2D*> _children;

    void pushGeom(SpriteBatch *batch) override;

public:
    EntityGroup2D();


    void addChild(Entity2D *child);

    void removeChild(Entity2D *child);
};



#endif //CPP_LEARN_ENTITYGROUP2D_H
