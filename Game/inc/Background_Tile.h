/* Copyright 2021 Samuel Dunny */
/* Background_Tile class (in header file) */

#ifndef BACKGROUND_TILE_H
#define BACKGROUND_TILE_H

#include <SFML/Graphics.hpp>

// from sf library
using sf::RenderWindow;
using sf::Texture;
using sf::Vector2f;
using sf::RectangleShape;
using sf::Keyboard;

class Background_Tile {
    // private attributes
private:
    RectangleShape bg_text;

    float x_Coord;
    float y_Coord;

    // public attributes
public:
    // Constructor
    Background_Tile(Texture* texture, Vector2f size, float x_pos, float y_pos);

    //Destructor
    ~Background_Tile();

    // takes in window reference, draws player
    void Draw(RenderWindow& window);
};

Background_Tile::Background_Tile(Texture* texture, Vector2f size, float x_pos, float y_pos) {
    bg_text.setTexture(texture);
    // set the same size as walls
    bg_text.setSize(size);
    bg_text.setOrigin(bg_text.getSize() / 2.0f);
    bg_text.setPosition(x_pos, y_pos);
    this->x_Coord = x_pos;
    this->y_Coord = y_pos;
}

Background_Tile::~Background_Tile() { /* empty */ }

void Background_Tile::Draw(RenderWindow& window) {
    window.draw(bg_text);
}

#endif  // BACKGROUND_TILE_H