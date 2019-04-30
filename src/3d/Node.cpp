//
// Created by Gilles Boisson on 2019-04-27.
//

#include "Node.h"



void Node::addChild(Node *node) {
    auto it = find(node);
    if(it == _children.end()){
        node->_parent = this;
        _children.push_back(node);
    }

}

void Node::removeChild(Node *node) {
    auto it = find(node);
    if(it != _children.end()) {
        _children.erase(it);
        node->_parent = nullptr;
    }



}

std::list<Node *>::iterator Node::find(Node *node) {
    return std::find(_children.begin(), _children.end(), node);
}


void Node::updateWorldMat(glm::mat4 *parentMat, glm::mat4 *worldMat) {
    if(parentMat != nullptr){
        trs.applyWorldMat(*parentMat, worldMat);
    }else{
        *worldMat = trs.getLocalMat();
    }

}

void Node::updateWorldMat(glm::mat4 *parentMat) {
    updateWorldMat(parentMat,true);
}

void Node::updateWorldMat(glm::mat4 *parentMat, bool updateChildren) {
    updateWorldMat(parentMat, &_worldMat);
    if(updateChildren){
        for(auto & it : _children){
            it->updateWorldMat(&_worldMat, true);
        }
    }
}

void Node::updateWorldMat() {
    updateWorldMat(true);
}

void Node::updateWorldMat(bool updateChildren) {
    updateWorldMat(nullptr, updateChildren);
}

void Node::updateGeometry() {
    updateWorldMat(true);
}


Node::Node() {}

const char *Node::getName() const {
    return name;
}

void Node::setName(const char *name) {
    name = name;
}

glm::mat4* Node::getWorldMat() {
    return &_worldMat;
}




