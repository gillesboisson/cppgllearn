//
// Created by Gilles Boisson on 2019-05-18.
//

#ifndef CPP_LEARN_GLMATERIALA_H
#define CPP_LEARN_GLMATERIALA_H


#include "GLShader.h"
#include <glm/glm.hpp>

#include "GLMesh.h"
#include "GLTransform.h"
#include "../3d/Camera.h"

class GLMaterialA {
protected:
    GLShader* _shader;
public:

    GLMaterialA(GLShader* shader = nullptr);

    virtual void render(GLMesh* mesh,GLTransform* transform,Camera* camera);

    virtual void bindGeomUniforms(glm::mat4 worldMat, Camera *camera) = 0;
    virtual void bindMatUniforms() = 0;
    GLShader* getActiveShader() const;

    void render(GLMesh *mesh, glm::mat4 mat, Camera *camera);
};


#endif //CPP_LEARN_GLMATERIALA_H
