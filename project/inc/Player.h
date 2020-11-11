/* Copyright 2020 Samuel Dunny */
/* Player class (in header file) */

#ifndef PLAYER_H
#define PLAYER_H

#include "Animation.h"

// from sf library
using sf::RenderWindow;
using sf::Texture;
using sf::Vector2f;
using sf::RectangleShape;
using sf::Keyboard;

const float body_height = 150.0f;
const float body_width = 100.0f;

class Player {
// private attributes
private:
   /* using RectangleSHape for this class instead of Sprite so we can use sprite sheets 
      instead of a bunch of sprites with different textures */
   RectangleShape body;

   // creating instance of animation (to animate body)
   Animation animation;

   // default texture
   Texture base_movement;

   // what row of the sprite sheet we are using
   unsigned int row;

   // player speed
   float speed;

   // whether the player is facing left or right (used so we dont have to create left and right animations)
   bool faceRight;

   bool movingUp;
   bool movingDown;

// public attributes
public:
   /* constructor
    * only need pointer to texture for size
    * imageCount for number of images in sheet
    * switchTime for frame rate
    */
   Player(Texture* texture, Vector2u imageCount, float switchTime, float speed);

   // destructor
   ~Player();

   // mutators
   void charSetTexture(Texture* texture);
   void charSetImageCount(Vector2u imageCount);
   void charSetSwitchTime(float switchTime);
   void charSetSpeed(float speed);

   // update function, responds to keyboard input and sets instance values accordingly
   void Update(float deltaTime);

   // takes in window reference, draws player
   void Draw(RenderWindow& window);

   // returns player position, used when setting center view in Game_Engine
   Vector2f getPlayerPos() {
      return body.getPosition();
   }

};

Player::Player(Texture* texture, Vector2u imageCount, float switchTime, float speed) :
   animation(texture, imageCount, switchTime) {

      this->speed = speed;

      // default row is 0
      row = 0;
      faceRight = true;

      body.setSize(Vector2f(body_width, body_height));
      body.setOrigin(body.getSize() / 2.0f);

      /* centers character in the middle of the initial screen
       * the resize function in Game-Engine will keep it center if window changes
      */
      body.setPosition(500, 500);
      body.setTexture(texture);
}

Player::~Player(){ /* blank, no allocation */ }

// mutators
void Player::charSetTexture(Texture* texture) {
   animation.setAnimationTexture(texture);
}
   
void Player::charSetImageCount(Vector2u imageCount) {
   animation.setImageCount(imageCount);
}
   
void Player::charSetSwitchTime(float switchTime) {
   animation.setSwitchTime(switchTime);
}
   
void Player::charSetSpeed(float speed) {
   this->speed = speed;
}

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
}

void Player::Draw(RenderWindow& window) {
   // draw the new movement
   window.draw(body);
}

#endif  // PLAYER_H