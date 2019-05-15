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
    _node.transform.scale(0.01f);
    _node2.transform.scale(20);

    _cube = PrimitiveHelper::createSkyboxTriangleMesh();
}

void TutoGLApp::setupShader() {
    std::cout << "SetupShader\n";

    _simpleShader.init("./assets/simple_light_shader.vert", "./assets/simple_light_shader.frag");
    _colorShader.init("./assets/color_shader.vert", "./assets/color_shader.frag");
    _textureShader.init("./assets/texture_shader.vert", "./assets/texture_shader.frag");
    _fixColorShader.init("./assets/fixcolor.vert", "./assets/fixcolor.frag");
    _skyboxShader.init("./assets/skybox.vert","./assets/skybox.frag");
    _cmReflectionShader.init("./assets/cm_reflection.vert","./assets/cm_reflection.frag");

    _testGeom.init("./assets/testgeom.vert","./assets/testgeom.frag","./assets/testgeom.glsl");
    _colorInstancedShader.init("./assets/color_instanced.vert","./assets/color_instanced.frag");

    //_textureTest.loadTexture2d("./assets/grass_2.png");

    const char* varyings[] = {"vPosition"};
    _testTf.initTransformFeedback("./assets/test_tf.vert",1,varyings,GL_INTERLEAVED_ATTRIBS);

    float geomTdata[] = {
        -0.1, -0.1, 0,  1.0,0.0,0.0,1.0,
        0.1, -0.1, 0,   0.0,1.0,0.0,1.0,
        -0.1, 0.1, 0,   0.0,0.0,1.0,1.0,
        0.1, 0.1, 0,    1.0,0.0,1.0,1.0
    };


    float elementPos[] = {
        -0.5, -0.5,
        0.5, -0.5,
        -0.5, 0.5,
        0.5, 0.5
    };

    uint16_t indices[] = {
        0,1,2,
        1,3,2
    };

    auto vBuffer = new GLBuffer(GL_ARRAY_BUFFER,GL_STATIC_DRAW,geomTdata,sizeof(geomTdata));
    vPBuffer = new GLBuffer(GL_ARRAY_BUFFER,GL_STATIC_DRAW,elementPos,sizeof(elementPos));
    auto iBuffer = new GLBuffer(GL_ELEMENT_ARRAY_BUFFER,GL_STATIC_DRAW,indices,sizeof(indices));
    auto attrs = new GLAttribute[3];

    attrs[0].set(GLAttributeLocation::Position,3,GL_FLOAT,vBuffer,7 * sizeof(float),GL_FALSE, 0);
    attrs[1].set(GLAttributeLocation::Color,4,GL_FLOAT,vBuffer,7 * sizeof(float),GL_FALSE, (void*) (3 * sizeof(float)));
    attrs[2].set(GLAttributeLocation::IPosition,2,GL_FLOAT,vPBuffer,2 * sizeof(float),GL_FALSE, nullptr,1);

    _geomTestMesh = new GLMesh(6,GL_TRIANGLES);
    _geomTestMesh->getVao()->init(attrs,3,iBuffer,GL_UNSIGNED_SHORT);


    // transform feedback
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    auto tfAttr = new GLAttribute(GLAttributeLocation::Position,2,GL_FLOAT,vPBuffer,2 * sizeof(float),GL_FALSE,nullptr);
    _tfIn = new GLVao();
    _tfIn->init(tfAttr,1);

    _tfOut = new GLBuffer(GL_ARRAY_BUFFER,GL_STATIC_READ,sizeof(elementPos));






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
    _simpleShader.useProgram();
    uint32_t colorL = _simpleShader.getUniformLocation("color");
//    uint32_t diffuseColorL = _simpleShader.getUniformLocation("pointLight.diffuse");
//    uint32_t ambientColorL = _simpleShader.getUniformLocation("pointLight.ambient");
//    uint32_t specularColorL = _simpleShader.getUniformLocation("pointLight.specular");
//    uint32_t shininessL = _simpleShader.getUniformLocation("pointLight.shininess");
//    uint32_t lightPositionL = _simpleShader.getUniformLocation("lightPosition");

    _camPosL = _simpleShader.getUniformLocation("camPosition");
    _mvpL   = _simpleShader.getUniformLocation("transform.mvp");
    _mL     = _simpleShader.getUniformLocation("transform.m");
    _rotL   = _simpleShader.getUniformLocation("transform.rot");


    light.diffuse = glm::vec3(0.5);
    light.ambient = glm::vec3(0.4);
    light.specular = glm::vec3(0.1);
    light.position = glm::vec3(3.0,3.0,3.0);
    light.shininess = 32.f;

    lightB = new GLBuffer(GL_UNIFORM_BUFFER,GL_STATIC_DRAW,&light,sizeof(light));
    lightB->bindBase(1);
    _simpleShader.bindUniformBlockIndex("Light",1);

    transformB = new GLBuffer(GL_UNIFORM_BUFFER,GL_DYNAMIC_DRAW,&transformub,sizeof(transformub));
    transformB->bindBase(2);
    _simpleShader.bindUniformBlockIndex("TransformUB",2);


    glm::vec4 color(1.0);
//    glm::vec3 diffuseColor(0.5);
//    glm::vec3 ambientColor(0.4);
//    glm::vec3 specularColor(0.1);
//    glm::vec3 lightPosition(3.0,3.0,3.0);
//    float shininess = 32.f;

    _simpleShader.setUniformVec4v(colorL,color);
//    _simpleShader.setUniformVec3v(diffuseColorL,diffuseColor);
//    _simpleShader.setUniformVec3v(ambientColorL,ambientColor);
//    _simpleShader.setUniformVec3v(specularColorL,specularColor);
//    _simpleShader.setUniformVec3v(lightPositionL,lightPosition);
//    _simpleShader.setUniformFloat(shininessL,shininess);
    _textureShader.useProgram();
    auto colorTLocation   = _textureShader.getUniformLocation("colorT");
    glUniform1i(colorTLocation, 0);


    _fixColorShader.useProgram();
    uint32_t colorFL = _fixColorShader.getUniformLocation("color");
    _mvpL2   = _fixColorShader.getUniformLocation("mvp");


    glm::vec4 colorC = glm::vec4(1.0);
    _fixColorShader.setUniformVec4v(colorFL,colorC);
    _mvpL2   = _fixColorShader.getUniformLocation("mvp");

    _skyboxShader.useProgram();
    _mvpL3   = _skyboxShader.getUniformLocation("mvp");
    _rotL3   = _skyboxShader.getUniformLocation("camRot");

    _cmReflectionShader.useProgram();
//    _cmReflectionShader.setUniformVec4v("color",color);
//    _cmReflectionShader.setUniformVec3v("pointLight.diffuse",diffuseColor);
//    _cmReflectionShader.setUniformVec3v("pointLight.ambient",ambientColor);
//    _cmReflectionShader.setUniformVec3v("pointLight.specular",specularColor);
//    _cmReflectionShader.setUniformFloat("pointLight.shininess",shininess);
//    _cmReflectionShader.setUniformVec3v("lightPosition",lightPosition);

}

