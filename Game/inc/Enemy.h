/* Copyright 2020 Samuel Dunny */
/* Enemy class (in header file) */

#ifndef ENEMY_H
#define ENEMY_H

#include "Individual.h"
#include "Wall.h"
#include <io.h>     // #include <unistd.h> doesn't port to windows

class Enemy : public Individual {
// private attributes
private:
    // used to time out attacks for enemies
    sf::Clock enemy_attackTimer;
    sf::Int32 enemy_attackTimerMax;
    
// public attributes
public:
    Enemy(Texture* texture, Vector2u imageCount, Vector2f size, float switchTime, float speed, int health, int attVal);

    ~Enemy();

    void Update(float deltaTime, int rv);

    void setRandPos(Vector2f initialCoords, Vector2f finalCoords);

    // for boss
    void setPos(Vector2f initialCoords);

    void Chase(Player& player, float deltaTime);

    void ConstantAttack(Individual& other);

    const bool getAttackTimer();

    void commitAttack(Individual& other);

    
};

Enemy::Enemy(Texture* texture, Vector2u imageCount, Vector2f size, float switchTime, float speed, int health, int attVal) :
        Individual(texture, imageCount, size, switchTime, speed) {
    this->enemy_attackTimer.restart();

    this->base_attackVal = attVal;

    // this is in milliseconds (enemy attacks every 3 seconds)
    this->enemy_attackTimerMax = 1000;
    setTotalHealth(health);
    setOriginalHealth(health);
}

Enemy::~Enemy() { /* empty */ }

void Enemy::Update(float deltaTime, int rv) {
    Vector2f movement(0.0f, 0.0f);

    // left
    if (rv == 4) 
        movement.x -= speed * deltaTime;
    // right
    if (rv == 2) 
        movement.x += speed * deltaTime;
    // up
    if (rv == 1) 
        movement.y -= speed * deltaTime;
    // down
    if (rv == 3)
        movement.y += speed * deltaTime;
    if (rv == 5) {
        movement.x = 0.0f;
        movement.y = 0.0f;
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
        if (movement.y > 0.0f) {
            row = 0;
            movingDown = true;
            movingUp = false;
        }
        // moving up
        if (movement.y < 0.0f) {
            row = 2;
            movingUp = true;
            movingDown = false;
        }
        // intentionally empty
        else {}
    }

   // update the animation
   animation.Update(row, deltaTime, faceRight, movingDown, movingUp);

   body.setTextureRect(animation.uvRect);   // update the character rectangle

   // update the health bar's animation and rectangle
   UpdateHealthBar(deltaTime);

   body.move(movement);     // move the character
   FoV.move(movement);      // move the characters field of vision
   hb->Move(movement);      // move the enemies healthbar
}

void Enemy::setRandPos(Vector2f initialC, Vector2f finalC) {

    // find range between given coordinates
    float x_max = abs(initialC.x) + abs(finalC.x);
    float y_max = abs(initialC.y) + abs(finalC.y);

    //std::cout << "MAX COORDS: " << x_max << ", " <<y_max << std::endl;

    
    float x_rand = 0.0f;
    float y_rand = 0.0f;

    while (x_rand == 0.0f ||  y_rand == 0.0f) {
        //srand((unsigned)time(0));
        x_rand = float(rand() % (int)x_max + 1);
        y_rand = float(rand() % (int)y_max + 1);
    }

    //float x_rand = float(rand() % (int)x_max + 1);
    //float y_rand = float(rand() % (int)y_max + 1);

    //std::cout << "\tRAND COORDS: " << x_rand << ", " << y_rand << std::endl;

    float x_coord = 0.0f;
    float y_coord = 0.0f;

    // upper right quadrant
    if (initialC.x < finalC.x && initialC.y > finalC.y) {
        x_coord = scale * (x_rand - abs(initialC.x));
        y_coord = -1.0f * scale * (y_rand - abs(initialC.y));
    }
    // lower right quadrant
    else if (initialC.x < finalC.x && initialC.y < finalC.y) {
        x_coord = scale * (x_rand - abs(initialC.x));
        y_coord = scale * (y_rand - abs(initialC.y));
    }
    // lower left quadrant
    else if (initialC.x > finalC.x && initialC.y < finalC.y) {
        x_coord = -1.0f * scale * (x_rand - abs(initialC.x));
        y_coord = scale * (y_rand - abs(initialC.y));
    }
    // upper left quadrant
    else {
        x_coord = -1.0f * scale * (x_rand - abs(initialC.x));
        y_coord = -1.0f * scale * (y_rand - abs(initialC.y));
    }

    //std::cout << "\tFINAL COORDS: " << x_coord << ", " << y_coord << std::endl;

    body.setPosition(x_coord, y_coord);

    // can set to red for bounds testing
    FoV.setOutlineColor(sf::Color::Transparent);

    // ensure enemy's outline spawns with enemy
    FoV.setPosition(body.getPosition());

    // setting health bar's positon to match enemies
    hb->setPos(sf::Vector2f(body.getPosition().x, body.getPosition().y - (3.0f * body.getSize().y / 4.0f)));
}

