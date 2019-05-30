//
// Created by Gilles Boisson on 2019-05-19.
//

#ifndef CPP_LEARN_SIMPLECOLORMATERIAL_H
#define CPP_LEARN_SIMPLECOLORMATERIAL_H


#include "../gl/GLMaterialA.h"
#include "../gl/GLRenderer.h"

class SimpleColorMaterial: public GLMaterialA {
protected:
    glm::vec4 _color{};
    uint32_t _colorU{};
public:
    SimpleColorMaterial(GLRenderer* renderer);
    void bindModelUniforms(glm::mat4 *worldMat, Camera *camera) override;
    void bindCommonUniforms() override;

    const glm::vec4 &getColor() const;

    void setColor(const glm::vec4 &color);
};


#endif //CPP_LEARN_SIMPLECOLORMATERIAL_H
