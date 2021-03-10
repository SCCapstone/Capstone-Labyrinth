/* Copyright 2021 Samuel Dunny */
/* Wall_Component  (in header file) */

#ifndef WALL_COMPONENT_H
#define WALL_COMPONENT_H

#include "Wall.h"
#include "Individual.h"

/* Purpose:
 *  This class instantiates 3 walls, and any child class that inherits from 
 *  this base class will be able to modify the configuration of those 3 walls
 *  to create essentially maze building blocks (step up from singular walls)
 */

class Wall_Component {
// protected scope so children can modify instance variables
protected:
    // variables for the walls
    Wall* wall1;
    Wall* wall2;
    Wall* wall3;

public:
    // constructor
    Wall_Component(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position);

    // destructor
    ~Wall_Component();

    // Draw method, draws all walls into referenced window
    void Draw(sf::RenderWindow& window);

    // returns true if Individual's Collider is many contact with any of the 3 wall segments
    bool ColliderCheck(Collider other, float push);

    void shiftWallComponent(float x_shift, float y_shift);

    bool inWallComponent(Vector2f pos);

    // when making strips and corners, wall 2 is always center, hence only returning wall 2's position
    Vector2f getCenterWallCoords() { return wall2->GetPosition(); }
};

// instantiates all wall instance variables
Wall_Component::Wall_Component(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position) {
    // build all 3 walls in the same place (effectively create just one wall)
    wall1 = new Wall(texture, size, position);
    wall2 = new Wall(texture, size, position);
    wall3 = new Wall(texture, size, position);
}

// empty destructor (handled in Game_Engine)
Wall_Component::~Wall_Component() { /* empty */ }

void Wall_Component::Draw(sf::RenderWindow& window) {
    wall1->Draw(window);
    wall2->Draw(window);
    wall3->Draw(window);
}

bool Wall_Component::ColliderCheck(Collider other, float push) {
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

void Wall_Component::shiftWallComponent(float x_shift, float y_shift) {
    wall1->SetPosition(Vector2f(wall1->GetPosition().x + (x_shift * scale),
                                wall1->GetPosition().y + (y_shift * scale)));

    wall2->SetPosition(Vector2f(wall2->GetPosition().x + (x_shift * scale),
                                wall2->GetPosition().y + (y_shift * scale)));

    wall3->SetPosition(Vector2f(wall3->GetPosition().x + (x_shift * scale),
                                wall3->GetPosition().y + (y_shift * scale)));
}

bool Wall_Component::inWallComponent(Vector2f pos) {
    return wall1->inWall(pos) ||
        wall2->inWall(pos) ||
        wall3->inWall(pos);
}

#endif  // WALL_COMPONENT_H