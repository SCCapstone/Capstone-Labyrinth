/* Copyright 2020 Samuel Dunny */
/* Individual class (in header file) */

#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include "Collider.h"
#include "HealthBar.h"

// from sf library
using sf::RenderWindow;
using sf::Texture;
using sf::Vector2f;
using sf::RectangleShape;
using sf::Keyboard;


class Individual {
// private attributes
protected:
   /* using RectangleSHape for this class instead of Sprite so we can use sprite sheets 
      instead of a bunch of sprites with different textures */
   RectangleShape body;
   RectangleShape FoV;

   
   HealthBar* hb;           // declare new health bar object
   Texture health_text;     // loading health bar sprite sheet
   unsigned int hb_row;     // the row for the health bar animation

   Animation animation;     // creating instance of animation (to animate body)
   unsigned int row;        // what row of the sprite sheet we are using

   // inidividual attributes
   float speed;
   Vector2f size;

   
   bool faceRight;          // whether the player is facing left or right (used so we dont have to create left and right animations)
   bool movingUp;           // whether the player is moving upwards
   bool movingDown;         // whether the player is moving downwards

   int base_attackVal = 10; // default attack
   int totalHealth = 100;   // original health
   int orig_health = 100;   // initial total health

// public attributes
public:
   /* constructor
    * only need pointer to texture for size
    * imageCount for number of images in sheet
    * switchTime for frame rate
    */
   Individual(Texture* texture, Vector2u imageCount, Vector2f size, float switchTime, float speed);

   // destructor
   virtual ~Individual();

   // takes in window reference, draws player
   void Draw(RenderWindow& window);

   void UpdateHealthBar(float deltaTime);

   // needed this method in this class, as referencing in Game_Engine would not work
   bool ColliderCheck(Collider other, float push);

   // checks if vision fields collide
   bool VisionColliderCheck(Collider other, float push);

   // checks if health bar fields collider
   bool HealthBarColliderCheck(Collider other, float push);
   
   // accessors
   int getTotalHealth() { return this->totalHealth; }
   int getOrignalHealth() { return this->orig_health; }
   int getAttackValue() { return this->base_attackVal; }
   float getHealthPercent() { return ((float(this->totalHealth) / float(this->orig_health)) * 100.0f);  }
   Vector2f getIndividualPos() { return body.getPosition(); }
   Vector2f getIndividualSize() { return body.getSize(); }
   sf::FloatRect GetGlobalIndividualBounds() { return body.getGlobalBounds(); }
   Collider GetCollider() { return Collider(body, FoV, hb->getHealthRect()); }

   // mutators
   void setTotalHealth(int val) { this->totalHealth = val; }
   void setOriginalHealth(int val) { this->orig_health = val; }
};

Individual::Individual(Texture* texture, Vector2u imageCount, Vector2f size, float switchTime, float speed) :
   animation(texture, imageCount, switchTime) {

      this->speed = speed;

      // default row is 0
      row = 0;
      hb_row = 0;
      faceRight = true;
      movingDown = false;
      movingUp = false;

      body.setSize(size);
      body.setOrigin(body.getSize() / 2.0f);
      body.setPosition(500, 500);
      body.setTexture(texture);

      //body.getSize();

      FoV.setSize(Vector2f(3.0f * size.x, 2.0f * size.y));
      FoV.setOrigin(FoV.getSize() / 2.0f);
      FoV.setFillColor(sf::Color::Transparent);
      FoV.setOutlineThickness(1.0f);
      FoV.setOutlineColor(sf::Color::Green);
      FoV.setPosition(body.getPosition());

      // instantiating a new health bar
      health_text.loadFromFile("imgs/healthBarv3.png");
      hb = new HealthBar(&body, body.getSize(), &health_text, Vector2u(1, 10), switchTime, speed);
}

Individual::~Individual(){ /* empty */ }

void Individual::Draw(RenderWindow& window) {
   // draw the new movement
   window.draw(body);
   window.draw(FoV);

   // draw health bar
   hb->Draw(window);
}

void Individual::UpdateHealthBar(float deltaTime) {
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

    // update health bar animation
    // health_anim.Update(hb_row, deltaTime, false, true, true);
    hb->Update(hb_row, deltaTime);

    // update the health bar rectangle
    // healthbar.setTextureRect(health_anim.uvRect);
    hb->setTextureRectangle();
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

bool Individual::HealthBarColliderCheck(Collider other, float push) {
    // returns the body's collider, checks with other's collider
    return GetCollider().CheckHealthBarCollision(other, push);
}

#endif  // INDIVIDUAL_H