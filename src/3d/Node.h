//
// Created by Gilles Boisson on 2019-04-27.
//


#ifndef CPP_LEARN_NODE_H
#define CPP_LEARN_NODE_H
#include <list>

#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../gl/GLTransform.h"

using namespace std;

class Node {
protected:
    Node* _parent{};
    list<Node*> _children;
    mat4 _worldMat;


public:
    GLTransform trs;
    const char* name;

    const char *getName() const;

    void setName(const char *name);

    Node();

    mat4* getWorldMat();

    void addChild(Node *node);
    void removeChild(Node *node);
    list<Node*>::iterator find(Node *node);

    // geometry update;
    void updateGeometry();
    void updateWorldMat();
    virtual void updateWorldMat(bool updateChildren);
    void updateWorldMat(mat4 *parentMat);
    virtual void updateWorldMat(mat4 *parentMat, bool updateChildren);
    virtual void updateWorldMat(mat4 *parentMat, mat4 *worldMat);



};


#endif //CPP_LEARN_NODE_H
