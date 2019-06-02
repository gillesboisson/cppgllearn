//
// Created by Gilles Boisson on 2019-05-29.
//

#ifndef CPP_LEARN_SPRITEMATERIAL_H
#define CPP_LEARN_SPRITEMATERIAL_H

#include "../../gl/GLMaterialA.h"
#include "../../gl/GLRenderer.h"

class SpriteMaterial: public GLMaterialA{
protected:
    GLTexture **_texture;
    uint16_t _nbTexture;
    void init(uint16_t nbTexture);

public:

    explicit SpriteMaterial(GLRenderer* renderer,uint16_t nbTexture);
    explicit SpriteMaterial(GLShader* shader,uint16_t nbTexture);
    ~SpriteMaterial();

    void bindModelUniforms(glm::mat4 *worldMat, Camera *camera) override;
    void bindCommonUniforms() override;

    GLTexture *getTexture(uint32_t textureIndex = 0) const;
    void setTexture(GLTexture *texture,uint32_t textureIndex = 0);


};


#endif //CPP_LEARN_SPRITEMATERIAL_H
