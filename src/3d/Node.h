//
// Created by Gilles Boisson on 2019-04-27.
//


#ifndef CPP_LEARN_NODE_H
#define CPP_LEARN_NODE_H
#include <list>


#include <glm/glm.hpp>
#include "../gl/GLTransform.h"


class Node {
protected:
    Node* _parent{};
    std::list<Node*> _children{};
    glm::mat4 _worldMat{};



public:
    GLTransform transform{};
    const char* name{};
    const char *getName() const;

    void setName(const char *name);


    glm::mat4* getWorldMat();

    void addChild(Node *node);
    void removeChild(Node *node);
    std::list<Node*>::iterator find(Node *node);


    // geometry update;
    void updateGeometry();
    void updateWorldMat();
    virtual void updateWorldMat(bool updateChildren);
    void updateWorldMat(glm::mat4 *parentMat);
    virtual void updateWorldMat(glm::mat4 *parentMat, bool updateChildren);
    virtual void updateWorldMat(glm::mat4 *parentMat, glm::mat4 *worldMat);



};


#endif //CPP_LEARN_NODE_H
