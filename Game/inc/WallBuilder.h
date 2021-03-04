/* Copyright 2020 Samuel Dunny */
/* Wall class (in header file) */

//TODO probably delete

#ifndef WALLBUILDER
#define WALLBUILDER

#include "Wall.h"

/* Purpose:
 *  This class instantiates 3 walls, and this class's children
 *  will be able to modify the configuration of those 3 walls to create
 *  essentially maze building blocks (step up singular walls)
 */

class WallBuilder {
protected:
    // variables for the walls
    Wall* wall1;
    Wall* wall2;
    Wall* wall3;

public:
    WallBuilder(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position);

    ~WallBuilder();

    void Draw(sf::RenderWindow& window);

    bool ColliderCheck(Collider other, float push);
};

WallBuilder::WallBuilder(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position) {
    // build all 3 walls in the same place (effectively create just one wall)
    wall1 = new Wall(texture, size, position);
    wall2 = new Wall(texture, size, position);
    wall3 = new Wall(texture, size, position);
}

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

#endif  // WALLBUILDER