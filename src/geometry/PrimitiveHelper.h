//
// Created by Gilles Boisson on 2019-05-05.
//

#ifndef CPP_LEARN_PRIMITIVEHELPER_H
#define CPP_LEARN_PRIMITIVEHELPER_H

#include "../gl/GLMesh.h"

class PrimitiveHelper {
    static const float quadMesh3DPosition[12];
    static const float quadMeshPosition[8];
    static const float cubePosition[24];


    static const uint16_t cubeTriangleIndices[36];
    static const GLushort cubeTriangleInsideIndices[36];

    static const GLushort cubeLineIndices[24];


public:
    static GLMesh *createCubeTriangleMesh();
    static GLMesh *createCubeLineMesh();
    static GLMesh *createSkyboxTriangleMesh();



    static const float *getCubePosition();

    static const uint16_t *getCubeTriangleIndices();

    static const uint16_t *getCubeLineIndices();
    static const float *getQuadMesh3DPosition();
    static const float *getQuadMeshPosition();

    static GLMesh *createQuadMesh3D();
};



#endif //CPP_LEARN_PRIMITIVEHELPER_H
