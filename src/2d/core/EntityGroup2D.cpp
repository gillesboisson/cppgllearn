//
// Created by Gilles Boisson on 2019-05-29.
//

#include "EntityGroup2D.h"

EntityGroup2D::EntityGroup2D():Entity2D() {

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
    }
}

void EntityGroup2D::removeChild(Entity2D *child){
    auto found = std::find(_children.begin(),_children.end(),child);
    if(found != _children.end()){
       _children.erase(found);
    }
}