/* Copyright 2020 Samuel Dunny */
/* Player class (in header file) */

#ifndef ENEMY_H
#define ENEMY_H

// for random placement
#include <ctime>

#include "Animation.h"
#include "Collider.h"

// from sf library
using sf::RenderWindow;
using sf::Texture;
using sf::Vector2f;
using sf::RectangleShape;
using sf::Keyboard;

//const float body_height = 150.0f;
//const float body_width = 100.0f;

#define body_height 150.0f
#define body_width 100.0f

class Enemy {
// private attributes
private:
   /* using RectangleSHape for this class instead of Sprite so we can use sprite sheets 
      instead of a bunch of sprites with different textures */
   RectangleShape body;

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
   /* constructor
    * only need pointer to texture for size
    * imageCount for number of images in sheet
    * switchTime for frame rate
    */
   Enemy(Texture* texture, Vector2u imageCount, float switchTime, float speed);

   // destructor
   ~Enemy();

   // update function, responds to keyboard input and sets instance values accordingly
   void Update(float deltaTime);

   // takes in window reference, draws player
   void Draw(RenderWindow& window);

   // returns player position, used when setting center view in Game_Engine
   Vector2f getPlayerPos() {
      return body.getPosition();
   }

   // every 'solid' object in game needs this method for collision
   Collider GetCollider() { return Collider(body); }

   // needed this method in this class, as referencing in Game_Engine would not work
   bool ColliderCheck(Collider other, float push);

};

Enemy::Enemy(Texture* texture, Vector2u imageCount, float switchTime, float speed) :
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
      srand((unsigned) time(0));

      int p1 = rand() % 1000 + 1;
      int p2 = rand() % 1000 + 1;

      body.setPosition(p1, p2);
      body.setTexture(texture);
}

Enemy::~Enemy(){ /* blank, no allocation */ }

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
      if (movement.y > 0.0f){
         row = 0;
         movingDown = true;
         movingUp = false;
      }
      // moving up
      if (movement.y < 0.0f){
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

void Enemy::Draw(RenderWindow& window) {
   // draw the new movement
   window.draw(body);
}

// wall_one->GetCollider().CheckCollision(player->GetCollider(), 0.0f);
bool Enemy::ColliderCheck(Collider other, float push) {
    return GetCollider().CheckCollision(other, push);
}

#endif  // ENEMY_H