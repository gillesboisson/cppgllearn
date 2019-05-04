

#ifndef GL_HELPER
#define GL_HELPER

#include <glad/glad.h>
#include <string>
#include <iostream>


void GLUploadBuffer(GLuint vbo,GLsizeiptr size,const GLvoid* data,GLenum target = GL_ARRAY_BUFFER,GLenum usage = GL_STATIC_DRAW);
std::string GLErrorMessage(GLenum error);
void GLThrowErrors();
void GLPrintErrors();

#endif