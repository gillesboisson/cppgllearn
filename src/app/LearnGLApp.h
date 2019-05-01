//
// Created by Gilles Boisson on 2019-04-27.
//

#ifndef CPP_LEARN_LEARNGLAPP_H
#define CPP_LEARN_LEARNGLAPP_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

#include "../gl/GLHelper.h"
#include "../gl/GLVao.h"
#include "../gl/GLShader.h"
#include "../gl/GLTexture.h"
#include "../gl/GLTransform.h"
#include "../gl/GLMesh.h"
#include "../3d/Node.h"
#include "../3d/Camera.h"


//const uint32_t points = 4;

//// Each poin has three values ( x, y, z)
//const uint32_t floatsPerPoint = 3;
//const uint32_t floatPerTP = 2;
//
//// Each color has 4 values ( red, green, blue, alpha )
//const uint32_t floatsPerColor = 4;

class LearnGLApp {

    void processInput(GLFWwindow *window);
    void initTexture();
    void initGeometry();
    void setupShader();
    void setupNodes();
    void loadDuck();

    const unsigned int SCR_WIDTH = 512;
    const unsigned int SCR_HEIGHT = 512;

    double _lastMousePosX;
    double _lastMousePosY;

    std::vector<uint32_t> vbos;
    std::vector<GLVao> vaos;
    std::vector<GLMesh> meshes;

    GLShader simpleShader;

    float angle;
    double targetFrameRate = 60;
    double frame_start;

    GLTexture texture;
    GLTransform glTransform;


    Node node;
    glm::mat4 mvp;
    Camera cam;

public:
    int Start();


};


#endif //CPP_LEARN_LEARNGLAPP_H
