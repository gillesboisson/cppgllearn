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
    texture.LoadTexture("./grass_2.png");
}



void LearnGLApp::initGeometry() {

    auto ratio = (float)SCR_WIDTH / (float)SCR_HEIGHT;
    cam = Camera::camPerspective(glm::radians(45.0f), ratio, 0.001f, 100.0f);

    cam.trs.position(0, 0, -8.0f);

    node.trs.position(1.f,1.f,1.f);
    node.trs.scale(0.01f);
    node.updateGeometry();

    //cam.trs.lookAt(node.trs.getPosition(),vec3(0.f,1.f,0.f));


}

void LearnGLApp::setupShader() {
    std::cout << "SetupShader\n";

    if(simpleShader.init("./assets/simple_shader.vert", "./assets/simple_shader.frag")){
        simpleShader.useProgram();
        transformLoc = simpleShader.getUniformLocation("transform");
        transformRotLoc = simpleShader.getUniformLocation("transformRot");
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


    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        angle+= 0.03f;

        node.trs.eulerAngle(0.0f, angle, 0.0f);
//
        node.updateGeometry();

        processInput(window);

        double mousePosX, mousePosY;
        glfwGetCursorPos(window, &mousePosX, &mousePosY);

        int rightClick = glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_RIGHT);

        if(rightClick == GLFW_PRESS) {
            cam.trs.rotateAroundAxis((mousePosX - _lastMousePosX ) / -100.f,glm::vec3(0,1,0));
            cam.trs.rotateAroundAxis((mousePosY - _lastMousePosY ) / -100.f,glm::vec3(1,0,0));
        }

        glm::mat4 camRotMat =  cam.trs.getRotMat();
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

        cam.trs.translate(translateV.x,translateV.y,translateV.z);

        _lastMousePosX = mousePosX;
        _lastMousePosY = mousePosY;

        cam.updateGeometry();



        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        cam.updateGeometry();

        texture.Bind();
        cam.updateMVP(&mvp, node.getWorldMat());
        simpleShader.uniformMat4v(transformLoc, mvp);
        simpleShader.uniformMat4v(transformRotLoc, node.trs.getRotMat());

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
