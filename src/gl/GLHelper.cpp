#include "GLHelper.h"


void GLUploadBuffer(GLuint vbo,GLsizeiptr size,const GLvoid* data,GLenum target,GLenum usage){
    glBindBuffer(target, vbo);
	glBufferData(target, size, data, usage);
    glBindBuffer(target, 0);

}


std::string GLErrorMessage(GLenum error){
    std::string errorM;
    std::string message;

    switch (error) {
        case GL_INVALID_ENUM:
            message = "GL_INVALID_ENUM ";
            break;
        case GL_INVALID_VALUE:
            message = "GL_INVALID_VALUE ";
            break;
        case GL_INVALID_OPERATION:
            message = "GL_INVALID_OPERATION ";
            break;
        case GL_STACK_OVERFLOW:
            message = "GL_STACK_OVERFLOW ";
            break;
        case GL_STACK_UNDERFLOW:
            message = "GL_STACK_UNDERFLOW ";
            break;
        case GL_OUT_OF_MEMORY:
            message = "GL_OUT_OF_MEMORY ";
            break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            message = "GL_INVALID_FRAMEBUFFER_OPERATION ";
            break;
        default:
            message = "Unknown error";
            break;
    }

    errorM = "OpenGL error : "+message;

    return errorM;
}

void GLThrowErrors(const std::string &errorMessage) {

    std::string errorM;

    while (auto error = glGetError()) {
        errorM = GLErrorMessage(error)+" :: "+errorMessage;
//        std::cerr << errorM;
        throw std::invalid_argument(errorM);

    }
}

void GLPrintErrors(const std::string &errorMessage) {

    std::string errorM;

    while (auto error = glGetError()) {
        errorM = GLErrorMessage(error)+" :: "+errorMessage;
        std::cout << error << std::endl;

    }

}

GLuint GLGenRenderBuffer(GLenum bufferType,int width,int height){
    GLuint rbo;
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, width, height);
    glBindRenderbuffer(GL_RENDERBUFFER,0);
    return rbo;
}
