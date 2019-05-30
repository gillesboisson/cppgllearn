//
// Created by Gilles Boisson on 2019-05-18.
//

#ifndef CPP_LEARN_GLRENDERER_H
#define CPP_LEARN_GLRENDERER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "GLTransformFeedbackShader.h"
#include "GLShader.h"
#include "GLVao.h"
#include "GLMaterialA.h"
#include <glm/glm.hpp>

#include "../core/Camera.h"
#include "../3d/Model.h"
#include "../utils/FBStack.h"

#include <map>

class GLRenderer {
protected:
    GLVao* _currentVao{};
    GLShader* _currentShader{};
    GLMaterialA* _currentMaterial{};


    bool _faceCullingEnabled{};
    bool _depthTestEnabled{};

    bool _rasterDiscarded{};
    glm::vec4 _clearColor{};



    std::map<const char*,GLShader*> _shaders{};

    GLint _viewportX;
    GLint _viewportY;
    GLsizei _viewportWidth;
    GLsizei _viewportHeight;

    void bindShader(GLShader* shader);
    void bindVao(GLVao *vao);
    void bindMaterial(GLMaterialA *material);

    FBStack* _fbStack;

public:

    GLRenderer();
    GLRenderer(GLsizei width,GLsizei height);
    GLRenderer(GLint vpX,GLint vpY,GLsizei width,GLsizei height);
    ~GLRenderer();

    GLVao *getCurrentVao() const;

    GLShader *getCurrentShader() const;

    bool isFaceCullingEnabled() const;
    bool isFragmentDiscarded() const;
    bool isDepthTestEnabled() const;


    void setFaceCullingEnabled(bool val);
    void setRasterDiscarded(bool val);
    void setDepthTestEnabled(bool val);


    GLShader* registerShader(const char* name,GLShader* shader);
    void deleteShader(const char *name);

    void setClearColor(glm::vec4 color);
    void clear() const;
    void reset();

    void renderMesh(GLMesh *mesh, GLMaterialA *material);


    void renderModel(Model *model, Camera *camera);


    void prepare(GLMaterialA* material, GLVao* vao,Camera *camera);

    GLShader *getShader(const char *name) const;

    void resize(GLsizei width,GLsizei height);

    void resetViewport() const;

    void prepareTransformFeedbackPass(GLTransformFeedbackShader *tfShader, GLVao *vao);

    void doTransformFeedbackPass(GLTransformFeedbackShader *tfShader, GLVao *vao, GLBuffer *outputBuffer,
                                 GLsizei count);

    void pushFrameBuffer(GLFrameBuffer *fbo);

    void swapFrameBuffer(GLFrameBuffer *fbo);

    GLFrameBuffer *popFrameBuffer();

    void prepare(GLMaterialA *material, GLVao *vao);
};


#endif //CPP_LEARN_GLRENDERER_H
