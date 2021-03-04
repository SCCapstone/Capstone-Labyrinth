/* Copyright 2021 Samuel Dunny */
/* WallBuilder (in header file) */

#ifndef WALLBUILDER_H
#define WALLBUILDER_H

#include "Wall.h"

/* Purpose:
 *  This class instantiates 3 walls, and any child class that inherits from 
 *  this base class will be able to modify the configuration of those 3 walls
 *  to create essentially maze building blocks (step up from singular walls)
 */

class WallBuilder {
// protected scope so children can modify instance variables
protected:
    // variables for the walls
    Wall* wall1;
    Wall* wall2;
    Wall* wall3;

public:
    // constructor
    WallBuilder(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position);

    // destructor
    ~WallBuilder();

    // Draw method, draws all walls into referenced window
    void Draw(sf::RenderWindow& window);

    // returns true if Individual's Collider is many contact with any of the 3 wall segments
    bool ColliderCheck(Collider other, float push);
};

// instantiates all wall instance variables
WallBuilder::WallBuilder(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position) {
    // build all 3 walls in the same place (effectively create just one wall)
    wall1 = new Wall(texture, size, position);
    wall2 = new Wall(texture, size, position);
    wall3 = new Wall(texture, size, position);
}

// empty destructor (handled in Game_Engine)
WallBuilder::~WallBuilder() { /* empty */ }

void WallBuilder::Draw(sf::RenderWindow& window) {
    wall1->Draw(window);
    wall2->Draw(window);
    wall3->Draw(window);
}

bool WallBuilder::ColliderCheck(Collider other, float push) {
    // retrieve contact status (only do this once, otherwise runs into glitch with running diagonally)
    bool wall_cond1 = wall1->ColliderCheck(other, push);
    bool wall_cond2 = wall2->ColliderCheck(other, push);
    bool wall_cond3 = wall3->ColliderCheck(other, push);

    // check for all possible conditions (overkill, but it works)
    if (wall_cond1)
        return true;
    if (wall_cond2)
        return true;
    if (wall_cond3)
        return true;

    if (wall_cond1 && wall_cond2)
        return true;
    if (wall_cond1 && wall_cond3)
        return true;
    if (wall_cond2 && wall_cond3)
        return true;

    if (wall_cond1 && wall_cond2 && wall_cond3)
        return true;

    return false;
}

#endif  // WALLBUILDER_H