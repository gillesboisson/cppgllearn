//
// Created by Gilles Boisson on 2019-05-05.
//

#include "GLFrameBuffer.h"
#include "GLHelper.h"

void GLFrameBuffer::init(int width,int height) {
    glGenFramebuffers(1, &_fbo);
    _width = width;
    _height = height;

}

void GLFrameBuffer::bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
}

void GLFrameBuffer::bindViewport() {
    glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
    glViewport(0,0,_width,_height);
}

void GLFrameBuffer::dispose() {

    glDeleteFramebuffers(1,&_fbo);
}

void GLFrameBuffer::attachTexture(const GLTexture &texture,GLenum attachment) {
    glBindFramebuffer(GL_FRAMEBUFFER,_fbo);
    glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, texture.getTarget(), texture.getGLId(), 0);
    glBindFramebuffer(GL_FRAMEBUFFER,0);
#ifdef DEBUG_GL
    GLPrintErrors("GLFrameBufferA :: attachTexture");
#endif
}

void GLFrameBuffer::attachColorTexture(const GLTexture &texture, uint16_t attachmentIndex) {
    attachTexture(texture,GL_COLOR_ATTACHMENT0+attachmentIndex);

}

GLTexture *GLFrameBuffer::attachNewTexture(GLenum format, GLenum target, GLenum type,GLenum attachment, int width, int height) {
    auto texture = new GLTexture();

    texture->initEmptyTexture2d(format, target, type, width, height);
    attachTexture(*texture,attachment);

    return texture;
}

GLTexture *GLFrameBuffer::attachNewTexture(GLenum format, GLenum target,GLenum attachment, GLenum type) {
    return attachNewTexture(format,target,type,attachment,_width,_height);
}

GLTexture *GLFrameBuffer::attachNewColorTexture(GLenum format, GLenum target, GLenum type, int width, int height,
                                                 uint16_t attachmentIndex) {
    return attachNewTexture(format,target,type,GL_COLOR_ATTACHMENT0+attachmentIndex,width,height);

}

GLTexture *GLFrameBuffer::attachNewColorTexture(GLenum format, GLenum target, GLenum type, uint16_t attachmentIndex) {
    return attachNewTexture(format,target,type,GL_COLOR_ATTACHMENT0+attachmentIndex,_width,_height);
}

void GLFrameBuffer::attachRenderBuffer(GLuint rbo,GLenum attachment){
    glBindFramebuffer(GL_FRAMEBUFFER,_fbo);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, attachment, GL_RENDERBUFFER, rbo);
    glBindFramebuffer(GL_FRAMEBUFFER,0);

}

GLuint GLFrameBuffer::attachNewRenderBuffer(GLenum bufferType,GLenum attachment,int width,int height){
    GLuint rbo = GLGenRenderBuffer(bufferType,width,height);
    attachRenderBuffer(rbo,attachment);
    return rbo;
}

GLuint GLFrameBuffer::attachNewRenderBuffer(GLenum bufferType,GLenum attachment){
    return attachNewRenderBuffer(bufferType,attachment,_width,_height);
}

GLuint GLFrameBuffer::attachNewDepthRenderBuffer(){
    return attachNewRenderBuffer(GL_DEPTH_COMPONENT24,GL_DEPTH_ATTACHMENT,_width,_height);
}

GLuint GLFrameBuffer::getGLId() const {
    return _fbo;
}

int GLFrameBuffer::getWidth() const {
    return _width;
}

int GLFrameBuffer::getHeight() const {
    return _height;
}
