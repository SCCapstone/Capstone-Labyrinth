/* Copyright 2020 Samuel Dunny */
/* Player class (in header file) */

#ifndef PLAYER_H
#define PLAYER_H

#include "inc/Individual.h"

class Player : public Individual {
// private attributes
private:
   // used to time out attacks for player
    sf::Clock player_attackTimer;
    sf::Int32 player_attackTimerMax;
  
// public attributes
public:
    Player(Texture* texture, Vector2u imageCount, float switchTime, float speed);

    ~Player();

    void Update(float time);

    void Attack(Individual& other);

    void commitAttack(Individual& other);

    const bool getAttackTimer();
};

Player::Player(Texture* texture, Vector2u imageCount, float switchTime, float speed):
        Individual(texture, imageCount, switchTime, speed) {
   this->player_attackTimer.restart();

   // this is in milliseconds (player attacks every second)
   this->player_attackTimerMax = 100;

   setTotalHealth(300);
}

Player::~Player() {/* empty */}

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

void Player::Attack(Individual& other) {
   if (getAttackTimer()) {
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
         if (other.getTotalHealth() > getAttackValue()) {
            commitAttack(other);
         }
      }
    }
}

void Player::commitAttack(Individual& other) {
   //std::cout << "Attacking" << std::endl;
   //std::cout << "  Pre Attack: " << other.getTotalHealth() << std::endl;
   float damage = other.getTotalHealth() - getAttackValue();
   other.setTotalHealth(damage);
   std::cout << "  Post Attack Enemy Health: " << other.getTotalHealth() << std::endl;
}

// this function returns true if it is time for enemy to attack 
const bool Player::getAttackTimer() {
    if (this->player_attackTimer.getElapsedTime().asMilliseconds() >= this->player_attackTimerMax) {
        this->player_attackTimer.restart();
        return true;
    }
    return false;
}
#endif  // PLAYER_H