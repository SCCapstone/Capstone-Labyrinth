/* Copyright 2020 Samuel Dunny */
/* Wall class (in header file) */

//TODO probably delete

#ifndef WALL_UPPERCORNER
#define WALL_UPPERCORNER

#include "Wall.h"

/*
 * will construct and draw the following
 * 
    2     3             3     2
    @@@@  @@@@          @@@@  @@@@
    @  @  @  @          @  @  @  @
    @  @  @  @          @  @  @  @
    @@@@  @@@@    or    @@@@  @@@@
    1                         1
    @@@@                      @@@@
    @  @                      @  @
    @  @                      @  @
    @@@@                      @@@@

    faceRight =         faceRight =
    True                False
 */

class Wall_UpperCorner {
private:
    // variables for the walls
    Wall* wall1;
    Wall* wall2;
    Wall* wall3;

public:
    Wall_UpperCorner(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position, bool faceRight);

    ~Wall_UpperCorner();

    void Draw(sf::RenderWindow& window);

    bool ColliderCheck(Collider other, float push);
};

Wall_UpperCorner::Wall_UpperCorner(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position, bool faceRight) {
    // wall1 will always be directly under wall 2
    wall1 = new Wall(texture, size, sf::Vector2f(position.x, position.y + size.y));

    // wall2 is placed at exact coordinates (corner wall)
    wall2 = new Wall(texture, size, position);

    // wall3 is placed either to the right or left of wall 2, depending on the requested orientation (faceRight)
    if (faceRight)
        wall3 = new Wall(texture, size, sf::Vector2f(position.x + size.x, position.y));
    else
        wall3 = new Wall(texture, size, sf::Vector2f(position.x - size.x, position.y));
}

Wall_UpperCorner::~Wall_UpperCorner() { /* empty */ }

void Wall_UpperCorner::Draw(sf::RenderWindow& window) {
    wall1->Draw(window);
    wall2->Draw(window);
    wall3->Draw(window);
}

bool Wall_UpperCorner::ColliderCheck(Collider other, float push) {

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

#endif  // WALL_UPPERCORNER