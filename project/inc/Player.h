/* Copyright 2020 Samuel Dunny */
/* Player class (in header file) */

#ifndef PLAYER_H
#define PLAYER_H

#include "Animation.h"

// from std library
using std::string;
using std::cout;
using std::endl;

// from sf library
using sf::RenderWindow;
using sf::Texture;
using sf::Sprite;
using sf::Vector2f;
using sf::View;

class Player {
// private attributes
private:
   /* using RectangleSHape for this class instead of Sprite so we can use sprite sheets 
      instead of a bunch of sprites with different textures */
   sf::RectangleShape body;

   // creating instance of animation (to animate body)
   Animation animation;

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
   Player(Texture* texture, Vector2u imageCount, float switchTime, float speed);
   ~Player();

   void Update(float deltaTime);

   void Draw(RenderWindow& window);

   Vector2f getPlayerPos() {
      return body.getPosition();
   }

};

// player constructor definition
Player::Player(Texture* texture, Vector2u imageCount, float switchTime, float speed) :
   animation(texture, imageCount, switchTime) {

      this->speed = speed;
      row = 0;
      faceRight = true;

      // TODO fix magic numbers
      body.setSize(Vector2f(100.0f, 150.0f));
      body.setOrigin(body.getSize() / 2.0f);
      body.setPosition(700, 350);
      body.setTexture(texture);
}

// player destructor definition
Player::~Player(){}

// update function, responds to keyboard input and sets instance values accordingly
void Player::Update(float deltaTime) {
   sf::Vector2f movement(0.0f, 0.0f);

   // TODO add other directions
   if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
      movement.x -= speed * deltaTime;
   }
   if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
      movement.x += speed * deltaTime;
   }
   if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
      movement.y -= speed * deltaTime;
   }
   if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
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

// takes in window reference, draws player
void Player::Draw(sf::RenderWindow& window) {
   // draw the new movement
   window.draw(body);
}

#endif  // PLAYER_H