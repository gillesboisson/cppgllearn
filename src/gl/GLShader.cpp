
 

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
 
#include "GLShader.h"


std::string GLShader::readFile(const char *file)
{
	std::ifstream t(file);

	// Read file into buffer
	std::stringstream buffer;
	buffer << t.rdbuf();

	// Make a std::string and fill it with the contents of buffer
	std::string fileContent = buffer.str();


	return fileContent;
}


void GLShader::useProgram() const
{
	// Load the shader into the rendering pipeline
	glUseProgram(_programId);
}

void GLShader::deleteElements(){
    if(_programId != 0) {
        glDeleteProgram(_programId);
        _programId = 0;
    }

    if(_vertexId != 0) {
        glDeleteShader(_vertexId);
        _vertexId = 0;
    }

    if(_fragmentId != 0) {
        glDeleteShader(_fragmentId);
        _fragmentId = 0;
    }

    if(_geometryId != 0) {
        glDeleteShader(_geometryId);
        _geometryId = 0;
    }

}

bool GLShader::initBaseShaders(const std::string &vertProgramPath, const std::string &fragProgramPath){
    deleteElements();
    _programId = glCreateProgram();
    _shaderType = Render;


    if (loadVertexShader(vertProgramPath) && loadFragmentShader(fragProgramPath)){
        return true;
    }

    deleteElements();
    return false;
}

bool GLShader::init(const std::string &vertProgramPath, const std::string &fragProgramPath)
{
    if(initBaseShaders(vertProgramPath,fragProgramPath)){
        return linkShaders();
    }

    deleteElements();
    return false;
}

bool GLShader::init(const std::string &vertProgramPath, const std::string &fragProgramPath, const std::string &geomProgramPath)
{
    if(initBaseShaders(vertProgramPath,fragProgramPath) && loadGeometryShader(geomProgramPath)){
        return linkShaders();
    }

    deleteElements();
    return false;

}




bool GLShader::loadGeometryShader(const std::string &filename)
{
    _geometryId = glCreateShader(GL_GEOMETRY_SHADER);

    return compileShader(filename,_geometryId);
}

bool GLShader::loadVertexShader(const std::string &filename)
{
	_vertexId = glCreateShader(GL_VERTEX_SHADER);

    return compileShader(filename,_vertexId);
}

bool GLShader::loadFragmentShader(const std::string &filename)
{
    _fragmentId = glCreateShader(GL_FRAGMENT_SHADER);

    return compileShader(filename,_fragmentId);

}

bool GLShader::linkShaders()
{
	// Link. At this point, our shaders will be inspected/optized and the binary code generated
	// The binary code will then be uploaded to the GPU
	glLinkProgram(_programId);

	// Verify that the linking succeeded
	int isLinked;
	glGetProgramiv(_programId, GL_LINK_STATUS, (int *)&isLinked);

	if (isLinked == 0)
        printShaderLinkingError(_programId);

	bool res = isLinked != 0;

	if(!res) deleteElements();

	return res;
}

void GLShader::printShaderLinkingError(int32_t shaderId)
{
	std::cout << "=======================================\n";
	std::cout << "GLShader linking failed : " << std::endl;

	// find length of shader info log
	int maxLength;
	glGetProgramiv(shaderId, GL_INFO_LOG_LENGTH, &maxLength);

	std::cout << "Info Length : " << maxLength << std::endl;

	// Get shader info log
	char* shaderProgramInfoLog = new char[maxLength];
	glGetProgramInfoLog(_programId, maxLength, &maxLength, shaderProgramInfoLog);

	std::cout << "Linker error message : " << shaderProgramInfoLog << std::endl;

	/* Handle the error in an appropriate way such as displaying a message or writing to a log file. */
	/* In this simple program, we'll just leave */
	delete[] shaderProgramInfoLog;
    shaderProgramInfoLog = nullptr;

}

// If something went wrong whil compiling the shaders, we'll use this function to find the error
void GLShader::printShaderCompilationErrorInfo(int32_t shaderId)
{
	std::cout << "=======================================\n";
	std::cout << "GLShader compilation failed : " << std::endl;

	// find length of shader info log
	int maxLength;
	glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &maxLength);

	// Get shader info log
	char* shaderInfoLog = new char[maxLength];
	glGetShaderInfoLog(shaderId, maxLength, &maxLength, shaderInfoLog );

	// Print shader info log
	std::cout << "\tError info : " << shaderInfoLog << std::endl;

	std::cout << "=======================================\n\n";
	delete []shaderInfoLog;
    shaderInfoLog = nullptr;
}

void GLShader::dispose()
{
	/* Cleanup all the things we bound and allocated */
	glUseProgram(0);
	glDetachShader(_programId, _vertexId);
	glDetachShader(_programId, _fragmentId);

	glDeleteProgram(_programId);


	glDeleteShader(_vertexId);
	glDeleteShader(_fragmentId);
}

void GLShader::setUniformMat4v(GLuint location, const glm::mat4 &mat) const {
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
}

void GLShader::setUniformVec4v(GLuint location, const glm::vec4 &vec) const{
    glUniform4fv(location, 1, glm::value_ptr(vec));
}

void GLShader::setUniformVec3v(GLuint location, const glm::vec3 &vec) const{
    glUniform3fv(location, 1, glm::value_ptr(vec));
}

void GLShader::setUniformFloat(GLuint location, float fl) const{
    glUniform1f(location, fl);
}


void GLShader::setUniformMat4v(const char* uniformName, const glm::mat4 &mat) const {
    GLuint location = glGetUniformLocation(_programId, uniformName);
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
}

void GLShader::setUniformVec4v(const char* uniformName, const glm::vec4 &vec) const {
    GLuint location = glGetUniformLocation(_programId, uniformName);
    glUniform4fv(location, 1, glm::value_ptr(vec));
}

void GLShader::setUniformVec3v(const char* uniformName, const glm::vec3 &vec) const {
    GLuint location = glGetUniformLocation(_programId, uniformName);
    glUniform3fv(location, 1, glm::value_ptr(vec));
}

void GLShader::setUniformFloat(const char* uniformName, float fl) const {
    GLuint location = glGetUniformLocation(_programId, uniformName);
    glUniform1f(location, fl);
}

uint32_t  GLShader::getUniformLocation(const char *uniformName) const {
    return glGetUniformLocation(_programId, uniformName);
}

void GLShader::bindUniformBlockIndex(const char *name, GLuint index) const {
    GLuint udIndex = glGetUniformBlockIndex(_programId, name);
    printf("bindUniformBlockIndex %d \n",udIndex);
    glUniformBlockBinding(_programId, udIndex, index);
}

bool GLShader::compileShader(const std::string &filename, GLuint shaderId) {

    std::string str = readFile(filename.c_str());

    char* src = const_cast<char*>( str.c_str());
    int32_t size = str.length();

    glShaderSource(shaderId, 1, &src, &size);

    // Compile the vertex shader
    glCompileShader(shaderId);

    int wasCompiled = 0;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &wasCompiled );

    if (wasCompiled == 0)
    {
        printShaderCompilationErrorInfo(shaderId);
        return false;
    }

    glAttachShader(_programId, shaderId);

    return true;
}

GLShaderType GLShader::getShaderType() const {
    return _shaderType;
}






