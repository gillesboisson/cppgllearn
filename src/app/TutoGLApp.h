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


class TutoGLApp : public GLFWAppA {
protected:
    Camera _cam;
    Model* _duck;

    glm::mat4 _mvp;

    GLShader _simpleShader;
    std::vector<GLBuffer*> _vbos;

    GLBuffer* lightB;
    PointLightU light;
    GLBuffer* transformB;
//    TransformUB transformub;

    GLRenderer* _renderer;

    void setupGeometry();

    void setupShader();

    void loadDuck();
    float _lastMousePosX;
    float _lastMousePosY;

public:
    TutoGLApp();

    virtual void afterStart() override;
    virtual void beforeQuit() override;

    virtual void update(double frameInterval,float frameSpeed) override;


    void setupUniforms();




    GLBuffer *vPBuffer;

    void setupRenderer();
};


#endif //CPP_LEARN_TUTOGLAPP_H
