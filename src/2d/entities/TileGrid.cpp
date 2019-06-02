//
// Created by Gilles Boisson on 2019-05-31.
//

#include "TileGrid.h"


#import "../core/Camera2D.h"


TileGrid::TileGrid(
    uint32_t nbTileX,
    uint32_t nbTileY,
    float tileWidth,
    float tileHeight,
    uint16_t *gridData,
    std::vector<SubTexture*> tileSet,
    Camera2D* camera
    ) : Entity2D() {

    _nbTileX = nbTileX;
    _nbTileY = nbTileY;
    _tileWidth = tileWidth;
    _tileHeight = tileHeight;
    _camera = camera;
    _tileSet = tileSet;


    _baseTexture = tileSet[0]->getTexture();
    //TODO: check if all sub texture are linked to the same GLTexture

    _gridData = gridData;

    updateGridRect();

}

TileGrid::TileGrid(
    uint32_t nbTileX,
    uint32_t nbTileY,
    float tileWidth,
    float tileHeight,
    std::vector<SubTexture*> tileSet,
    Camera2D* camera) : TileGrid(nbTileX,nbTileY,tileWidth,tileHeight, new uint16_t[nbTileX*nbTileY],tileSet,camera) {


}

TileGrid::TileGrid(
    uint32_t nbTileX,
    uint32_t nbTileY,
    std::vector<SubTexture*> tileSet,
    Camera2D* camera) :TileGrid(nbTileX,nbTileY,tileSet[0]->getWidth(),tileSet[0]->getHeight(),tileSet,camera){

}

TileGrid::TileGrid(
    uint32_t nbTileX,
    uint32_t nbTileY,
    uint16_t *gridData,
    std::vector<SubTexture*> tileSet,
    Camera2D* camera) :TileGrid(nbTileX,nbTileY,tileSet[0]->getWidth(),tileSet[0]->getHeight(),gridData,tileSet,camera){

}

TileGrid::~TileGrid(){
    delete[] _gridData;
}

void TileGrid::updateGridRect(){
    _gridRect.set(0,0,_nbTileX * _tileWidth,_nbTileY * _tileHeight);
}


void TileGrid::pushGeom(SpriteBatch *batch) {
    Rect camRect = _camera->getRect();
    camRect.clamp(_gridRect);

//    float rectW = camRect.getWidth();
//    float rectH = camRect.getHeight();

    int iX0 = floor(camRect.getLeft() / _tileWidth);
    int iY0 = floor(camRect.getTop() / _tileHeight);
    int iX1 = ceil(camRect.getRight() / _tileWidth);
    int iY1 = ceil(camRect.getBottom() / _tileHeight);

    uint32_t rectNbTileX = iX1 - iX0;
    uint32_t rectNbTileY = iY1 - iY0;

    uint32_t nbVisibleTileX = _nbTileX < rectNbTileX ? _nbTileX : rectNbTileX;
    uint32_t nbVisibleTileY = _nbTileY < rectNbTileY ? _nbTileY : rectNbTileY;

    uint32_t gridLength = nbVisibleTileX * nbVisibleTileY;

    uint32_t nbPoints = 4 * gridLength;
    uint32_t nbIndices = 6 * gridLength;

    SpriteVertex* vertices;
    uint16_t *indices;
    uint16_t indicesOffset = batch->pull(&vertices,&indices,nbPoints,nbIndices);

    uint16_t ptInd;

    for (int i = 0; i < nbPoints; ++i) {

        ptInd = i * 4 + indicesOffset;

        indices[0] = ptInd;
        indices[1] = ptInd + 1;
        indices[2] = ptInd + 2;
        indices[3] = ptInd + 1;
        indices[4] = ptInd + 3;
        indices[5] = ptInd + 2;

        indices += 6;
    }



//    printf("iX0 %d,iX1 %d,iY0 %d,iY1 %d \n",iX0 ,iX1 ,iY0 ,iY1 );


    int gridPos;
    int vIndex = 0;

    SubTexture *text;

    float x = _worldMat[2][0];
    float y = _worldMat[2][1];
    float depth = transform.getDepth();

    uint16_t gridVal;


    for (int iY = iY0; iY < iY1; ++iY) {
        for (int iX = iX0; iX < iX1; ++iX,vIndex++) {
            gridPos = iX + iY * _nbTileX;

            gridVal = _gridData[gridPos];

            if(gridVal > 0) {
                text = _tileSet[gridVal - 1];
                auto uv = text->getUvs();

                // uvs;
                vertices[0].uv = uv[0];
                vertices[1].uv = uv[1];
                vertices[2].uv = uv[2];
                vertices[3].uv = uv[3];
            }else{
                vertices[0].uv =
                vertices[1].uv =
                vertices[2].uv =
                vertices[3].uv = glm::vec2(0);
            }

            vertices[0].pos = glm::vec3(iX * _tileWidth+x, iY * _tileHeight +y, depth);
            vertices[1].pos = glm::vec3(vertices[0].pos.x + _tileWidth, vertices[0].pos.y,depth);
            vertices[2].pos = glm::vec3(vertices[0].pos.x, vertices[0].pos.y + _tileHeight,depth);
            vertices[3].pos = glm::vec3(vertices[0].pos.x+ _tileWidth, vertices[0].pos.y + _tileHeight,depth);

            vertices[0].color = _color;
            vertices[1].color = _color;
            vertices[2].color = _color;
            vertices[3].color = _color;

            vertices+=4;
        }
    }

}

