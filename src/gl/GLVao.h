

#ifndef GL_VAO
#define GL_VAO

#include <glad/glad.h>
#include "GLAttribute.h"
#include <string>
#include <map>




enum GLAttributeLocation{
    Position = 0,
    Uv = 1,
    Uv2 = 2,
    Normal = 3,
    Color = 4,
    Tangant = 5,
    Joint = 6,
    Weight = 7,
    IPosition = 10,
    IOrientation = 11,
    IColor = 12,
    IScale = 13
};





//GLAttribute CreateGLAttribute(uint32_t location, GLint size, GLenum type,GLuint vbo,GLsizei stride,GLboolean normalize,const GLvoid * pointer);
//GLAttribute* NewGLAttribute(uint32_t location, GLint size, GLenum type,GLuint vbo,GLsizei stride,GLboolean normalize,const GLvoid * pointer);

void ActivateGLAttribute(GLAttribute* attr);

class GLVao{
    GLAttribute* _attributes;
    GLuint _glId;
    GLuint _indexBufferGlId;
    GLenum _indType = GL_UNSIGNED_SHORT;
    int _nbAttributes;


public:

    GLenum getIndType() const;
    void init(GLAttribute *attributes, int nbAttributes);
    void init(GLAttribute *attributes, int nbAttributes, GLuint indVbo);
    void init(GLAttribute *attributes, int nbAttributes, GLuint indVbo, GLenum indType);
    void bind();
    void gen();
    void activate();
    void dispose(bool destroyBuffers = true);

    GLuint getGLId();
    GLuint getIndexBufferGlId();
};


#endif