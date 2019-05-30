//
// Created by Gilles Boisson on 2019-05-18.
//


#include "GLRenderer.h"
#include <iostream>

GLVao *GLRenderer::getCurrentVao() const {
    return _currentVao;
}

GLShader *GLRenderer::getCurrentShader() const {
    return _currentShader;
}


bool GLRenderer::isFaceCullingEnabled() const {
    return _faceCullingEnabled;
}

bool GLRenderer::isFragmentDiscarded() const {
    return _rasterDiscarded;
}


void GLRenderer::bindShader(GLShader *shader) {
    if(shader != _currentShader){
        _currentShader = shader;
        if(_currentShader != nullptr){
            _currentShader->useProgram();
        }else{
            glUseProgram(0);
        }
    }
}

void GLRenderer::bindVao(GLVao *vao) {
    if(vao != _currentVao){
        _currentVao = vao;
        if(_currentVao != nullptr){
            _currentVao->bind();
        }else{
            glBindVertexArray(0);
        }
    }
}

void GLRenderer::setClearColor(glm::vec4 color) {
    _clearColor = color;
    glClearColor(_clearColor.r,_clearColor.g,_clearColor.b,_clearColor.a) ;


}

void GLRenderer::clear() const{
    // TODO: update based enabled features
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLRenderer::reset()  {
    glUseProgram(0);
    glBindVertexArray(0);
    _currentVao = nullptr;
    _currentShader = nullptr;
    resetViewport();
}

void GLRenderer::bindMaterial(GLMaterialA *material) {
    if(material != _currentMaterial){
        _currentMaterial= material;
        if(_currentMaterial!= nullptr){
            _currentMaterial->bindCommonUniforms();
        }
    }
}

void GLRenderer::renderMesh(GLMesh *mesh, GLMaterialA *material) {
    bindShader(material->getActiveShader());
    bindMaterial(material);
    bindVao(mesh->getVao());
    mesh->draw();
}

void GLRenderer::renderModel(Model *model, Camera *camera) {
    auto mat = model->getMaterial();
    auto mesh = model->getMesh();
    bindShader(mat->getActiveShader());
    bindMaterial(mat);
    bindVao(model->getMesh()->getVao());
    mat->render(mesh,*model->getWorldMat(),camera);
}

void GLRenderer::prepare(GLMaterialA *material, GLVao *vao, Camera *camera) {
    bindShader(material->getActiveShader());
    bindMaterial(material);
    bindVao(vao);
    material->bindModelUniforms(nullptr, camera);
}


void GLRenderer::prepareTransformFeedbackPass(
    GLTransformFeedbackShader* tfShader,
    GLVao* vao){

    setRasterDiscarded(false);
    bindShader(tfShader);
    bindVao(vao);
}

void GLRenderer::doTransformFeedbackPass(
    GLTransformFeedbackShader* tfShader,
    GLVao* vao,
    GLBuffer *outputBuffer,
    GLsizei count
){
    prepareTransformFeedbackPass(tfShader,vao);
    tfShader->doPass(outputBuffer,count);

}

GLShader* GLRenderer::registerShader(const char *name, GLShader *shader) {
    if(_shaders.find(name) == _shaders.end()) {
        _shaders[name] = shader;
        return shader;
    }else{
        printf("GLRenderer::registerShader : shader %s already exists",name);
        return shader;
    }
}

GLShader* GLRenderer::getShader(const char *name) const{
    auto foundShader = _shaders.find(name);
    if(foundShader != _shaders.end()){
        return foundShader->second;
    }else {
        printf("!! Shader %s not found \n",name);
        return nullptr;
    }
}


void GLRenderer::deleteShader(const char *name) {
    auto foundShader = _shaders.find(name);
    if(foundShader != _shaders.end()){
        delete foundShader->second;
        _shaders.erase(name);
    }
}

bool GLRenderer::isDepthTestEnabled() const {
    return _depthTestEnabled;
}

void GLRenderer::setFaceCullingEnabled(bool val) {
    if(val != _faceCullingEnabled){
        _faceCullingEnabled = val;
        if(_faceCullingEnabled){
            glEnable(GL_CULL_FACE);
            glCullFace(GL_BACK);
        }else{
            glDisable(GL_CULL_FACE);
        }
    }
}

void GLRenderer::setRasterDiscarded(bool val) {
    if(val != _rasterDiscarded){
        _rasterDiscarded = val;
        if(_rasterDiscarded){
            glEnable(GL_RASTERIZER_DISCARD);
        }else{
            glDisable(GL_RASTERIZER_DISCARD);
        }
    }
}

void GLRenderer::setDepthTestEnabled(bool val) {
    if(val != _depthTestEnabled){
        _depthTestEnabled = val;
        if(_depthTestEnabled){
            glEnable(GL_DEPTH_TEST);
        }else{
            glDisable(GL_DEPTH_TEST);
        }
    }
}

GLRenderer::GLRenderer():GLRenderer(0,0,0,0) {

}

GLRenderer::GLRenderer(GLsizei width, GLsizei height):GLRenderer(0,0,width,height) {

}

GLRenderer::GLRenderer(GLint vpX, GLint vpY, GLsizei width, GLsizei height) {
    _viewportX = vpX;
    _viewportY = vpY;
    _viewportWidth = width;
    _viewportHeight = height;
    _fbStack = new FBStack(30);
    _fbStack->push(vpX,vpY,width,height);
}

void GLRenderer::pushFrameBuffer(GLFrameBuffer* fbo){
    _fbStack->push(fbo);
}

void GLRenderer::swapFrameBuffer(GLFrameBuffer* fbo){
_fbStack->replace(fbo);
}

GLFrameBuffer* GLRenderer::popFrameBuffer(){
    if(_fbStack->getStackInd() > 1) {
        auto fbStackData = _fbStack->pop();
        return fbStackData->fbo;
    }else{
        return nullptr;
    }
}





void GLRenderer::resetViewport() const{
    _fbStack->restore(0); // restore
}

GLRenderer::~GLRenderer() {
    delete _fbStack;
}

void GLRenderer::resize(GLsizei width, GLsizei height) {
    _viewportWidth = width;
    _viewportHeight = height;
    if(_fbStack->getStackInd() > 1) {
        auto vpStack = _fbStack->getStack();
        vpStack->width = width;
        vpStack->height = height;
    }else{
        _fbStack->replace(
            _viewportX,
            _viewportY,
            _viewportWidth,
            _viewportHeight
            );
    }
}



