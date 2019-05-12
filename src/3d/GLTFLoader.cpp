//
// Created by Gilles Boisson on 2019-04-28.
//

#include "GLTFLoader.h"
#include "../gl/GLHelper.h"
#include "../gl/GLBuffer.h"



std::vector<GLBuffer*> GLTFLoader::loadBufferViews(const std::vector<tinygltf::Buffer> &buffers,
                                                  const std::vector<tinygltf::BufferView> &bufferViews) {

    std::vector<GLBuffer*> vbos;

    for(auto & it : bufferViews){
        auto buffer = buffers[it.buffer];

        unsigned char* bufferC = &buffer.data[it.byteOffset];

        auto vbo = new GLBuffer(it.target,GL_STATIC_DRAW);
        vbo->uploadData(it.byteLength,bufferC);
        vbos.push_back(vbo);

    }

    return vbos;
}

//std::vector<GLAttribute> GLTFLoader::LoadAccessors(const std::vector<uint32_t>& vbos, const std::vector<tinygltf::Accessor> &accessors) {
//    std::vector<GLAttribute> attributes(accessors.size());
//    GLAttribute attr;
//
//    for(auto & it : accessors){
//        attr.size       = it.count;
//        attr.
//    }
//    return attributes;
//}

std::vector<GLMesh*>
GLTFLoader::loadMeshes(const std::vector<GLBuffer*> &vbos,
                       const std::vector<tinygltf::BufferView> &bufferViews,
                       const std::vector<tinygltf::Accessor> &accessors,
                       const std::vector<tinygltf::Primitive> &primitives) {

    std::vector<GLMesh*> meshes;
    meshes.reserve(primitives.size());


    tinygltf::Accessor acc;



    for(auto & pr : primitives){


        auto attributes = new GLAttribute[pr.attributes.size()];
        uint32_t nbPoints = 0;
        uint8_t ind = 0;

        for(auto & attr : pr.attributes){
            auto attrLocation  = GTLFAttributeLocation.find(attr.first);

            if(attrLocation != GTLFAttributeLocation.end()){
                acc = accessors[attr.second];


                if(nbPoints == 0){
                    nbPoints = acc.count;
                }

                attributes[ind++].set(
                        attrLocation->second,
                        acc.type,
                        acc.componentType,
                        vbos[acc.bufferView],
                        bufferViews[acc.bufferView].byteStride,
                        acc.normalized,
                        (GLvoid*) acc.byteOffset
                        );



            }else{
                std::printf("Attribute %s Not found",attr.first.c_str());
            }
        }


        GLBuffer* indicesVBO ;
        GLenum indType = GL_UNSIGNED_SHORT;

        if(pr.indices >= 0){
            auto indAcc = accessors[pr.indices];
            indicesVBO = vbos[indAcc.bufferView];
            nbPoints = indAcc.count;
            indType = indAcc.componentType;
        }


        GLMesh* mesh = new GLMesh(nbPoints,pr.mode);
        mesh->getVao()->init(attributes,pr.attributes.size(), indicesVBO, indType);
        meshes.emplace_back(mesh);


    }

    return meshes;
}
