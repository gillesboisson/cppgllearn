//
// Created by Gilles Boisson on 2019-05-30.
//


#include "TextureAtlas.h"
#include <iostream>
#include <fstream>

SubTexture* TextureAtlas::addSubTexture(const char *name, uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
    if(_subTextures.find(name) == _subTextures.end()){
        auto texture =  new SubTexture(_texture,x,y,width,height);
        _subTextures[name] = texture;
        return texture;
    }else{
        printf("TextureAtlas::addTexture : sub texture %s already exists",name);
        return nullptr;
    }
}




SubTexture* TextureAtlas::getSubTexture(const char *name){
    if(_subTextures.find(name) == _subTextures.end()){
        printf("TextureAtlas::getTexture : sub texture %s not found",name);
        return nullptr;
    }else{
       return _subTextures[name];
    }
}


TextureAtlas::TextureAtlas(GLTexture* texture){
    _texture = texture;
}

TextureAtlas::~TextureAtlas(){
    for (auto const& t : _subTextures){
        delete t.second;
    }
}

bool TextureAtlas::load(const char* filename) {

    std::ifstream file(filename);
    Json::CharReaderBuilder rbuilder;
    Json::Value root;
    std::string formattedErrorMessages;
    bool parsingSuccessful = Json::parseFromStream(rbuilder,file,&root,&formattedErrorMessages);

    if (!parsingSuccessful)
    {

        return false;
    }

    return load(root);
}

bool TextureAtlas::load(const Json::Value& jsonData){
    Json::Value frames = jsonData["frames"];

    for(Json::Value const& frame:frames){

        addSubTexture(
            frame["filename"].asCString(),
            frame["frame"]["x"].asUInt(),
            frame["frame"]["y"].asUInt(),
            frame["frame"]["width"].asUInt(),
            frame["frame"]["height"].asUInt()
        );
    }

    return true;
}

