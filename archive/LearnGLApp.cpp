//
// Created by Gilles Boisson on 2019-04-27.
//

#include "LearnGLApp.h"
#include <thread>
#include <chrono>

#include "../3d/GLTFLoader.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}


void LearnGLApp::processInput(GLFWwindow *window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void LearnGLApp::initTexture() {
    texture.loadTexture2d("./grass_2.png");
}



void LearnGLApp::initGeometry() {

    auto ratio = (float)SCR_WIDTH / (float)SCR_HEIGHT;
    cam = Camera::camPerspective(glm::radians(45.0f), ratio, 0.001f, 100.0f);

    cam.transform.position(0, 0, -8.0f);
//    node.transform.position(1.f,1.f,1.f);
    node.transform.scale(0.01f);
    node.updateGeometry();

    //cam.trs.lookAt(node.trs.getPosition(),vec3(0.f,1.f,0.f));


}

void LearnGLApp::setupShader() {
    std::cout << "SetupShader\n";

    if(simpleShader.init("./assets/simple_light_shader.vert", "./assets/simple_light_shader.frag")){
        simpleShader.useProgram();
        glBindBuffer(GL_ARRAY_BUFFER, 0);


    }
}

void LearnGLApp::setupNodes() {
    auto subNode = new Node();
    node.addChild(subNode);
    node.addChild(new Node());
    node.removeChild(subNode);
}

int LearnGLApp::Start() {
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    initGeometry();
    setupShader();
    initTexture();
    setupNodes();
    loadDuck();

    uint32_t colorL = simpleShader.getUniformLocation("color");
    uint32_t diffuseColorL = simpleShader.getUniformLocation("material.diffuse");
    uint32_t ambientColorL = simpleShader.getUniformLocation("material.ambient");
    uint32_t specularColorL = simpleShader.getUniformLocation("material.specular");
    uint32_t shininessL = simpleShader.getUniformLocation("material.shininess");
    uint32_t lightPositionL = simpleShader.getUniformLocation("lightPosition");
    uint32_t camPosL = simpleShader.getUniformLocation("camPosition");


    uint32_t mvpL   = simpleShader.getUniformLocation("transform.mvp");
    uint32_t mL     = simpleShader.getUniformLocation("transform.m");
    uint32_t rotL   = simpleShader.getUniformLocation("transform.rot");



    glm::vec4 color(1.0);
    glm::vec3 diffuseColor(1.0);
    glm::vec3 ambientColor(0.1);
    glm::vec3 specularColor(0.3);
    glm::vec3 lightPosition(3.0,3.0,3.0);
    float shininess = 32.f;


    simpleShader.setUniformVec4v(colorL,color);
    simpleShader.setUniformVec3v(diffuseColorL,diffuseColor);
    simpleShader.setUniformVec3v(ambientColorL,ambientColor);
    simpleShader.setUniformVec3v(specularColorL,specularColor);
    simpleShader.setUniformVec3v(lightPositionL,lightPosition);
    simpleShader.setUniformFloat(shininessL,shininess);





    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        angle+= 0.03f;

        node.transform.eulerAngle(0.0f, angle, 0.0f);
//
        node.updateGeometry();

        processInput(window);

        double mousePosX, mousePosY;
        glfwGetCursorPos(window, &mousePosX, &mousePosY);

        int rightClick = glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_RIGHT);

        if(rightClick == GLFW_PRESS) {
            cam.transform.rotateAroundAxis((mousePosX - _lastMousePosX ) / -100.f,glm::vec3(0,1,0));
            cam.transform.rotateAroundAxis((mousePosY - _lastMousePosY ) / -100.f,glm::vec3(1,0,0));
        }

        glm::mat4 camRotMat =  cam.transform.getRotMat();
        glm::vec4 translateV = glm::vec4(0.0,0.0,0.0,1.0);
        if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
            translateV.x += 0.1f;
        }
        if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
            translateV.x -= 0.1f;
        }

        if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
            translateV.z += 0.1f;
        }
        if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
            translateV.z -= 0.1f;
        }

        translateV = camRotMat * translateV;

        cam.transform.translate(translateV.x,translateV.y,translateV.z);

        _lastMousePosX = mousePosX;
        _lastMousePosY = mousePosY;

        cam.updateGeometry();

        simpleShader.setUniformVec3v(camPosL,cam.transform.getPosition());


        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        cam.updateGeometry();

        texture.bind();
        glm::mat4 *modelM = node.getWorldMat();
        const glm::mat4 &rotM = node.transform.getRotMat();

        cam.updateMVP(&mvp, modelM);
        simpleShader.setUniformMat4v(mvpL, mvp);
        simpleShader.setUniformMat4v(mL, *modelM);
        simpleShader.setUniformMat4v(rotL, rotM);

        meshes[0].draw();

        glfwSwapBuffers(window);

        double t = glfwGetTime() / 1000;
        auto idleT = (long long int)(15.99 - (t - frame_start));

        if(idleT > 0){
            std::this_thread::sleep_for(std::chrono::milliseconds(idleT));
        }

        frame_start = t;

        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();

    return 0;
}



void LearnGLApp::loadDuck() {
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

    vbos = GLTFLoader::loadBufferViews(model.buffers, model.bufferViews);
    meshes = GLTFLoader::loadMeshes(vbos, model.bufferViews, model.accessors, model.meshes[0].primitives);
}