// for boss types to manually set position (instead of randomly)
void Enemy::setPos(Vector2f coords) {
    body.setPosition(coords);

    // reset boss's outline to tranparent
    FoV.setOutlineColor(sf::Color::Transparent);

    // ensure enemy's outline spawns with enemy
    FoV.setPosition(body.getPosition());

    // setting health bar's positon to match enemies
    hb->setPos(sf::Vector2f(body.getPosition().x, body.getPosition().y - (3.0f * body.getSize().y / 4.0f)));
}

void Enemy::Chase(Player& player, float deltaTime) {
    Vector2f playerPos = player.getIndividualPos();
    Vector2f enemyPos = getIndividualPos();

    Vector2f movement(0.0f, 0.0f);

    float deltaX = playerPos.x - enemyPos.x;
    float deltaY = playerPos.y - enemyPos.y;

    // movement speed is tripled for chasing effect

    // left
    if (deltaX < 0) 
        movement.x -= 3.0f * speed * deltaTime;
    // right
    if (deltaX > 0) 
        movement.x += 3.0f * speed * deltaTime;
    // up
    if (deltaY < 0) 
        movement.y -= 3.0f * speed * deltaTime;
    // down
    if (deltaY > 0)
        movement.y += 3.0f * speed * deltaTime;

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
        if (movement.y > 0.0f) {
            row = 0;
            movingDown = true;
            movingUp = false;
        }
        // moving up
        if (movement.y < 0.0f) {
            row = 2;
            movingUp = true;
            movingDown = false;
        }
        // intentionally empty
        else {}
    }

    // update the animation
    animation.Update(row, deltaTime, faceRight, movingDown, movingUp);
    
    body.setTextureRect(animation.uvRect);  // update the character rectangle
   
    // update the health bar's animation and rectangle
    UpdateHealthBar(deltaTime);

    body.move(movement);    // move the character
    FoV.move(movement);     // move the characters field of vision
    hb->Move(movement);     // move the enemies healthbar
}

void Enemy::ConstantAttack(Individual& other) {
    if (getAttackTimer()) {
        commitAttack(other);        
    }
}

// this funciton returns true if it is time for enemy to attack 
const bool Enemy::getAttackTimer() {
    if (this->enemy_attackTimer.getElapsedTime().asMilliseconds() >= this->enemy_attackTimerMax) {
        this->enemy_attackTimer.restart();
        return true;
    }
    return false;
}

// overriding Individual commitAttack() method
void Enemy::commitAttack(Individual& other) {
   //std::cout << "Attacking" << std::endl;
   //std::cout << "  Pre Attack: " << other.getTotalHealth() << std::endl;
   int damage = other.getTotalHealth() - getAttackValue();
   other.setTotalHealth(damage);
   std::cout << "  Post Attack Player Health: " << other.getTotalHealth() << std::endl;
   std::cout << "       Original Player Health: " << other.getOrignalHealth() << std::endl;
   std::cout << "       Player Health Percentage: " << other.getHealthPercent() << std::endl;
}

#endif  // ENEMY_H