/* Copyright 2020 Samuel Dunny */
/* Player class (in header file) */

#ifndef PLAYER_H
#define PLAYER_H

#include "Individual.h"

class Player : public Individual {
// private attributes
private:
   // used to time out attacks for player
    sf::Clock player_attackTimer;
    sf::Int32 player_attackTimerMax;
  
// public attributes
public:
    Player(Texture* texture, Vector2u imageCount, float switchTime, float speed, int health);

    ~Player();

    void Update(float time);

    void Attack(Individual& other);

    void commitAttack(Individual& other);

    const bool getAttackTimer();
};

Player::Player(Texture* texture, Vector2u imageCount, float switchTime, float speed, int health):
        Individual(texture, imageCount, switchTime, speed) {
   this->player_attackTimer.restart();

   // this is in milliseconds (player attacks every second)
   this->player_attackTimerMax = 150;

   setTotalHealth(health);
   setOriginalHealth(health);
}

Player::~Player() {/* empty */}

void Player::Update(float deltaTime) {
   Vector2f movement(0.0f, 0.0f);

   // update movement based on key press
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
      row = 1;
   else {
      // running left and right animations
      if (movement.x != 0.0f) {
         row = 3;
         if (movement.x > 0.0f)
            faceRight = true;
         else
            faceRight = false;
      }
      // moving down
      if (movement.y > 0.0f){
         row = 1;
         movingDown = true;
         movingUp = false;
      }
      // moving up
      if (movement.y < 0.0f){
         row = 0;
         movingUp = true;
         movingDown = false;
      }
      else {/* intentionally empty */}
   }

   /* conditions for health bar 
    *   100% - 81%  = full bar [4]
    *   61% - 80%   = 75% bar
    *   41% - 60%   = 50% bar
    *   21% - 40%   = 25% bar
    *   0% - 20%    = empty bar
    */
   float perc = getHealthPercent();
   if (perc > 81.0)
       hb_row = 4;
   if (perc <= 80.0 && perc > 61.0)
       hb_row = 3;
   if (perc <= 60.0 && perc > 41.0)
       hb_row = 2;
   if (perc <= 40.0 && perc > 21.0)
       hb_row = 1;
   if (perc <= 20)
       hb_row = 0;
   else {/* intentionally empty */ }

   // update the animation
   animation.Update(row, deltaTime, faceRight, movingDown, movingUp);

   // update health bar animation
   // health_anim.Update(hb_row, deltaTime, false, true, true);
   hb->Update(hb_row, deltaTime);

   // update the character rectangle
   body.setTextureRect(animation.uvRect);

   // update the health bar rectangle
   // healthbar.setTextureRect(health_anim.uvRect);
   hb->setTextureRectangle();

   // move the character
   body.move(movement);

   // ensure players field of vision moves with them
   FoV.move(movement);

   // move health bar along with player
   // healthbar.move(movement);
   hb->Move(movement);
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

// this function returns true if it is time for player to attack 
const bool Player::getAttackTimer() {
    if (this->player_attackTimer.getElapsedTime().asMilliseconds() >= this->player_attackTimerMax) {
        this->player_attackTimer.restart();
        return true;
    }
    return false;
}
#endif  // PLAYER_H