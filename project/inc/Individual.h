/* Copyright 2020 Samuel Dunny */
/* Individual class (in header file) */

#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include "Animation.h"
#include "Collider.h"

// from sf library
using sf::RenderWindow;
using sf::Texture;
using sf::Vector2f;
using sf::RectangleShape;
using sf::Keyboard;

#define body_height 150.0f
#define body_width 100.0f

class Individual {
// private attributes
protected:
   /* using RectangleSHape for this class instead of Sprite so we can use sprite sheets 
      instead of a bunch of sprites with different textures */
   RectangleShape body;
   RectangleShape FoV;

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

   int base_attackVal = 10;
   int totalHealth = 100;

// public attributes
public:
   /* constructor
    * only need pointer to texture for size
    * imageCount for number of images in sheet
    * switchTime for frame rate
    */
   Individual(Texture* texture, Vector2u imageCount, float switchTime, float speed);

   // destructor
   virtual ~Individual();

   // takes in window reference, draws player
   void Draw(RenderWindow& window);

   // needed this method in this class, as referencing in Game_Engine would not work
   bool ColliderCheck(Collider other, float push);

   // checks if vision fields collide
   bool VisionColliderCheck(Collider other, float push);

   bool isColliding(Collider other);

   // attack function
   void commitAttack(Individual& other);

   
   // accessors
   int getTotalHealth() { return this->totalHealth; }
   int getAttackValue() { return this->base_attackVal; }
   float getSpeed() { return this->speed; }
   Vector2f getIndividualPos() { return body.getPosition(); }
   Collider GetCollider() { return Collider(body, FoV); }

   // mutators
   void setTotalHealth(int val) { this->totalHealth = val; }
   void setAttackValue(int val) { this->base_attackVal = val; }
   void setSpeed(float sp) { this->speed = sp; }
};

Individual::Individual(Texture* texture, Vector2u imageCount, float switchTime, float speed) :
   animation(texture, imageCount, switchTime) {

      this->speed = speed;

      // default row is 0
      row = 0;
      faceRight = true;

      body.setSize(Vector2f(body_width, body_height));
      body.setOrigin(body.getSize() / 2.0f);

      body.setPosition(500, 500);
      body.setTexture(texture);

      FoV.setSize(Vector2f(3.0f * body_width, 2.0f * body_height));
      FoV.setOrigin(FoV.getSize() / 2.0f);
      FoV.setFillColor(sf::Color::Transparent);
      FoV.setOutlineThickness(1.0f);
      FoV.setOutlineColor(sf::Color::Green);
      FoV.setPosition(body.getPosition());
}

Individual::~Individual(){ /* empty */ }

void Individual::Draw(RenderWindow& window) {
   // draw the new movement
   window.draw(body);
   window.draw(FoV);
}

// wall_one->GetCollider().CheckCollision(player->GetCollider(), 0.0f);
bool Individual::ColliderCheck(Collider other, float push) {
    // returns the body's collider, checks with other's collider
    return GetCollider().CheckCollision(other, push);
}

bool Individual::VisionColliderCheck(Collider other, float push) {
    // returns the FoV's collider, checks with other
    return GetCollider().CheckVisionCollision(other, push);
}

bool Individual::isColliding(Collider other) {
   return GetCollider().isColliding(other);
}

void Individual::commitAttack(Individual& other) {
   //std::cout << "Attacking" << std::endl;
   //std::cout << "  Pre Attack: " << other.getTotalHealth() << std::endl;
   float damage = other.getTotalHealth() - getAttackValue();
   other.setTotalHealth(damage);
   std::cout << "  Post Attack Health: " << other.getTotalHealth() << std::endl;
}

#endif  // INDIVIDUAL_H