//
// Created by Gilles Boisson on 2019-05-30.
//


#include "TextureAtlas.h"
#include <iostream>
#include <fstream>

#include <map>
#include <string>
#include <iterator>
#include <algorithm>
SubTexture* TextureAtlas::addSubTexture(const std::string& name, uint32_t x, uint32_t y, uint32_t width, uint32_t height) {


    if(_subTextures.count(name) == 0){
        auto texture =  new SubTexture(_texture,x,y,width,height);

        auto ret = _subTextures.insert(_subTextures.end(),std::pair<std::string,SubTexture*>(name,texture));

        return texture;
    }else{
        printf("TextureAtlas::addTexture : sub texture %s already exists\n",name.c_str());
        return nullptr;
    }
}




SubTexture* TextureAtlas::getSubTexture(const std::string& name){
    if(_subTextures.find(name) == _subTextures.end()){
        printf("TextureAtlas::getTexture : sub texture %s not found\n",name.c_str());
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
    std::string line;

    std::ifstream file(filename);
//    if (file.is_open())
//    {
//        while ( getline (file,line) )
//        {
//            std::cout << line << '\n';
//        }
//        file.close();
//    }

    Json::CharReaderBuilder rbuilder;
    Json::Value root;
    std::string formattedErrorMessages;
    bool parsingSuccessful = Json::parseFromStream(rbuilder,file,&root,&formattedErrorMessages);

    auto fr = root["frames"][0];

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
            frame["frame"]["w"].asUInt(),
            frame["frame"]["h"].asUInt()
        );
    }


    return true;
}

