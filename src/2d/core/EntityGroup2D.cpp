//
// Created by Gilles Boisson on 2019-05-29.
//

#include "EntityGroup2D.h"

EntityGroup2D::EntityGroup2D():Entity2D() {
    _propagateFastTransform = true;
}

void EntityGroup2D::pushGeom(SpriteBatch *batch) {
    for(auto entity:_children){
        entity->push(batch,_worldMat);
    }
}



void EntityGroup2D::addChild(Entity2D *child){
    auto found = std::find(_children.begin(),_children.end(),child);
    if(found == _children.end()){
        _children.push_back(child);
        if(_propagateFastTransform) child->setFastTransform(transform.isFastTransform());
    }
}

void EntityGroup2D::removeChild(Entity2D *child){
    auto found = std::find(_children.begin(),_children.end(),child);
    if(found != _children.end()){
       _children.erase(found);
    }
}

void EntityGroup2D::setFastTransform(bool fastTransform) {
    Entity2D::setFastTransform(fastTransform);
    if(_propagateFastTransform) {
        for(auto entity:_children){
            entity->setFastTransform(fastTransform);
        }
    }
}

bool EntityGroup2D::isPropagateFastTransform() const {
    return _propagateFastTransform;
}

void EntityGroup2D::setPropagateFastTransform(bool propagateFastTransform) {
    _propagateFastTransform = propagateFastTransform;
}

void EntityGroup2D::setFastTransform(bool fastTransform, bool enableFastTransformPropagation) {
    _propagateFastTransform = enableFastTransformPropagation;
    setPropagateFastTransform(fastTransform);
}

