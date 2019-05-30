//
// Created by Gilles Boisson on 2019-05-30.
//

#ifndef CPP_LEARN_TEXTUREATLAS_H
#define CPP_LEARN_TEXTUREATLAS_H

#include <map>
#include "SubTexture.h"
//#include "nlohmann/json.hpp"
#include "json/json.h"



class TextureAtlas {
protected:
    std::map<std::string,SubTexture*>_subTextures{};
    GLTexture *_texture;



public:
    explicit TextureAtlas(GLTexture *texture);
    ~TextureAtlas();

    SubTexture* addSubTexture(const std::string& name, uint32_t x, uint32_t y, uint32_t width, uint32_t height);
    SubTexture* getSubTexture(const std::string& name);


    bool load(const Json::Value &jsonData);

    bool load(const char *filename);
};


#endif //CPP_LEARN_TEXTUREATLAS_H
