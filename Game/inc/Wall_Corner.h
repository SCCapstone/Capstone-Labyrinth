/* Copyright 2021 Samuel Dunny */
/* Wall_Corner class (in header file) */

#ifndef WALL_CORNER
#define WALL_CORNER

#include "WallBuilder.h"

/*
 * will construct and draw the following
 
    2     3             3     2             1                         1
    @@@@  @@@@          @@@@  @@@@          @@@@                      @@@@
    @  @  @  @          @  @  @  @          @  @                      @  @
    @  @  @  @          @  @  @  @          @  @                      @  @
    @@@@  @@@@    or    @@@@  @@@@    or    @@@@          or          @@@@
    1                         1             2     3             3     2
    @@@@                      @@@@          @@@@  @@@@          @@@@  @@@@
    @  @                      @  @          @  @  @  @          @  @  @  @
    @  @                      @  @          @  @  @  @          @  @  @  @
    @@@@                      @@@@          @@@@  @@@@          @@@@  @@@@

    faceRight =         faceRight =         faceRight =         faceRight =
    True                False               True                False
    faceUp =            faceUp =            faceUp =            faceUp =
    False               False               True                True

 */

class Wall_Corner: public WallBuilder {
private:
    // conditions for the corner orientation (not necessary, might use later)
    bool faceRight;
    bool faceUp;

public:
    Wall_Corner(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position, bool faceRight, bool faceUp);

    ~Wall_Corner();
};

Wall_Corner::Wall_Corner(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position, bool fRight, bool fUp):
    WallBuilder(texture, size, position) {
    // lower corner
    if (fUp) {
        // wall1 will always be directly above wall 2
        wall1->SetPosition(sf::Vector2f(position.x, position.y - size.y));

        // wall2 is placed at exact coordinates (corner wall)
        wall2->SetPosition(position);

        this->faceUp = true;

        // wall3 is placed either to the right or left of wall2
        if (fRight) {
            // to the right (facing right)
            wall3->SetPosition(sf::Vector2f(position.x + size.x, position.y));
            this->faceRight = true;
        }
        else {
            // to the left (facing left)
            wall3->SetPosition(sf::Vector2f(position.x - size.x, position.y));
            this->faceRight = false;
        }
    }
    // upper corner
    else {
        // wall1 will always be directly under wall 2
        wall1->SetPosition(sf::Vector2f(position.x, position.y + size.y));

        // wall2 is placed at exact coordinates (corner wall)
        wall2->SetPosition(position);

        this->faceUp = false;

        // wall3 is placed either to the right or left of wall2
        if (fRight) {
            // to the right (facing right)
            wall3->SetPosition(sf::Vector2f(position.x + size.x, position.y));
            this->faceRight = true;
        }
        else {
            // to the left (facing left)
            wall3->SetPosition(sf::Vector2f(position.x - size.x, position.y));
            this->faceRight = false;
        }
    }
}

Wall_Corner::~Wall_Corner() { /* empty */ }

#endif  // WALL_CORNER