//
// Created by Gilles Boisson on 2019-04-27.
//

#ifndef CPP_LEARN_GLMESH_H
#define CPP_LEARN_GLMESH_H

#include "GLVao.h"
#include "tiny_gltf.h"

class GLMesh {
protected:
    GLVao* _vao;
    uint32_t _nbIndices;
    GLenum _renderType = GL_TRIANGLES;

public:

    ~GLMesh();

    void dispose(bool disposeVao = true);

    explicit GLMesh(uint32_t nbIndices,GLenum renderType = GL_STATIC_DRAW);
    explicit GLMesh(uint32_t nbPoints,GLVao* vao,GLenum renderType = GL_STATIC_DRAW);

    GLenum getRenderType();

    void draw(uint32_t nbIndices);
    void draw();


    uint32_t getNbPoints() const;
    GLVao *getVao() const;

};



#endif //CPP_LEARN_GLMESH_H
