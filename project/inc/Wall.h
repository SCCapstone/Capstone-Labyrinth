/* Copyright 2020 Samuel Dunny */
/* Collider class (in header file) */

#ifndef WALL_H
#define WALL_H

#include <SFML/Graphics.hpp>
#include "Collider.h"

class Wall {
// private attributes
private:
    sf::RectangleShape wall;

// public attributes
public:
    Wall(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position);
    ~Wall();

    // takes in window reference, draws player
   void Draw(sf::RenderWindow& window);

    // every 'solid' object in game needs this method for collision
   Collider GetCollider() { return Collider(wall); }

   bool ColliderCheck(Collider other, float push);

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
    GetCollider().CheckCollision(other, push);
}

#endif  // COLLIDER_H