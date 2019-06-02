//
// Created by Gilles Boisson on 2019-05-28.
//

#include "Entity2D.h"
#include "EntityGroup2D.h"

Entity2D::Entity2D() {
    reset();
}

void Entity2D::reset(){
    _color = glm::vec4(1,1,1,1);
    _parent = nullptr;
    transform.reset();
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

void Entity2D::updateGeom(const glm::mat3 &parentMat){
    transform.updateWorldMat(&_worldMat,parentMat);
}

void Entity2D::push(void *batch, const glm::mat3 &parentMat){
    updateGeom(parentMat);
    prepareBatch(batch);
}

const glm::vec2 &Entity2D::getPosition() const {
    return transform.getPosition();
}

const glm::vec2 &Entity2D::getScale() const {
    return transform.getScale();
}

const glm::vec2 &Entity2D::getPivot() const {
    return transform.getPivot();
}

const glm::vec2 &Entity2D::getSize() const {
    return transform.getSize();
}

float Entity2D::getRotation() const {
    return transform.getRotation();
}

float Entity2D::getDepth() const {
    return transform.getDepth();
}

void Entity2D::setPosition(const glm::vec2 &position) {
    transform.setPosition(position);
}

void Entity2D::setScale(const glm::vec2 &scale){
    transform.setScale(scale);
}

void Entity2D::setSize(const glm::vec2 &size) {
    transform.setSize(size);
}

void Entity2D::setPivot(const glm::vec2 &pivot) {
    transform.setPivot(pivot);
}

void Entity2D::setRotation(float rotation) {
    transform.setRotation(rotation);
}

void Entity2D::setDepth(float depth) {
    transform.setDepth(depth);
}

void Entity2D::setPosition(float x, float y) {
    transform.setPosition(x,y);
}

void Entity2D::setScale(float x, float y) {
    transform.setScale(x,y);
}

void Entity2D::setPivot(float x, float y) {
    transform.setPivot(x,y);
}

void Entity2D::setSize(float x, float y) {
    transform.setSize(x,y);
}

void Entity2D::setScale(float scale) {
    transform.setScale(scale);
}

bool Entity2D::isFastTransform() const {
    return transform.isFastTransform();
}

void Entity2D::setFastTransform(bool fastTransform) {
    transform.setFastTransform(fastTransform);
}

Entity2D::~Entity2D() {
    if(_parent != nullptr) _parent->removeChild(this);

}








