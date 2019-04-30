//
// Created by Gilles Boisson on 2019-04-28.
//

#ifndef CPP_LEARN_GLTFLOADER_H
#define CPP_LEARN_GLTFLOADER_H
#include <vector>

#include "tiny_gltf.h"
#include "../gl/GLMesh.h"


const std::map<std::string,GLAttributeLocation> GTLFAttributeLocation = {
        {"POSITION",Position},
        {"NORMAL",Normal},
        {"TANGENT",Tangant},
        {"TEXCOORD_0",Uv},
        {"TEXCOORD_1",Uv2},
        {"COLOR_0",Color},
        {"JOINTS_0",Joint},
        {"WEIGHTS_0",Weight},
};




class GLTFLoader {


public:

    static std::vector<uint32_t> loadBufferViews(
            const std::vector<tinygltf::Buffer> &buffers,
            const std::vector<tinygltf::BufferView> &bufferViews
    );


//    static std::vector<GLAttribute> LoadAccessors(const std::vector<uint32_t> &vbos, const std::vector<tinygltf::Accessor> &accessors);


    static std::vector<GLMesh> loadMeshes(const std::vector<uint32_t> &vbos,
                                          const std::vector<tinygltf::BufferView> &bufferViews,
                                          const std::vector<tinygltf::Accessor> &accessors,
                                          const std::vector<tinygltf::Primitive> &primitives);


};


#endif //CPP_LEARN_GLTFLOADER_H
