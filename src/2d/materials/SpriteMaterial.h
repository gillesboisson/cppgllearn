//
// Created by Gilles Boisson on 2019-05-29.
//

#ifndef CPP_LEARN_SPRITEMATERIAL_H
#define CPP_LEARN_SPRITEMATERIAL_H

#include "../../gl/GLMaterialA.h"
#include "../../gl/GLRenderer.h"

class SpriteMaterial: public GLMaterialA{
protected:
    GLTexture *_texture;

public:

    explicit SpriteMaterial(GLRenderer* renderer);
    explicit SpriteMaterial(GLShader* shader);

    void bindModelUniforms(glm::mat4 *worldMat, Camera *camera) override;
    void bindCommonUniforms() override;

    GLTexture *getTexture() const;
    void setTexture(GLTexture *texture);


};


#endif //CPP_LEARN_SPRITEMATERIAL_H
