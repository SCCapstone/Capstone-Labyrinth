/* Copyright 2020 Samuel Dunny */
/* Player class (in header file) */

#ifndef ENEMY_H
#define ENEMY_H

#include "inc/Individual.h"
// for random placement
#include <ctime>

class Enemy : public Individual {
// private attributes
private:
    
// public attributes
public:
    Enemy(Texture* texture, Vector2u imageCount, float switchTime, float speed) :
        Individual(texture, imageCount, switchTime, speed) {}

    void Update(float deltaTime);

    void setRandPos();

};

void Enemy::Update(float deltaTime) {
    Vector2f movement(0.0f, 0.0f);

    // TODO add other directions
    if (Keyboard::isKeyPressed(Keyboard::A)) {
        movement.x -= speed * deltaTime;
    }
    if (Keyboard::isKeyPressed(Keyboard::D)) {
        movement.x += speed * deltaTime;
    }
    if (Keyboard::isKeyPressed(Keyboard::W)) {
        movement.y -= speed * deltaTime;
    }
    if (Keyboard::isKeyPressed(Keyboard::S)) {
        movement.y += speed * deltaTime;
    }

    // idle animation
    if (movement.x == 0.0f && movement.y == 0.0f)
        row = 1;
    else {
        // running left and right animations
        if (movement.x != 0.0f) {
            row = 2;
            if (movement.x > 0.0f)
                faceRight = true;
            else
                faceRight = false;
        }
        // moving down
        if (movement.y > 0.0f) {
            row = 0;
            movingDown = true;
            movingUp = false;
        }
        // moving up
        if (movement.y < 0.0f) {
            row = 2;
            movingUp = true;
            movingDown = false;
        }
        // intentionally empty
        else {}
    }
    // update the animation
   animation.Update(row, deltaTime, faceRight, movingDown, movingUp);

   // update the character rectangle
   body.setTextureRect(animation.uvRect);

   // move the character
   body.move(movement);
}

void Enemy::setRandPos() {
   srand((unsigned) time(0));

   int p1 = rand() % 1000 + 1;
   int p2 = rand() % 1000 + 1;

   body.setPosition(p1, p2);
}

#endif  // ENEMY_H