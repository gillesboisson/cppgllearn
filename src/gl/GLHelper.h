

#ifndef GL_HELPER
#define GL_HELPER

#include <glad/glad.h>
#include <string>
#include <iostream>


std::string GLErrorMessage(GLenum error);
void GLThrowErrors(const std::string &errorMessage = "");
void GLPrintErrors(const std::string &errorMessage = "");
GLuint GLGenRenderBuffer(GLenum bufferType,int width,int height);

#endif
