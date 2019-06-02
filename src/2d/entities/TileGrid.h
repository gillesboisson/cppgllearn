//
// Created by Gilles Boisson on 2019-05-31.
//

#ifndef CPP_LEARN_TILEGRID_H
#define CPP_LEARN_TILEGRID_H


#include "PolyA.h"
#include "../core/SubTexture.h"
#include "../../utils/Rect.h"
#include "../core/Camera2D.h"


class TileGrid : public Entity2D{
protected:



    uint32_t _nbTileX;
    uint32_t _nbTileY;
    float _tileWidth;
    float _tileHeight;
    Camera2D *_camera;
    Rect  _gridRect;

    uint16_t *_gridData;

    std::vector<SubTexture*> _tileSet;

    GLTexture *_baseTexture;


    void updateGridRect();


    void pushGeom(SpriteBatch *batch) override;
    void prepareBatch(SpriteBatch *batch) override;

public:


    TileGrid(uint32_t nbTileX, uint32_t nbTileY, float tileWidth, float tileHeight, uint16_t *gridData,
             std::vector<SubTexture *> tileSet, Camera2D *camera);

    TileGrid(uint32_t nbTileX, uint32_t nbTileY, uint16_t *gridData, std::vector<SubTexture *> tileSet,
             Camera2D *camera);

    TileGrid(uint32_t nbTileX, uint32_t nbTileY, float tileWidth, float tileHeight,std::vector<SubTexture*> tileSet, Camera2D *camera);

    TileGrid(uint32_t nbTileX, uint32_t nbTileY, std::vector<SubTexture *> tileSet, Camera2D *camera);

    ~TileGrid();


    uint32_t getNbTileX() const;

    uint32_t getNbTileY() const;

    float getTileWidth() const;

    void setTileWidth(float tileWidth);

    float getTileHeight() const;

    void setTileHeight(float tileHeight);

    Camera2D *getCamera() const;

    const Rect &getGridRect() const;

    uint16_t *getGridData() const;

    uint32_t getGridSize();

    const std::vector<SubTexture *> &getTileSet() const;
};


#endif //CPP_LEARN_TILEGRID_H
