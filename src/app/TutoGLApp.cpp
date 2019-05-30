//
// Created by Gilles Boisson on 2019-04-30.
//

#include "TutoGLApp.h"
#include "../geometry/PrimitiveHelper.h"


TutoGLApp::TutoGLApp():GLFWAppA(512,512,"Open GL Tutos",60) {
    _mvp = glm::mat4(1.0);

}

void TutoGLApp::setupGeometry() {
    auto ratio = (float)_windowWidth / (float)_windowHeight;
    _cam = Camera::camPerspective(glm::radians(45.0f), ratio, 0.001f, 100.0f);
    _cam.transform.position(0, 0, -8.0f);

}

void TutoGLApp::setupShader() {
    std::cout << "SetupShader\n";


    auto lightS =_renderer->registerShader(
        "simpleLight",
        new GLShader("./assets/shaders/simple_light_shader.vert", "./assets/shaders/simple_light_shader.frag")
        );

    auto colorS = _renderer->registerShader(
        "fixColor",
        new GLShader("./assets/shaders/fix_color.vert", "./assets/shaders/fix_color.frag")
        );

    auto blinnPhongShader = _renderer->registerShader(
        "blinnPhong",
        new GLShader("./assets/shaders/blinn_phong.vert", "./assets/shaders/blinn_phong.frag")
    );


    lightS->useProgram();

    lightB = new GLBuffer(GL_UNIFORM_BUFFER,GL_STATIC_DRAW,sizeof(PointLightU));
    lightB->bindBase(1);


    transformB = new GLBuffer(GL_UNIFORM_BUFFER,GL_DYNAMIC_DRAW,sizeof(TransformU));
    transformB->bindBase(2);

    glm::vec4 color(1.0);

    lightS->bindUniformBlockIndex("TransformUB",2);
    lightS->bindUniformBlockIndex("Light",1);
    lightS->setUniformVec4v("color",color);

    blinnPhongShader->useProgram();
    blinnPhongShader->bindUniformBlockIndex("TransformUB",2);
    blinnPhongShader->bindUniformBlockIndex("Light",1);
    blinnPhongShader->setUniformVec4v("color",color);




}

void TutoGLApp::loadDuck() {
    tinygltf::Model model;
    tinygltf::TinyGLTF loader;
    std::string err;
    std::string warn;

    bool ret = loader.LoadASCIIFromFile(&model, &err, &warn, "gltf/duck.json");

    if (!warn.empty()) {
        printf("Warn: %s\n", warn.c_str());
    }

    if (!err.empty()) {
        printf("Err: %s\n", err.c_str());
    }

    if (!ret) {
        printf("Failed to parse glTF\n");
    }

    auto vbos = GLTFLoader::loadBufferViews(model.buffers, model.bufferViews);
    auto meshes = GLTFLoader::loadMeshes(vbos, model.bufferViews, model.accessors, model.meshes[0].primitives);

    auto mat = new SimpleLightMaterial(_renderer,transformB,lightB,&light);

    _duck = new Model(*meshes.data(),mat);
    _duck->transform.scale(0.01);
    _duck->updateGeometry();


    auto quad = PrimitiveHelper::createQuadMesh3D();

    _quadMat = new SimpleColorMaterial(_renderer);
    _quadMat->setColor(glm::vec4(1,1,1,1));
    _quadMesh = PrimitiveHelper::createQuadMesh3D();


}

void TutoGLApp::setupUniforms() {

    light.diffuse = glm::vec3(0.5);
    light.ambient = glm::vec3(0.4);
    light.specular = glm::vec3(0.3);
    light.position = glm::vec3(3.0,3.0,3.0);
    light.shininess = 6.f;

    glm::vec4 color(1.0);
}

void TutoGLApp::afterStart() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    setupGeometry();
    setupShader();
    loadDuck();
    setupUniforms();

}

void TutoGLApp::beforeQuit() {

}

void TutoGLApp::update(double frameInterval,float frameSpeed) {
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    // handle cam nav -------------------------
    double mousePosX, mousePosY;
    glfwGetCursorPos(_window, &mousePosX, &mousePosY);

    int rightClick = glfwGetMouseButton(_window,GLFW_MOUSE_BUTTON_RIGHT);

    if(rightClick == GLFW_PRESS) {
        _cam.transform.rotateAroundAxis((mousePosX - _lastMousePosX ) / -100.f,glm::vec3(0,1,0));
        _cam.transform.rotateAroundAxis((mousePosY - _lastMousePosY ) / -100.f,glm::vec3(1,0,0));
    }

    glm::mat4 camRotMat =  _cam.transform.getRotMat();
    glm::vec4 translateV = glm::vec4(0.0,0.0,0.0,1.0);
    if(glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS){
        translateV.x += 0.1f;
    }
    if(glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS){
        translateV.x -= 0.1f;
    }

    if(glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS){
        translateV.z += 0.1f;
    }
    if(glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS){
        translateV.z -= 0.1f;
    }

    if(glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(_window,true);
    }

    translateV = camRotMat * translateV;

    _cam.transform.translate(translateV.x,translateV.y,translateV.z);

    _lastMousePosX = mousePosX;
    _lastMousePosY = mousePosY;

    _cam.updateGeometry();


    _renderer->clear();
    _renderer->renderModel(_duck,&_cam);
//    _renderer->renderMesh(_quadMesh,_quadMat);


}

void TutoGLApp::initRenderer() {
    GLFWAppA::initRenderer();
    _renderer->setClearColor(glm::vec4(0,0,0,0));
    _renderer->setDepthTestEnabled(true);
    _renderer->setFaceCullingEnabled(true);
}
