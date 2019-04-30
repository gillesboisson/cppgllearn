// OpenGL / glew Headers
#ifndef LIBS_SHADER_H
#define LIBS_SHADER_H
#include <glad/glad.h>

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



class GLShader
{
public:

	GLuint _shaderProgram;
	GLuint _vertexshader, _fragmentShader;

	std::string readFile(const char *file);
 
	void bindAttributeLocation(int index, const std::string &attribute);
	void useProgram();

	bool init(const std::string &vertProgramPath, const std::string &fragProgramPath);
 
	bool loadVertexShader(const std::string &filename);
	bool loadFragmentShader(const std::string &filename);

	bool linkShaders();

	void printShaderLinkingError(int32_t shaderId);

	// If something went wrong whil compiling the shaders, we'll use this function to find the error
	void printShaderCompilationErrorInfo(int32_t shaderId);
 
	void dispose();

    unsigned int getUniformLocation(const char *uniformName);
    void uniformMat4v(GLuint location, glm::mat4 mat);
};

#endif