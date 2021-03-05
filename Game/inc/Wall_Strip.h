/* Copyright 2021 Samuel Dunny */
/* Wall_Strip (in header file) */

#ifndef WALL_STRIP_H
#define WALL_STRIP_H

#include "Wall_Component.h"

/* This class publicly inherits from Wall_Component
*   - uses polymorphism for instantiation
*   - creates horizontal or vertical strip of 3 wall segments (listed below)
*   - placement of segement is always based on segment 2
*   - diagram of configuration and wall segment labels

   1     2     3
   @@@@  @@@@  @@@@          @@@@ 1    horizontal =
   @  @  @  @  @  @          @  @      False
   @  @  @  @  @  @          @  @
   @@@@  @@@@  @@@@    or    @@@@

   horizontal =              @@@@ 2
   True                      @  @
                             @  @
                             @@@@

                             @@@@ 3
                             @  @
                             @  @
                             @@@@
 */

class Wall_Strip: public Wall_Component {
private:
    // conditions for the strip orientation (not necessary, might use later)
    bool horizontal;

public:
    // constructor
    Wall_Strip(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position, bool horiz);

    // destructor
    ~Wall_Strip();
};

// constructs Wall_Strip by passing 3/4 parameters to Wall_Component (polymorphism)
Wall_Strip::Wall_Strip(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position, bool hor):
    Wall_Component(texture, size, position) {
    // horizontal strip
    if (hor) {
        // wall1 will always be to the left of wall2
        wall1->SetPosition(sf::Vector2f(position.x - size.x, position.y));

        // wall2 is placed at exact coordinates (middle wall)
        wall2->SetPosition(position);

        // wall3 will always be to the right of wall2
        wall3->SetPosition(sf::Vector2f(position.x + size.x, position.y));

        this->horizontal = true;
    }
    // vertical strip
    else {
        // wall1 will always be directly over wall2
        wall1->SetPosition(sf::Vector2f(position.x, position.y - size.y));

        // wall2 is placed at exact coordinates (middle wall)
        wall2->SetPosition(position);

        // wall3 will always be directly under wall2
        wall3->SetPosition(sf::Vector2f(position.x, position.y+ size.y));
        this->horizontal = false;
    }
}

// empty destructor (handled in Game_Engine)
Wall_Strip::~Wall_Strip() { /* empty */ }

#endif  // WALL_STRIP_H