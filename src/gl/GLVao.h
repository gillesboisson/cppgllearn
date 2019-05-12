

#ifndef GL_VAO
#define GL_VAO

#include <glad/glad.h>
#include "GLAttribute.h"
#include "GLBuffer.h"
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
//    GLuint _indexBufferGlId;
    GLBuffer *_indexBuffer;

    GLenum _indType = GL_UNSIGNED_SHORT;
    int _nbAttributes;


public:

    ~GLVao();

    GLenum getIndType() const;
    void init(GLAttribute *attributes, int nbAttributes);
    void init(GLAttribute *attributes, int nbAttributes, GLBuffer *indexBuffer);
    void init(GLAttribute *attributes, int nbAttributes, GLBuffer *indexBuffer, GLenum indType);
    void bind();
    void gen();
    void activate();
    void dispose(bool destroyBuffers = true);


    GLBuffer *getIndexBuffer() const;

    GLuint getGLId();
};


#endif