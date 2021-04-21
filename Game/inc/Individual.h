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

   Vector2f getSize() { return this->size; }
   float getSpeed() { return this->speed; }

   // mutators
   void setTotalHealth(int val) { this->totalHealth = val; }
   void setOriginalHealth(int val) { this->orig_health = val; }
};

Individual::Individual(Texture* texture, Vector2u imageCount, Vector2f aSize, float switchTime, float aSpeed) :
   animation(texture, imageCount, switchTime) {
    
      if (aSpeed <= 0)
          this->speed = 10.0f;
      else
          this->speed = aSpeed;

      // default row is 0
      row = 0;
      hb_row = 0;
      faceRight = true;
      movingDown = false;
      movingUp = false;

      // ensure size is valid
      if (aSize.x <= 0 || aSize.y <= 0)
          this->size = Vector2f(100.0f, 150.0f);
      else
          this->size = aSize;

      body.setSize(size);
      body.setOrigin(body.getSize() / 2.0f);
      body.setPosition(500, 500);
      body.setTexture(texture);

      //body.getSize();

      FoV.setSize(Vector2f(3.0f * size.x, 2.0f * size.y));
      FoV.setOrigin(FoV.getSize() / 2.0f);
      FoV.setFillColor(sf::Color::Transparent);
      FoV.setOutlineThickness(1.0f);

      // Can changfe to green for bounds testing
      FoV.setOutlineColor(sf::Color::Transparent);

      FoV.setPosition(body.getPosition());

      // instantiating a new health bar
      health_text.loadFromFile("imgs/healthBarv4.png");
      // switchTime multiplied by a factor to smooth out animation of health decrement
      hb = new HealthBar(&body, body.getSize(), &health_text, Vector2u(1, 20), switchTime*10.0f, speed);
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
    float perc = getHealthPercent();

    /* conditions for health bar (perc)
    *   >= 95%              = full bar [0]
    *   >= 90% and < 95%    = [1]
    *   >= 85% and < 90%    = [2]
    *   >= 80% and < 85%    = [3]
    *   >= 75% and < 80%    = [4]
    *   >= 70% and < 75%    = [5]
    *   >= 65% and < 70%    = [6]
    *   >= 60% and < 65%    = [7]
    *   >= 55% and < 60%    = [8]
    *   >= 50% and < 55%    = [9]
    *   >= 45% and < 50%    = [10]
    *   >= 40% and < 45%    = [11]
    *   >= 35% and < 40%    = [12]
    *   >= 30% and < 35%    = [13]
    *   >= 25% and < 30%    = [14]
    *   >= 20% and < 25%    = [15]
    *   >= 15% and < 20%    = [16]
    *   >= 10% and < 15%    = [17]
    *   >= 5%  and < 10%    = [18]
    *   >= 0%  and < 5%     = [19]
    */

    if (perc >= 95.0)
        hb_row = 0;
    if (perc >= 90.0 && perc < 95.0)
        hb_row = 1;
    if (perc >= 85.0 && perc < 90.0)
        hb_row = 2;
    if (perc >= 80.0 && perc < 85.0)
        hb_row = 3;
    if (perc >= 75.0 && perc < 80.0)
        hb_row = 4;
    if (perc >= 70.0 && perc < 75.0)
        hb_row = 5;
    if (perc >= 65.0 && perc < 70.0)
        hb_row = 6;
    if (perc >= 60.0 && perc < 65.0)
        hb_row = 7;
    if (perc >= 55.0 && perc < 60.0)
        hb_row = 8;
    if (perc >= 50.0 && perc < 55.0)
        hb_row = 9;
    if (perc >= 45.0 && perc < 50.0)
        hb_row = 10;
    if (perc >= 40.0 && perc < 45.0)
        hb_row = 11;
    if (perc >= 35.0 && perc < 40.0)
        hb_row = 12;
    if (perc >= 30.0 && perc < 35.0)
        hb_row = 13;
    if (perc >= 25.0 && perc < 30.0)
        hb_row = 14;
    if (perc >= 20.0 && perc < 25.0)
        hb_row = 15;
    if (perc >= 15.0 && perc < 20.0)
        hb_row = 16;
    if (perc >= 10.0 && perc < 15.0)
        hb_row = 17;
    if (perc >= 5.0 && perc < 10.0)
        hb_row = 18;
    if (perc >= 0.0 && perc < 5.0)
        hb_row = 19;
    else { /* intentionally empty */ }
    

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