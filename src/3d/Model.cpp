//
// Created by Gilles Boisson on 2019-05-18.
//

#include "Model.h"

Model::Model(GLMesh *mesh,GLMaterialA* material):Node() {
    _mesh = mesh;
    _material = material;
}

GLMesh *Model::getMesh() const {
    return _mesh;
}

GLMaterialA *Model::getMaterial() const {
    return _material;
}
