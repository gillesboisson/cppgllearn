//
// Created by Gilles Boisson on 2019-04-30.
//

#ifndef CPP_LEARN_TUTOGLAPP_H
#define CPP_LEARN_TUTOGLAPP_H


#include "../gl/GLFWAppA.h"
#include "../3d/Camera.h"
#include "../3d/Node.h"
#include "../gl/GLShader.h"
#include "../gl/GLBatchA.h"
#include "../3d/GLTFLoader.h"

struct WireframeVertex{
    glm::vec3 position;
    glm::vec4 color;
};

class WireframeBatch: public GLBatchA<WireframeVertex>{

protected:
    void complete() override;
    GLVao* createVao() override;

public:
    WireframeBatch();


};

class TutoGLApp : public GLFWAppA {
protected:
    Camera _cam;
    Node _node;
    Node _node2;
    GLShader _simpleShader;
    GLShader _colorShader;
    std::vector<uint32_t> _vbos;
    std::vector<GLMesh> _meshes;

    WireframeBatch _wireframeBatch;

    void setupGeometry();

    void setupShader();

    void loadDuck();
    glm::mat4 _mvp;



    uint32_t _camPosL  ;
    uint32_t _mvpL    ;
    uint32_t _mL      ;
    uint32_t _rotL    ;

    float _angle;
    float _lastMousePosX;
    float _lastMousePosY;

public:
    TutoGLApp();

    virtual void afterStart() override;
    virtual void beforeQuit() override;

    virtual void update(double frameInterval,float frameSpeed) override;


    void setupUniforms();


};


#endif //CPP_LEARN_TUTOGLAPP_H
