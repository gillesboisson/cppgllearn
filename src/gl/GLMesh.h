//
// Created by Gilles Boisson on 2019-04-27.
//

#ifndef CPP_LEARN_GLMESH_H
#define CPP_LEARN_GLMESH_H

#include "GLVao.h"
#include "tiny_gltf.h"

class GLMesh {
protected:
    GLVao _vao;
    uint32_t _nbPoints;
public:
    uint32_t getNbPoints() const;

public:
    const GLVao &getVao() const;

public:


protected:
    GLenum _renderType = GL_TRIANGLES;

public:
    GLMesh();
    explicit GLMesh(uint32_t nbPoints,GLVao vao);
    explicit GLMesh(uint32_t nbPoints,GLVao vao,GLenum renderType);

    GLenum getRenderType();

    void draw(uint32_t nbPoints);
    void draw();
};



#endif //CPP_LEARN_GLMESH_H
