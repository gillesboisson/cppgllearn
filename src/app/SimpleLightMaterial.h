//
// Created by Gilles Boisson on 2019-05-18.
//

#ifndef CPP_LEARN_SIMPLELIGHTMATERIAL_H
#define CPP_LEARN_SIMPLELIGHTMATERIAL_H

#include "glm/glm.hpp"
#include "../gl/GLMaterialA.h"
#include "../gl/GLRenderer.h"


struct PointLightU {
    glm::vec3 ambient;uint32_t __s1;
    glm::vec3 diffuse;uint32_t __s2;
    glm::vec3 specular;uint32_t __s3;
    glm::vec3 position;
    float shininess;
};

struct TransformU {
    glm::mat4 mvp;
    glm::mat4 rot;
    glm::mat4 m;
};

class SimpleLightMaterial :public GLMaterialA{
protected:
    GLBuffer* _transformUB;
    GLBuffer* _lightUB;
    PointLightU* _light;
    TransformU _transformU;
    uint32_t _camPosUI;

public:

    SimpleLightMaterial(GLRenderer* renderer,GLBuffer* transformUB,GLBuffer* lightUB,PointLightU* light);
    void bindGeomUniforms(glm::mat4 worldMat, Camera *camera) override;
    void bindMatUniforms() override;


};


#endif //CPP_LEARN_SIMPLELIGHTMATERIAL_H
