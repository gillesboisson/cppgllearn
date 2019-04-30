#include <glad/glad.h>
#include <string>
#include <map>


#ifndef GL_VAO
#define GL_VAO


typedef struct GLAttribute{

    uint32_t location;
    GLint size;
    GLenum type;
    GLboolean normalize;
    GLsizei stride;
    GLuint vbo;
    
    const GLvoid * pointer;

} GLAttribute;

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





GLAttribute CreateGLAttribute(uint32_t location, GLint size, GLenum type,GLuint vbo,GLsizei stride,GLboolean normalize,const GLvoid * pointer);

void ActivateGLAttribute(GLAttribute* attr);

class GLVao{
    GLAttribute* _attributes;
    GLuint _vao;
    GLuint _indVbo;
    GLenum _indType = GL_UNSIGNED_SHORT;
public:
    GLenum GetIndType() const;

private:
    int _nbAttributes;


public:
    void init(GLAttribute *attributes, int nbAttributes);
    void init(GLAttribute *attributes, int nbAttributes, GLuint indVbo);
    void init(GLAttribute *attributes, int nbAttributes, GLuint indVbo, GLenum indType);
    void bind();
    void gen();
    void activate();
    void dispose();

    GLuint getVao();
    GLuint getIndVbo();
};


#endif