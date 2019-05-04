//
// Created by Gilles Boisson on 2019-04-30.
//

#include "GLFWAppA.h"

#include <cmath>


void GLFWAppA::framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}


bool GLFWAppA::start() {
    beforeStart();
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    double timeAfterUpdate, timeExec, timeInterval;

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

    _window = glfwCreateWindow(_windowWidth, _windowHeight, _windowTitle, NULL, NULL);
    if (_window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(_window);
    glfwSetFramebufferSizeCallback(_window, GLFWAppA::framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return false;
    }


    afterStart();

    //    glEnable(GL_DEPTH_TEST);
    //    glClearColor(0.0, 0.0, 0.0, 0.0);
    //    glEnable(GL_CULL_FACE);
    //    glCullFace(GL_BACK);

    _active = true;
    while (!glfwWindowShouldClose(_window)) {

        double time = glfwGetTime() * 1000;

        if (_lastFrameTime != 0) {
            timeInterval = time - _lastFrameTime;
            update(timeInterval, 1000 / timeInterval / _fps);
        }

        glfwSwapBuffers(_window);

        timeAfterUpdate = glfwGetTime() * 1000;
        timeExec = timeAfterUpdate - time;

        long long int idleT = floor(1000 / (double) _fps - timeExec) - 1;

        if (idleT > 0) {
            std::this_thread::sleep_for(std::chrono::milliseconds(idleT));
        }

        _lastFrameTime = time;

        glfwPollEvents();
        _lastFrameTime = time;
        if (!_active) glfwSetWindowShouldClose(_window, true);
    }

    beforeQuit();
    quit();

    return true;


}

uint16_t GLFWAppA::getFps() const {
    return _fps;
}

bool GLFWAppA::isActive() const {
    return _active;
}

GLFWwindow *GLFWAppA::getWindow() const {
    return _window;
}

float GLFWAppA::getWindowWidth() const {
    return _windowWidth;
}

float GLFWAppA::getWindowHeight() const {
    return _windowHeight;
}

const char *GLFWAppA::getWindowTitle() const {
    return _windowTitle;
}

void GLFWAppA::quit() {
    glfwTerminate();
}

void GLFWAppA::beforeStart() {

}

void GLFWAppA::afterStart() {

}

void GLFWAppA::beforeQuit() {

}

GLFWAppA::GLFWAppA(int width, int height, const char *title, uint16_t fps) {
    _windowWidth = width;
    _windowHeight = height;
    _windowTitle = title;
    _fps = fps;
}

