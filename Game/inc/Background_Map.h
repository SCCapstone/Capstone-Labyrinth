/* Copyright 2021 Samuel Dunny */
/* Background_Map class (in header file) */

#ifndef BACKGROUND_MAP_H
#define BACKGROUND_MAP_H

#include "BackGround_Tile.h"

class Background_Map {
    // private attributes
private:
    // number of tiles in the vector
    int tile_amount;

    // amount of tiles in the x and y directions
    float x_amt;
    float y_amt;

    // vector of enemy pointer objects
    std::vector<Background_Tile*> tiles;

    // public attributes
public:
    // Constructor
    Background_Map(Texture* texture, Vector2f size, float x_posSTART, float y_posSTART, float x_posEND, float y_posEND);

    //Destructor
    ~Background_Map();

    // takes in window reference, draws player
    void Draw(RenderWindow& window);

    int getTileAmount() { return this->tile_amount;  }
};

Background_Map::Background_Map(Texture* texture, Vector2f size, float x_posSTART, float x_posEND, float y_posSTART, float y_posEND) {
    this->x_amt = abs(x_posSTART - x_posEND);
    this->y_amt = abs(y_posSTART - y_posEND);
    tile_amount = 0;

    for (float i = y_posSTART; i < y_posEND; i += 1.0f) {
        for (float j = x_posSTART; j < x_posEND; j += 1.0f) {
            Background_Tile* nTile = new Background_Tile(texture, size, j * scale, i * scale);
            tile_amount++;
            tiles.push_back(nTile);
        }
    }    
}

Background_Map::~Background_Map() {
    tiles.clear();
    delete& tiles;
}

void Background_Map::Draw(RenderWindow& window) {
    for (int i = 0; i < tile_amount; i++) {
        tiles.at(i)->Draw(window);
    }
}

#endif  // BACKGROUND_MAP_H