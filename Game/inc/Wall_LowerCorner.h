/* Copyright 2020 Samuel Dunny */
/* Wall class (in header file) */

#ifndef WALL_LOWERCORNER
#define WALL_LOWERCORNER

#include "Wall_Interface.h"

/*
 * will construct and draw the following
    1                         1
    @@@@                      @@@@
    @  @                      @  @
    @  @                      @  @
    @@@@                      @@@@
    2     3             3     2
    @@@@  @@@@          @@@@  @@@@
    @  @  @  @          @  @  @  @
    @  @  @  @          @  @  @  @
    @@@@  @@@@    or    @@@@  @@@@

    faceRight =         faceRight =
    True                False
 */

class Wall_LowerCorner: public Wall_Interface {
private:

public:
    Wall_LowerCorner(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position, bool faceRight);

    ~Wall_LowerCorner();

    // takes in window reference, draws player
    void Draw(sf::RenderWindow& window);

    // needed this method in this class, as referencing in Game_Engine would not work
    bool ColliderCheck(Collider other, float push);

    // every 'solid' object in game needs this method for collision
    Collider* GetColliders() {
        Collider colARR[3] = { Collider(wall1, wall1View, wall1HB),
                               Collider(wall2, wall2View, wall2HB),
                               Collider(wall3, wall3View, wall3HB) };
        return colARR;
    }
    
};

Wall_LowerCorner::Wall_LowerCorner(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position, bool faceRight) {

    wall1.setSize(size);
    wall1.setOrigin(size / 2.0f);
    wall1.setTexture(texture);
    // place this wall a square above the corner wall (square 2)
    wall1.setPosition(position.x, position.y - size.y);

    wall2.setSize(size);
    wall2.setOrigin(size / 2.0f);
    wall2.setTexture(texture);
    // place this wall at designated coordinates (corner square)
    wall2.setPosition(position);

    // if faceRight = true, square 3 will be placed on right side of square 2
    // origin will be based off corner square (square 2)
    if (faceRight) {
        wall3.setSize(size);
        wall3.setOrigin(size / 2.0f);
        wall3.setTexture(texture);
        // place this wall a square right of the corner wall (square 2)
        wall3.setPosition(position.x + size.x, position.y);
    }
    else {
        wall3.setSize(size);
        wall3.setOrigin(size / 2.0f);
        wall3.setTexture(texture);
        // place this wall a square left of the corner wall (square 2)
        wall3.setPosition(position.x - size.x, position.y);
    }
}

Wall_LowerCorner::~Wall_LowerCorner() { /* empty */ }

void Wall_LowerCorner::Draw(sf::RenderWindow& window) {
    window.draw(wall1);
    window.draw(wall2);
    window.draw(wall3);
}

bool Wall_LowerCorner::ColliderCheck(Collider other, float push) {
    // return GetCollider().CheckCollision(other, push);
    Collider* checkWalls = GetColliders();
    return checkWalls[1].CheckCollision(other, push) ||
            checkWalls[2].CheckCollision(other, push) ||
            checkWalls[3].CheckCollision(other, push);
}



#endif