void TileGrid::prepareBatch(SpriteBatch *batch) {
    batch->hasSameTextureOrEnd(_baseTexture);
}

uint32_t TileGrid::getNbTileX() const {
    return _nbTileX;
}


uint32_t TileGrid::getNbTileY() const {
    return _nbTileY;
}


float TileGrid::getTileWidth() const {
    return _tileWidth;
}

void TileGrid::setTileWidth(float tileWidth) {
    _tileWidth = tileWidth;
    updateGridRect();

}

float TileGrid::getTileHeight() const {
    return _tileHeight;
}

void TileGrid::setTileHeight(float tileHeight) {
    _tileHeight = tileHeight;
    updateGridRect();

}

Camera2D *TileGrid::getCamera() const {
    return _camera;
}

const Rect &TileGrid::getGridRect() const {
    return _gridRect;
}

uint16_t *TileGrid::getGridData() const {
    return _gridData;
}

const std::vector<SubTexture *> &TileGrid::getTileSet() const {
    return _tileSet;
}

uint32_t TileGrid::getGridSize() {
    return _nbTileX * _nbTileY;
}



//
//void TileGrid::updateGrid() {
//    float rectW = _rect.getWidth();
//    float rectH = _rect.getHeight();
//
//    uint32_t rectNbTileX = ceil(rectW / _tileWidth);
//    uint32_t rectNbTileY = ceil(rectH / _tileHeight);
//
//    uint32_t nbVisibleTileX = _nbTileX < rectNbTileX ? _nbTileX : rectNbTileX;
//    uint32_t nbVisibleTileY = _nbTileY < rectNbTileY ? _nbTileY : rectNbTileY;
//
//    uint32_t gridLength = nbVisibleTileX * nbVisibleTileY;
//
//    uint32_t nbPoints = 4 * gridLength;
//    uint32_t nbIndices = 6 * gridLength;
//
//    auto uvs = new glm::vec2[nbPoints];
//    auto positions = new glm::vec2[nbPoints];
//    auto indices = new uint16_t[nbIndices];
//
//    delete[] _positions;
//    delete[] _uvs;
//    delete[] _indices;
//
//    set(nbPoints, nbIndices, positions, uvs, indices);
//
//    uint16_t *indice;
//    uint16_t ptInd;
//
//    for (int i = 0; i < nbPoints; ++i) {
//        indice = indices + (i * 6);
//        ptInd = i * 4;
//
//        indice[0] = ptInd;
//        indice[1] = ptInd + 1;
//        indice[2] = ptInd + 2;
//        indice[3] = ptInd + 1;
//        indice[4] = ptInd + 3;
//        indice[5] = ptInd + 2;
//    }
//
//    /*
//    uint32_t ptOffset;
//
//    for (int i = 0; i < nbVisibleTileY ; ++i) {
//        for (int f = 0; f < nbVisibleTileX; ++f) {
//
//            ptOffset = i* nbVisibleTileX + f;
//
//            auto pos = positions+(ptOffset * 4);
//
//            pos[0] = glm::vec2(f * _tileWidth, i * _tileHeight);
//            pos[1] = glm::vec2(pos[0].x + _tileWidth, pos[0].y);
//            pos[2] = glm::vec2(pos[0].x, pos[0].y + _tileHeight);
//            pos[3] = glm::vec2(pos[0].x+ _tileWidth, pos[0].y + _tileHeight);
//
//
//
//        }
//    }*/
//
//}


