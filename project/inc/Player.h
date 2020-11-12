/* Copyright 2020 Samuel Dunny */
/* Player class (in header file) */

#ifndef PLAYER_H
#define PLAYER_H

#include "inc/Individual.h"

class Player : public Individual {
// private attributes
private:
  
// public attributes
public:
    Player(Texture* texture, Vector2u imageCount, float switchTime, float speed) :
        Individual(texture, imageCount, switchTime, speed) {}

    ~Player();

    void Update(float time);
};

Player::~Player() { /* empty */}

void Player::Update(float deltaTime) {
   Vector2f movement(0.0f, 0.0f);

   // TODO add other directions
   if (Keyboard::isKeyPressed(Keyboard::Left)) {
      movement.x -= speed * deltaTime;
   }
   if (Keyboard::isKeyPressed(Keyboard::Right)) {
      movement.x += speed * deltaTime;
   }
   if (Keyboard::isKeyPressed(Keyboard::Up)) {
      movement.y -= speed * deltaTime;
   }
   if (Keyboard::isKeyPressed(Keyboard::Down)) {
      movement.y += speed * deltaTime;
   }

   // idle animation
   if (movement.x == 0.0f && movement.y == 0.0f)
      row = 0;
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
      if (movement.y > 0.0f){
         row = 0;
         movingDown = true;
         movingUp = false;
      }
      // moving up
      if (movement.y < 0.0f){
         row = 3;
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

   // ensure players field of vision moves with them
   FoV.move(movement);
}

#endif  // PLAYER_H