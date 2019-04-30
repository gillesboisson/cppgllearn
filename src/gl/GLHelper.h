#include <glad/glad.h>

#ifndef GL_HELPER
#define GL_HELPER


void GLUploadBuffer(GLuint vbo,GLsizeiptr size,const GLvoid* data,GLenum target = GL_ARRAY_BUFFER,GLenum usage = GL_STATIC_DRAW);

#endif
