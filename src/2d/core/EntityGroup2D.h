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
    bool _propagateFastTransform;

    void prepareBatch(void *batch) override;

public:
    EntityGroup2D();


    void addChild(Entity2D *child);

    void removeChild(Entity2D *child);

    void setFastTransform(bool fastTransform) override;
    void setFastTransform(bool fastTransform,bool enableFastTransformPropagation);

    bool isPropagateFastTransform() const;

    void setPropagateFastTransform(bool propagateFastTransform);


};



#endif //CPP_LEARN_ENTITYGROUP2D_H
