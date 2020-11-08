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

// public attributes
public:
   Player(Texture* texture, Vector2u imageCount, float switchTime, float speed);
   ~Player();

   void Update(float deltaTime);

   void Draw(RenderWindow& window);
};

Player::Player(Texture* texture, Vector2u imageCount, float switchTime, float speed) :
   animation(texture, imageCount, switchTime) {

      this->speed = speed;
      row = 0;
      faceRight = true;

      // TODO fix magic numbers
      body.setSize(Vector2f(100.0f, 150.0f));
      body.setPosition(700, 350);
      body.setTexture(texture);
}

Player::~Player(){}

void Player::Update(float deltaTime) {
   sf::Vector2f movement(0.0f, 0.0f);

   // TODO add other directions
   if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
      movement.x -= speed * deltaTime;
   }
   if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
      movement.x += speed * deltaTime;
   }

   // idle animation
   if (movement.x == 0.0f)
      row = 2;
   // running animations
   else {
      row = 2;
      if (movement.x > 0.0f)
         faceRight = true;
      else
         faceRight = false;
   }

   animation.Update(row, deltaTime, faceRight);
   body.setTextureRect(animation.uvRect);
   body.move(movement);
}

void Player::Draw(sf::RenderWindow& window) {
   window.draw(body);
}

#endif  // PLAYER_H