
 

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
 
#include "GLShader.h"

std::string GLShader::readFile(const char *file)
{
	// Open file
	
	
	//std::cout << "> Open file " << file << std::endl;
	

	std::ifstream t(file);

	// Read file into buffer
	std::stringstream buffer;
	buffer << t.rdbuf();

	// Make a std::string and fill it with the contents of buffer
	std::string fileContent = buffer.str();

	//std::cout << "<  " << fileContent << std::endl << "==================" << std::endl;

	return fileContent;
}


void GLShader::useProgram()
{
	// Load the shader into the rendering pipeline
	glUseProgram(_shaderProgram);
}

bool GLShader::init(const std::string &vertProgramPath, const std::string &fragProgramPath)
{
	// Generate our shader. This is similar to glGenBuffers() and glGenVertexArray(), except that this returns the ID
	_shaderProgram = glCreateProgram();

	if (!loadVertexShader(vertProgramPath))
		return false;

	if (!loadFragmentShader(fragProgramPath))
		return false;

	// All shaders has been create, now we must put them together into one large object
	return linkShaders();
}


bool GLShader::loadVertexShader(const std::string &filename)
{
	std::cout << "Linking Vertex shader" << filename << " " << std::endl;

	// Read file as std::string 
	std::string str = readFile(filename.c_str());



	 // c_str() gives us a const char*, but we need a non-const one
	char* src = const_cast<char*>( str.c_str());
	int32_t size = str.length();
	
	// Create an empty vertex shader handle
	_vertexshader = glCreateShader(GL_VERTEX_SHADER);

	// Send the vertex shader source code to OpenGL
	glShaderSource(_vertexshader, 1, &src, &size);

	// Compile the vertex shader
	glCompileShader(_vertexshader);

	int wasCompiled = 0;
	glGetShaderiv(_vertexshader, GL_COMPILE_STATUS, &wasCompiled );

	if (wasCompiled == 0)
	{
        printShaderCompilationErrorInfo(_vertexshader);
		return false;
	}

	glAttachShader(_shaderProgram, _vertexshader);
	return true;
}

bool GLShader::loadFragmentShader(const std::string &filename)
{
	std::cout << "Loading Fragment GLShader" << filename << " "<< std::endl;

	// Read file as std::string 
	std::string str = readFile(filename.c_str());

	 // c_str() gives us a const char*, but we need a non-const one
	char* src = const_cast<char*>( str.c_str());
	int32_t size = str.length();
	
	// Create an empty vertex shader handle
	_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	// Send the vertex shader source code to OpenGL
	glShaderSource(_fragmentShader, 1, &src, &size);

	// Compile the vertex shader
	glCompileShader(_fragmentShader);

	int wasCompiled = 0;
	glGetShaderiv(_fragmentShader, GL_COMPILE_STATUS, &wasCompiled );

	if (wasCompiled == 0)
	{
        printShaderCompilationErrorInfo(_fragmentShader);
		return false;
	}

	glAttachShader(_shaderProgram, _fragmentShader);
	return true;
}

bool GLShader::linkShaders()
{
	// Link. At this point, our shaders will be inspected/optized and the binary code generated
	// The binary code will then be uploaded to the GPU
	glLinkProgram(_shaderProgram);

	// Verify that the linking succeeded
	int isLinked;
	glGetProgramiv(_shaderProgram, GL_LINK_STATUS, (int *)&isLinked);

	if (isLinked == 0)
        printShaderLinkingError(_shaderProgram);

	return isLinked != 0;
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
	glGetProgramInfoLog(_shaderProgram, maxLength, &maxLength, shaderProgramInfoLog);

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
	glDetachShader(_shaderProgram, _vertexshader);
	glDetachShader(_shaderProgram, _fragmentShader);

	glDeleteProgram(_shaderProgram);


	glDeleteShader(_vertexshader);
	glDeleteShader(_fragmentShader);
}

void GLShader::setUniformMat4v(GLuint location, const glm::mat4 &mat) {
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
}

void GLShader::setUniformVec4v(GLuint location, const glm::vec4 &vec) {
    glUniform4fv(location, 1, glm::value_ptr(vec));
}

void GLShader::setUniformVec3v(GLuint location, const glm::vec3 &vec) {
    glUniform3fv(location, 1, glm::value_ptr(vec));
}

void GLShader::setUniformFloat(GLuint location, float fl) {
    glUniform1f(location, fl);
}

uint32_t  GLShader::getUniformLocation(const char *uniformName) {
    return glGetUniformLocation(_shaderProgram, uniformName);
}


