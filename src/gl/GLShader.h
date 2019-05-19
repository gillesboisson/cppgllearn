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


enum GLShaderType{
    Render,
    TransformFeedback,
};


class GLShader
{

protected:

    GLuint _programId{};
    GLuint _vertexId, _fragmentId, _geometryId{};
    GLShaderType _shaderType{};


    bool loadVertexShader(const std::string &filename);
    bool loadFragmentShader(const std::string &filename);
    bool loadGeometryShader(const std::string &filename);
    bool compileShader(const std::string &filename, GLuint shaderId);

public:


    GLShader();
    GLShader(const std::string &vertProgramPath, const std::string &fragProgramPath);
    GLShader(const std::string &vertProgramPath, const std::string &fragProgramPath, const std::string &geomProgramPath);

	std::string readFile(const char *file);
 
	void useProgram() const;

    bool init(const std::string &vertProgramPath, const std::string &fragProgramPath);
    bool init(const std::string &vertProgramPath, const std::string &fragProgramPath, const std::string &geomProgramPath);


//    bool initTransformFeedback(const std::string &vertProgramPath, const std::string &geomProgramPath,GLsizei count,const char** varying,GLenum bufferMode);


    bool linkShaders();

	void printShaderLinkingError(int32_t shaderId);

	// If something went wrong whil compiling the shaders, we'll use this function to find the error
	void printShaderCompilationErrorInfo(int32_t shaderId);
 
	void dispose();

    uint32_t getUniformLocation(const char *uniformName) const;
    void setUniformMat4v(GLuint location, const glm::mat4 & mat) const;

    void setUniformVec4v(GLuint location, const glm::vec4 & vec) const;

    void setUniformVec3v(GLuint location, const glm::vec3 & vec) const;

    void setUniformFloat(GLuint location, float fl) const;

    void setUniformMat4v(const char *uniformName, const glm::mat4 &mat) const;

    void setUniformVec4v(const char *uniformName, const glm::vec4 &vec) const;

    void setUniformVec3v(const char *uniformName, const glm::vec3 &vec) const;

    void setUniformFloat(const char *uniformName, float fl) const;

    void bindUniformBlockIndex(const char* name,GLuint index) const;

    bool initBaseShaders(const std::string &vertProgramPath, const std::string &fragProgramPath);

    void deleteElements();


    GLShaderType getShaderType() const;


};

#endif