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
    Player(Texture* texture, Vector2u imageCount, Vector2f size, float switchTime, float speed, int health, int attVal);

    ~Player();

    void Update(float time);

    void Attack(Individual& other);

    void commitAttack(Individual& other);

    const bool getAttackTimer();
};

Player::Player(Texture* texture, Vector2u imageCount, Vector2f size, float switchTime, float speed, int health, int attVal):
        Individual(texture, imageCount, size, switchTime, speed) {
   this->player_attackTimer.restart();

   this->base_attackVal = attVal;

   // this is in milliseconds (player attacks every second)
   this->player_attackTimerMax = 150;

   // always starting player at the origin
   body.setPosition(0.0f,0.0f);
   FoV.setPosition(body.getPosition());
   hb->setPos(sf::Vector2f(body.getPosition().x, body.getPosition().y - (3.0f * body.getSize().y / 4.0f)));

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
    *   > 91%       = full bar [0]
    *   90%  - 81%  = [1]
    *   80%  - 71%  = [2]
    *   70%  - 61%  = [3]
    *   60%  - 51%  = [4]
    *   50%  - 41%  = [5]
    *   40%  - 31%  = [6]
    *   30%  - 21%  = [7]
    *   20%  - 11%  = [8]
    *   10%  - 1%   = [9]
    *   1% <        = [10]
    */
   float perc = getHealthPercent();
   if (perc > 91.0)
       hb_row = 0;
   if (perc <= 90.0 && perc > 81.0)
       hb_row = 1;
   if (perc <= 80.0 && perc > 71.0)
       hb_row = 2;
   if (perc <= 70.0 && perc > 61.0)
       hb_row = 3;
   if (perc <= 60.0 && perc > 51.0)
       hb_row = 4;
   if (perc <= 50.0 && perc > 41.0)
       hb_row = 5;
   if (perc <= 40.0 && perc > 31.0)
       hb_row = 6;
   if (perc <= 30.0 && perc > 21.0)
       hb_row = 7;
   if (perc <= 20.0 && perc > 11.0)
       hb_row = 8;
   if (perc <= 10.0)
       hb_row = 9;
   else {/* intentionally empty */ }   

   // update the animation
   animation.Update(row, deltaTime, faceRight, movingDown, movingUp);
   // update health bar animation
   hb->Update(hb_row, deltaTime);

   
   body.setTextureRect(animation.uvRect);   // update the character rectangle
   hb->setTextureRectangle();               // update the health bar rectangle

   body.move(movement); // move the character
   FoV.move(movement);  // ensure players field of vision moves with them
   hb->Move(movement);  // move health bar along with player
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
   int damage = other.getTotalHealth() - getAttackValue();
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