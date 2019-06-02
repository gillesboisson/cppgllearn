//
// Created by Gilles Boisson on 2019-04-30.
//

#include "TutoGLApp.h"
#include "../geometry/PrimitiveHelper.h"
#include "../2d/materials/SpriteShader.h"


TutoGLApp::TutoGLApp():GLFWAppA(512,512,"Open GL Tutos",30) {
//    _mvp = glm::mat4(1.0);

}


void TutoGLApp::afterRendererInit() {

    // setup sprite shader
    SpriteShader::init(_renderer);

    // load atlas
    auto texture = new GLTexture();
    texture->loadTexture2d("../content/textures/test2.png");
    _atlas = new TextureAtlas(texture);
    _atlas->load("../content/textures/test2.json");


    // init stage
    _stage = new Stage2D(_renderer,_windowWidth,_windowHeight);
    _cam = _stage->getCamera();
    _sprite1 = new Sprite(_atlas->getSubTexture("radar-green.png"));
    _sprite2 = new Sprite(_atlas->getSubTexture("radar-green.png"));
    _group1 = new EntityGroup2D();



    std::vector<SubTexture*> textures;

    textures.push_back(_atlas->getSubTexture("radar-green.png"));
    textures.push_back(_atlas->getSubTexture("radar-blue.png"));
    textures.push_back(_atlas->getSubTexture("radar-red.png"));

    auto gridData = new uint16_t[81]{
        1,1,1,1,1,1,1,1,1,
        1,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,1,
        1,0,0,2,2,2,0,0,1,
        1,0,0,2,2,2,0,0,1,
        1,0,0,2,2,2,0,0,1,
        1,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,1,
        1,1,1,1,1,1,1,1,1
        };

    _grid           = new TileGrid(9,9,gridData,textures,_cam);





    _sprite1->transform.setPosition(glm::vec2(10,10));
    _sprite2->transform.setPosition(glm::vec2(20,20));
    _sprite2->setScale(2);



    _group1->setFastTransform(true);
    _group1->setPosition(20,30);



    _angle = 0.f;
    _group1->addChild(_sprite1);
    _group1->addChild(_sprite2);
//    _stage->addChild(_group1);
    _stage->addChild(_grid);
}

void TutoGLApp::beforeQuit() {

}

void TutoGLApp::update(double frameInterval,float frameSpeed) {
    _renderer->clear();
    _angle -= 0.01;
//    _sprite1->transform.setRotation(_angle);
//    _sprite2->transform.setRotation(_angle);
//    _group1->transform.setRotation(-_angle / 2);


    auto camRect = _cam->getRectPtr();

    auto camPos = camRect->getPosition();


    if(glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS){
        camPos.x -= 3;
    }
    if(glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS){
        camPos.x += 3;
    }

    if(glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS){
        camPos.y -= 3;
    }
    if(glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS){
        camPos.y += 3;
    }

    camRect->setPosition(camPos);


    if(glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(_window,true);
    }

    _stage->render();

}

void TutoGLApp::initRenderer() {
    GLFWAppA::initRenderer();
    _renderer->setClearColor(glm::vec4(0,0,0,0));
    _renderer->setDepthTestEnabled(false);
    _renderer->setFaceCullingEnabled(false);
    _renderer->setAlphaBlendingEnabled(true);
}
