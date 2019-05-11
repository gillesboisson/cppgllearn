//
// Created by Gilles Boisson on 2019-04-26.
//

#ifndef CPP_LEARN_GLTEXTURE_H
#define CPP_LEARN_GLTEXTURE_H

#include <glad/glad.h>

#include "stb_image.h"

class GLTexture {
protected:
    int _width;
    int _height;
    GLuint _glId;
    GLenum _type;
    GLenum _target;
    GLenum _format;

    void initLinearTexture();

    void gen();

public:
    void loadTexture2d(const char *imagePath);

    ///
    /// \param format : GL_RED, GL_RG, GL_RGB, GL_BGR, GL_RGBA, GL_BGRA, GL_RED_INTEGER, GL_RG_INTEGER, GL_RGB_INTEGER, GL_BGR_INTEGER, GL_RGBA_INTEGER, GL_BGRA_INTEGER, GL_STENCIL_INDEX, GL_DEPTH_COMPONENT, GL_DEPTH_STENCIL.
    /// \param target : GL_TEXTURE_2D, GL_PROXY_TEXTURE_2D, GL_TEXTURE_1D_ARRAY, GL_PROXY_TEXTURE_1D_ARRAY, GL_TEXTURE_RECTANGLE, GL_PROXY_TEXTURE_RECTANGLE, GL_TEXTURE_CUBE_MAP_POSITIVE_X, GL_TEXTURE_CUBE_MAP_NEGATIVE_X, GL_TEXTURE_CUBE_MAP_POSITIVE_Y, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, GL_TEXTURE_CUBE_MAP_POSITIVE_Z, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, or GL_PROXY_TEXTURE_CUBE_MAP.
    /// \param type : GL_UNSIGNED_BYTE, GL_BYTE, GL_UNSIGNED_SHORT, GL_SHORT, GL_UNSIGNED_INT, GL_INT, GL_HALF_FLOAT, GL_FLOAT, GL_UNSIGNED_BYTE_3_3_2, GL_UNSIGNED_BYTE_2_3_3_REV, GL_UNSIGNED_SHORT_5_6_5, GL_UNSIGNED_SHORT_5_6_5_REV, GL_UNSIGNED_SHORT_4_4_4_4, GL_UNSIGNED_SHORT_4_4_4_4_REV, GL_UNSIGNED_SHORT_5_5_5_1, GL_UNSIGNED_SHORT_1_5_5_5_REV, GL_UNSIGNED_INT_8_8_8_8, GL_UNSIGNED_INT_8_8_8_8_REV, GL_UNSIGNED_INT_10_10_10_2, and GL_UNSIGNED_INT_2_10_10_10_REV.
    /// \param width : Texture width
    /// \param height : Texture height
    void initEmptyTexture2d(GLenum format, GLenum target, GLenum type, int width, int height);

    void bind() const;

    void activate(unsigned int index = 0) const;

    void dispose();

    // accessors ----------------------------------------------------------------

    int getWidth() const;

    int getHeight() const;

    GLuint getGLId() const;

    GLenum getType() const;

    GLenum getTarget() const;

    GLenum getFormat() const;

    void loadTextureCubeMap(const char *baseImagePath, const char *fileExtension);
};


#endif //CPP_LEARN_GLTEXTURE_H
