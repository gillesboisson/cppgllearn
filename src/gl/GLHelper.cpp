#include "GLHelper.h"


void GLUploadBuffer(GLuint vbo,GLsizeiptr size,const GLvoid* data,GLenum target,GLenum usage){
    glBindBuffer(target, vbo);
	glBufferData(target, size, data, usage);
}