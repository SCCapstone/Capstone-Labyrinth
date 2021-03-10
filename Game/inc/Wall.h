/* Copyright 2020 Samuel Dunny */
/* Wall class (in header file) */

#ifndef WALL_H
#define WALL_H

#include "Collider.h"

// scale for all wall objects
static const float scale = 250.0f;

// ranges for background display
const static float X_NEG_RANGE = -25.0f;
const static float X_POS_RANGE = 25.0f;
const static float Y_NEG_RANGE = -25.0f;
const static float Y_POS_RANGE = 25.0f;

class Wall {
// private attributes
private:
    sf::RectangleShape wall;

    // useless, needed for collider call
    sf::RectangleShape wallView;

    // useless, needed for collider call
    sf::RectangleShape wallHB;

// public attributes
public:
    Wall(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position);
    ~Wall();

    // takes in window reference, draws player
    void Draw(sf::RenderWindow& window);

    // needed this method in this class, as referencing in Game_Engine would not work
    bool ColliderCheck(Collider other, float push);

    // every 'solid' object in game needs this method for collision
    Collider GetCollider() { return Collider(wall, wallView, wallHB); }

    // mutator
    void SetPosition(Vector2f pos) { wall.setPosition(pos); }

    // accessor
    Vector2f GetPosition() { return wall.getPosition();  }

    // used to tell if enemy's coords are in wall, helps respawn somewhere else
    bool inWall(Vector2f pos) {
        sf::FloatRect bounds = wall.getGlobalBounds();
        return bounds.contains(pos);
    }
};

Wall::Wall(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position) {
    wall.setSize(size);
    wall.setOrigin(size/2.0f);
    wall.setTexture(texture);
    wall.setPosition(position);
}

Wall::~Wall() { /* empty */}

void Wall::Draw(sf::RenderWindow& window) {
   window.draw(wall);
}

// wall_one->GetCollider().CheckCollision(player->GetCollider(), 0.0f);
bool Wall::ColliderCheck(Collider other, float push) {
    return GetCollider().CheckCollision(other, push);
    sf::FloatRect bounds = wall.getGlobalBounds();
    bool cond = bounds.contains(Vector2f(0.0f, 0.0f));
}

#endif  // WALL_H