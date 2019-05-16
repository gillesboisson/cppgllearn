//
// Created by Gilles Boisson on 2019-05-16.
//

#include "GLTransformFeedbackShader.h"

void GLTransformFeedbackShader::initTransformFeedback(){
    deleteElements();
    _programId = glCreateProgram();
    _shaderType = TransformFeedback;
}

bool GLTransformFeedbackShader::init(const std::string &vertProgramPath, GLsizei count, const char **varying,
                                     GLenum bufferMode) {
    initTransformFeedback();

    if (loadVertexShader(vertProgramPath)){
        glTransformFeedbackVaryings(_programId,count,varying,bufferMode);
        return linkShaders();
    }

    deleteElements();
    return false;
}

bool GLTransformFeedbackShader::init(const std::string &vertProgramPath, const std::string &geomProgramPath,
                                     GLsizei count, const char **varying, GLenum bufferMode) {

    initTransformFeedback();

    if (loadVertexShader(vertProgramPath) && loadGeometryShader(geomProgramPath)){
        glTransformFeedbackVaryings(_programId,count,varying,bufferMode);
        return linkShaders();;
    }

    deleteElements();
    return false;
}

void GLTransformFeedbackShader::doPass(GLBuffer *outputBuffer,GLenum renderType,GLsizei start,GLsizei count) const {
    useProgram();
    glEnable(GL_RASTERIZER_DISCARD);
    outputBuffer->bindBase(GL_TRANSFORM_FEEDBACK_BUFFER,0);
    glBeginTransformFeedback(renderType);
    glDrawArrays(renderType,start,count);
    glEndTransformFeedback();
    glDisable(GL_RASTERIZER_DISCARD);
}

void GLTransformFeedbackShader::doPass(GLBuffer *outputBuffer,GLenum renderType,GLsizei count) const {
    doPass(outputBuffer,renderType,0,count);
}

void GLTransformFeedbackShader::doPass(GLBuffer *outputBuffer,GLsizei count) const {
    doPass(outputBuffer,GL_POINTS,0,count);
}

void GLTransformFeedbackShader::doPass(GLBuffer *outputBuffer,GLsizei start,GLsizei count) const {
    doPass(outputBuffer,GL_POINTS,start,count);
}