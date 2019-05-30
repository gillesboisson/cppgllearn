//
// Created by Gilles Boisson on 2019-04-30.
//

#include "TutoGLApp.h"
#include "../geometry/PrimitiveHelper.h"
#include "../2d/materials/SpriteShader.h"


TutoGLApp::TutoGLApp():GLFWAppA(512,512,"Open GL Tutos",60) {
//    _mvp = glm::mat4(1.0);

}


void TutoGLApp::afterRendererInit() {

    // setup sprite shader
    SpriteShader::init(_renderer);

    // load atlas
    auto texture = new GLTexture();
    texture->loadTexture2d("assets/textures/test.png");
    _atlas = new TextureAtlas(texture);
    _atlas->load("assets/textures/test.json");


    // init stage
    _stage = new Stage2D(_renderer,_windowWidth,_windowHeight);
    _cam = _stage->getCamera();
    _sprite1 = new Sprite(_atlas->getSubTexture("red-germ.png"));
//    _sprite1->transform.setScale(glm::vec2(2.0,3.0));
    _group1 = new EntityGroup2D();

    _group1->transform.setPosition(glm::vec2(250,250));

    _sprite1->transform.setPosition(glm::vec2(65,65));
    _sprite1->transform.setPivot(glm::vec2(0.5,0.5));

    _angle = 0.f;
//    _sprite1->transform.setRotation(0.3);
    _group1->addChild(_sprite1);
    _stage->addChild(_group1);
}

void TutoGLApp::beforeQuit() {

}

void TutoGLApp::update(double frameInterval,float frameSpeed) {
    _renderer->clear();
    _angle -= 0.01;
    _sprite1->transform.setRotation(_angle);
    _group1->transform.setRotation(-_angle / 2);


    _stage->render();

}

void TutoGLApp::initRenderer() {
    GLFWAppA::initRenderer();
    _renderer->setClearColor(glm::vec4(0,0,0,0));
    _renderer->setDepthTestEnabled(false);
    _renderer->setFaceCullingEnabled(false);
}
