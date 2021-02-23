/* Copyright 2020 Samuel Dunny */
/* Individual class (in header file) */

#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include "Animation.h"
#include "Collider.h"
#include "HealthBar.h"

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

   // declare new health bar object
   HealthBar* hb;
   // loading sprite sheet
   Texture health_text;
   unsigned int hb_row;

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
   int orig_health = totalHealth;

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
   
   // accessors
   int getTotalHealth() { return this->totalHealth; }
   int getOrignalHealth() { return this->orig_health; }
   int getAttackValue() { return this->base_attackVal; }
   float getSpeed() { return this->speed; }
   Vector2f getIndividualPos() { return body.getPosition(); }
   Collider GetCollider() { return Collider(body, FoV); }

   // mutators
   void setTotalHealth(int val) { this->totalHealth = val; }
   void setOriginalHealth(int val) { this->orig_health = val; }
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

      // instantiating a new health bar
      health_text.loadFromFile("imgs/healthbar.png");
      hb = new HealthBar(&body, Vector2f(body_width, body_height), &health_text, Vector2u(1, 5), switchTime, speed);
}

Individual::~Individual(){ /* empty */ }

void Individual::Draw(RenderWindow& window) {
   // draw the new movement
   window.draw(body);
   window.draw(FoV);

   // draw health bar
   hb->Draw(window);
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

#endif  // INDIVIDUAL_H