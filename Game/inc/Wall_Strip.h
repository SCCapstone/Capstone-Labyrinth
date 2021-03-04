/* Copyright 2021 Samuel Dunny */
/* Wall_Strip (in header file) */

#ifndef WALL_STRIP
#define WALL_STRIP

#include "WallBuilder.h"

/*
 * will construct and draw the following

   1     2     3
   @@@@  @@@@  @@@@
   @  @  @  @  @  @
   @  @  @  @  @  @
   @@@@  @@@@  @@@@

          or

   @@@@ 1
   @  @
   @  @
   @@@@

   @@@@ 2
   @  @
   @  @
   @@@@

   @@@@ 3
   @  @
   @  @
   @@@@

 */

class Wall_Strip: public WallBuilder {
private:
    // conditions for the strip orientation (not necessary, might use later)
    bool horizontal;

public:
    Wall_Strip(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position, bool horiz);

    ~Wall_Strip();
};

Wall_Strip::Wall_Strip(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position, bool hor):
    WallBuilder(texture, size, position) {
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

Wall_Strip::~Wall_Strip() { /* empty */ }

#endif  // WALL_CORNER