//
// Created by Gilles Boisson on 2019-05-28.
//

#include "Entity2D.h"

Entity2D::Entity2D() {
    reset();
}

void Entity2D::reset(){
    _color = glm::vec4(1,1,1,1);
    _parent = nullptr;
    _transform.reset();
}

float Entity2D::getAlpha(){
    return _color[3];
}

void Entity2D::getAlpha(float alpha){
    _color[3] = alpha;
}

glm::vec3 Entity2D::getColor(){
    return glm::vec3(_color.x,_color.y,_color.z);
}

void Entity2D::getColor(glm::vec3 color){
    _color.x = color.x;
    _color.y = color.y;
    _color.z = color.z;
}

void Entity2D::updateGeom(const glm::mat3x2& parentMat){
    _transform.updateWorldMat(&_worldMat,parentMat);
}

void Entity2D::pushGeom(SpriteBatch* batch){

}


void Entity2D::push(SpriteBatch* batch,const glm::mat3x2& parentMat){
    updateGeom(parentMat);
    pushGeom(batch);
}

