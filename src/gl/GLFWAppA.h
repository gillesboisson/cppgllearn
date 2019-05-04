//
// Created by Gilles Boisson on 2019-04-30.
//

#ifndef CPP_LEARN_GLFWAPPA_H
#define CPP_LEARN_GLFWAPPA_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

#include <thread>
#include <chrono>

#include "../gl/GLHelper.h"


class GLFWAppA {
protected:
    uint16_t _fps;
    bool _active = false;
    GLFWwindow* _window;
    int _windowWidth;
    int _windowHeight;
    const char* _windowTitle;
    double _lastFrameTime;

    static void framebuffer_size_callback(GLFWwindow *window, int width, int height);

public:




    GLFWAppA(int width,int height,const char* title,uint16_t fps = 60);

    uint16_t getFps() const;

    bool isActive() const;

    GLFWwindow *getWindow() const;

    float getWindowWidth() const;

    float getWindowHeight() const;

    const char *getWindowTitle() const;




    bool start();
    void quit();


    virtual void beforeStart();
    virtual void afterStart();
    virtual void update(double frameInterval,float frameSpeed) = 0;
    virtual void beforeQuit();




};


#endif //CPP_LEARN_GLFWAPPA_H