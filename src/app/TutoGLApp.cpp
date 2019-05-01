//
// Created by Gilles Boisson on 2019-04-30.
//

#include "TutoGLApp.h"



TutoGLApp::TutoGLApp():GLFWAppA(512,512,"Open GL Tutos",60) {
    _mvp = glm::mat4(1.0);

}




void TutoGLApp::setupGeometry() {
    auto ratio = (float)_windowWidth / (float)_windowHeight;
    _cam = Camera::camPerspective(glm::radians(45.0f), ratio, 0.001f, 100.0f);

    _cam.transform.position(0, 0, -8.0f);
//    node.transform.position(1.f,1.f,1.f);
    _node.transform.scale(0.01f);
    _node.updateGeometry();
}

void TutoGLApp::setupShader() {
    std::cout << "SetupShader\n";

    if(_simpleShader.init("./assets/simple_light_shader.vert", "./assets/simple_light_shader.frag")){
        _simpleShader.useProgram();
        glBindBuffer(GL_ARRAY_BUFFER, 0);


    }
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

    _vbos = GLTFLoader::loadBufferViews(model.buffers, model.bufferViews);
    _meshes = GLTFLoader::loadMeshes(_vbos, model.bufferViews, model.accessors, model.meshes[0].primitives);
}

void TutoGLApp::setupUniforms() {
    uint32_t colorL = _simpleShader.getUniformLocation("color");
    uint32_t diffuseColorL = _simpleShader.getUniformLocation("material.diffuse");
    uint32_t ambientColorL = _simpleShader.getUniformLocation("material.ambient");
    uint32_t specularColorL = _simpleShader.getUniformLocation("material.specular");
    uint32_t shininessL = _simpleShader.getUniformLocation("material.shininess");
    uint32_t lightPositionL = _simpleShader.getUniformLocation("lightPosition");

    _camPosL = _simpleShader.getUniformLocation("camPosition");
    _mvpL   = _simpleShader.getUniformLocation("transform.mvp");
    _mL     = _simpleShader.getUniformLocation("transform.m");
    _rotL   = _simpleShader.getUniformLocation("transform.rot");

    glm::vec4 color(1.0);
    glm::vec3 diffuseColor(1.0);
    glm::vec3 ambientColor(0.1);
    glm::vec3 specularColor(0.3);
    glm::vec3 lightPosition(3.0,3.0,3.0);
    float shininess = 32.f;

    _simpleShader.setUniformVec4v(colorL,color);
    _simpleShader.setUniformVec3v(diffuseColorL,diffuseColor);
    _simpleShader.setUniformVec3v(ambientColorL,ambientColor);
    _simpleShader.setUniformVec3v(specularColorL,specularColor);
    _simpleShader.setUniformVec3v(lightPositionL,lightPosition);
    _simpleShader.setUniformFloat(shininessL,shininess);
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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // update node rotation  -------------------------
    _angle += 0.03f * frameInterval / 16;
    _node.transform.eulerAngle(0.0f, _angle, 0.0f);
    _node.updateGeometry();

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

    translateV = camRotMat * translateV;

    _cam.transform.translate(translateV.x,translateV.y,translateV.z);

    _lastMousePosX = mousePosX;
    _lastMousePosY = mousePosY;

    _cam.updateGeometry();

    // update transform uniform -------------------------

    glm::mat4 *modelM = _node.getWorldMat();
    const glm::mat4 &rotM = _node.transform.getRotMat();

    _cam.updateMVP(&_mvp, modelM);
    _simpleShader.setUniformMat4v(_mvpL, _mvp);
    _simpleShader.setUniformMat4v(_mL, *modelM);
    _simpleShader.setUniformMat4v(_rotL, rotM);
    _simpleShader.setUniformVec3v(_camPosL,_cam.transform.getPosition());

    // draw mesh
    _meshes[0].draw();
}