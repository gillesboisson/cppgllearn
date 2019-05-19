//
// Created by Gilles Boisson on 2019-04-30.
//

#ifndef CPP_LEARN_TUTOGLAPP_H
#define CPP_LEARN_TUTOGLAPP_H


#include "../gl/GLFWAppA.h"
#include "../3d/Camera.h"
#include "../3d/Node.h"
#include "../gl/GLShader.h"
#include "../gl/GLTransformFeedbackShader.h"
#include "../gl/GLBatchA.h"
#include "../gl/GLBuffer.h"
#include "../gl/GLFrameBuffer.h"
#include "../3d/GLTFLoader.h"
#include "../3d/Model.h"
#include "../gl/GLRenderer.h"
#include "SimpleLightMaterial.h"
#include "SimpleColorMaterial.h"


class TutoGLApp : public GLFWAppA {
protected:
    Camera _cam;
    Model* _duck;
    Model* _quad;


    glm::mat4 _mvp;


    std::vector<GLBuffer*> _vbos;

    GLBuffer* lightB;
    PointLightU light;
    GLBuffer* transformB;
//    TransformUB transformub;


    void setupGeometry();

    void setupShader();

    void loadDuck();
    float _lastMousePosX;
    float _lastMousePosY;

    SimpleColorMaterial *_quadMat;
    GLMesh *_quadMesh;

public:
    TutoGLApp();

    virtual void afterStart() override;
    virtual void beforeQuit() override;

    virtual void update(double frameInterval,float frameSpeed) override;


    void setupUniforms();

    void initRenderer() override ;


    GLBuffer *vPBuffer;





};


#endif //CPP_LEARN_TUTOGLAPP_H