void TutoGLApp::afterStart() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);


    setupTexture();
    setupFBO();
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

//    _node2.transform.eulerAngle(0.0f, 0.0f, _angle);
    _node2.updateGeometry();

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


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // update transform uniform -------------------------
//    _simpleShader.useProgram();
//    _cubeMapTest.bind();

//    glm::mat4 *modelM = _node.getWorldMat();
//    const glm::mat4 &rotM = _node.transform.getRotMat();

//    _cam.updateMVP(&_mvp, modelM);

//    transformub.m = *_node.getWorldMat();
//    _cam.updateMVP(&transformub.mvp,&transformub.m);
//    transformub.rot = _node.transform.getRotMat();
//    transformB->uploadData();
//
//    _simpleShader.setUniformVec3v("camPosition",_cam.transform.getPosition());
//    _meshes[0]->draw();


//    _skyboxShader.useProgram();
//    glm::mat4 *modelM2 = _node2.getWorldMat();
//    const glm::mat4 &rotM2 = _node2.transform.getRotMat();
//
//    _cam.updateMVP(&_mvp, modelM2);
//    _skyboxShader.setUniformMat4v(_mvpL3, _mvp);
//    _skyboxShader.setUniformMat4v(_rotL3, _cam.transform.getRotMat());
//    _cubeMapTest.bind();
//
//    _cube->draw();


//    _colorInstancedShader.useProgram();
//    _geomTestMesh->drawInstances(4);

//    setupShader();


    _testTf.useProgram();
    glEnable(GL_RASTERIZER_DISCARD);
    _tfOut->bindBase(GL_TRANSFORM_FEEDBACK_BUFFER,0);
    _tfIn->bind();


    glBeginTransformFeedback(GL_POINTS);
//    GLPrintErrors("glBeginTransformFeedback");
    glDrawArrays(GL_POINTS,0,4);
    glEndTransformFeedback();
//    GLPrintErrors("glEndTransformFeedback");
    glFlush();
    GLfloat feedback[5];
    glGetBufferSubData(GL_TRANSFORM_FEEDBACK_BUFFER, 0, sizeof(feedback), feedback);
    glDisable(GL_RASTERIZER_DISCARD);

}

void TutoGLApp::setupFBO() {
    _fbo.init(512,512);
    _fboTexture = _fbo.attachNewColorTexture(GL_RGBA,GL_TEXTURE_2D,GL_UNSIGNED_BYTE);
    //_fbo.attachNewTexture(GL_)

    _fboTexture->activate(0);

    _fbo.attachNewDepthRenderBuffer();


    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
        printf("ERRRRRROR\n");
    }

}

void TutoGLApp::setupTexture() {
    _cubeMapTest.loadTextureCubeMap("assets/siege","tga");
}

// Wireframe batch

void WireframeBatch::complete() {




    auto indT = _vao->getIndType();
    glDrawElements(GL_TRIANGLES,_indicesSize,indT, nullptr);
}

GLVao* WireframeBatch::createVao() {

    auto *attributes = new GLAttribute[2];

    auto stride = sizeof(WireframeVertex);
    auto uvOffset = sizeof(glm::vec3);

    attributes[0].set(GLAttributeLocation::Position, 3, GL_FLOAT, _vbo, stride,GL_FALSE, 0);
    attributes[1].set(GLAttributeLocation::Uv, 2, GL_FLOAT, _vbo, stride, GL_FALSE, (GLvoid *) uvOffset);

    auto vao = new GLVao();

    vao->init(attributes,2,_ibo,GL_UNSIGNED_SHORT);



    return vao;
}



WireframeBatch::WireframeBatch():GLBatchA(1024,1024) {

}
