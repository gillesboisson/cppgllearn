//
// Created by Gilles Boisson on 2019-05-05.
//

#include "PrimitiveHelper.h"
const float PrimitiveHelper::cubePosition[] = {
    -1,-1,1,
    1,-1,1,
    -1,1,1,
    1,1,1,

    -1,-1,-1,
    1,-1,-1,
    -1,1,-1,
    1,1,-1
};

const GLushort PrimitiveHelper::cubeTriangleIndices[] = {
    0,1,2,1,3,2,
    1,5,3,5,7,3,
    5,4,7,4,6,7,
    4,0,6,0,2,6,
    4,5,0,5,1,0,
    2,3,6,3,7,6
};

const GLushort PrimitiveHelper::cubeTriangleInsideIndices[] = {
    1,0,2,1,2,3,
    5,1,3,5,3,7,
    4,5,7,4,7,6,
    0,4,6,0,6,2,
    5,4,0,5,0,1,
    3,2,6,3,6,7
};



const GLushort PrimitiveHelper::cubeLineIndices[] = {
    0,1,1,5,5,4,4,0,
    2,3,3,7,7,6,6,2,
    0,2,1,3,5,7,4,6,
};

GLMesh *PrimitiveHelper::createCubeTriangleMesh() {

//    GLuint vbo;
//    GLuint ibo;
//
//    glGenBuffers(1,&vbo);
//    glGenBuffers(1,&ibo);
//    glBindBuffer(GL_ARRAY_BUFFER, vbo);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(cubePosition), cubePosition,GL_STATIC_DRAW);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeTriangleIndices), cubeTriangleIndices,GL_STATIC_DRAW);

    auto vbo = new GLBuffer(GL_ARRAY_BUFFER,GL_STATIC_DRAW,(GLvoid*) cubePosition,sizeof(cubePosition));
    auto ibo = new GLBuffer(GL_ELEMENT_ARRAY_BUFFER,GL_STATIC_DRAW,(GLvoid*) cubeTriangleIndices,sizeof(cubeTriangleIndices));


    auto attr = new GLAttribute(GLAttributeLocation::Position,3,GL_FLOAT,vbo,sizeof(float) * 3,GL_FALSE, nullptr);
    auto mesh = new GLMesh(36,GL_TRIANGLES);
    mesh->getVao()->init(attr,1,ibo,GL_UNSIGNED_SHORT);


    return mesh;
}

GLMesh *PrimitiveHelper::createSkyboxTriangleMesh() {





//    glGenBuffers(1,&vbo);
//    glGenBuffers(1,&ibo);
//    glBindBuffer(GL_ARRAY_BUFFER, vbo);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(cubePosition), cubePosition,GL_STATIC_DRAW);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeTriangleInsideIndices), cubeTriangleInsideIndices,GL_STATIC_DRAW);



    auto vbo = new GLBuffer(GL_ARRAY_BUFFER,GL_STATIC_DRAW,(GLvoid*) cubePosition,sizeof(cubePosition));
    auto ibo = new GLBuffer(GL_ELEMENT_ARRAY_BUFFER,GL_STATIC_DRAW,(GLvoid*) cubeTriangleInsideIndices,sizeof(cubeTriangleInsideIndices));
//    GLVao vao;

//    auto attr = new GLAttribute(GLAttributeLocation::Position,3,GL_FLOAT,vbo,sizeof(float) * 3,GL_FALSE, nullptr);
//    vao.init(attr,1,ibo,GL_UNSIGNED_SHORT);
//
//    auto mesh = new GLMesh(36,vao);

    auto attr = new GLAttribute(GLAttributeLocation::Position,3,GL_FLOAT,vbo,sizeof(float) * 3,GL_FALSE, nullptr);
    auto mesh = new GLMesh(36,GL_TRIANGLES);
    mesh->getVao()->init(attr,1,ibo,GL_UNSIGNED_SHORT);


    return mesh;
}

GLMesh *PrimitiveHelper::createCubeLineMesh() {

//    GLuint vbo;
//    GLuint ibo;
//
//    glGenBuffers(1,&vbo);
//    glGenBuffers(1,&ibo);
//    glBindBuffer(GL_ARRAY_BUFFER, vbo);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(cubePosition), cubePosition,GL_STATIC_DRAW);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeLineIndices), cubeLineIndices,GL_STATIC_DRAW);

    auto vbo = new GLBuffer(GL_ARRAY_BUFFER,GL_STATIC_DRAW,(GLvoid*) cubePosition,sizeof(cubePosition));
    auto ibo = new GLBuffer(GL_ELEMENT_ARRAY_BUFFER,GL_STATIC_DRAW,(GLvoid*) cubeLineIndices,sizeof(cubeLineIndices));

//    GLVao vao;
//    auto attr = new GLAttribute(GLAttributeLocation::Position,3,GL_FLOAT,vbo,sizeof(float) * 3,GL_FALSE, nullptr);
//    vao.init(attr,1,ibo,GL_UNSIGNED_SHORT);

     auto attr = new GLAttribute(GLAttributeLocation::Position,3,GL_FLOAT,vbo,sizeof(float) * 3,GL_FALSE, nullptr);
    auto mesh = new GLMesh(36,GL_LINES);
    mesh->getVao()->init(attr,1,ibo,GL_UNSIGNED_SHORT);

//    auto mesh = new GLMesh(24,vao,GL_LINES);

    return mesh;
}

const float *PrimitiveHelper::getCubePosition() {
    return cubePosition;
}

const uint16_t *PrimitiveHelper::getCubeTriangleIndices() {
    return cubeTriangleIndices;
}

const uint16_t *PrimitiveHelper::getCubeLineIndices() {
    return cubeLineIndices;
}
