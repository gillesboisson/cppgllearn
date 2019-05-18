//
// Created by Gilles Boisson on 2019-05-18.
//

#ifndef CPP_LEARN_MODEL_H
#define CPP_LEARN_MODEL_H


#include "Node.h"
#include "../gl/GLMesh.h"
#include "../gl/GLMaterialA.h"

class Model :public Node{

protected:
    GLMesh* _mesh;

    GLMaterialA* _material;
public:
    Model(GLMesh* mesh,GLMaterialA* material);

    // getters
    GLMesh *getMesh() const;
    GLMaterialA *getMaterial() const;


};


#endif //CPP_LEARN_MODEL_H
