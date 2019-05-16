//
// Created by Gilles Boisson on 2019-05-16.
//

#ifndef CPP_LEARN_GLTRANSFORMFEEDBACKSHADER_H
#define CPP_LEARN_GLTRANSFORMFEEDBACKSHADER_H


#include "GLVao.h"
#include "GLShader.h"

class GLTransformFeedbackShader: public GLShader {

protected:

    GLShader* _shader;
    void initTransformFeedback();



public:




    bool init(const std::string &vertProgramPath, GLsizei count, const char **varying, GLenum bufferMode);

    //    void transformFeedbackVaryings(GLsizei count, const char **varying, GLenum bufferMode);
    bool init(const std::string &vertProgramPath, const std::string &geomProgramPath, GLsizei count,
              const char **varying, GLenum bufferMode);

    void doPass(GLBuffer *outputBuffer, GLenum renderType, GLsizei start, GLsizei count) const;

    void doPass(GLBuffer *outputBuffer, GLenum renderType, GLsizei count) const;

    void doPass(GLBuffer *outputBuffer, GLsizei count) const;

    void doPass(GLBuffer *outputBuffer, GLsizei start, GLsizei count) const;
};


#endif //CPP_LEARN_GLTRANSFORMFEEDBACKSHADER_H
