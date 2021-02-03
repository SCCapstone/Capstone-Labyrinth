/* Copyright 2020 Samuel Dunny */
/* Player class (in header file) */

#ifndef ENEMY_H
#define ENEMY_H

#include "Individual.h"
// #include <unistd.h>	// doesn't port to windows
#include <io.h>

class Enemy : public Individual {
// private attributes
private:
    // used to time out attacks for enemies
    sf::Clock enemy_attackTimer;
    sf::Int32 enemy_attackTimerMax;
    
// public attributes
public:
    Enemy(Texture* texture, Vector2u imageCount, float switchTime, float speed);

    ~Enemy();

    void Update(float deltaTime, int rv);

    void setRandPos();

    void Chase(Player& player, float deltaTime);

    void ConstantAttack(Individual& other);

    const bool getAttackTimer();

    void commitAttack(Individual& other);
};

Enemy::Enemy(Texture* texture, Vector2u imageCount, float switchTime, float speed) :
        Individual(texture, imageCount, switchTime, speed) {
    this->enemy_attackTimer.restart();

    // this is in milliseconds (enemy attacks every 3 seconds)
    this->enemy_attackTimerMax = 1000;
}

Enemy::~Enemy() { /* empty */ }

void Enemy::Update(float deltaTime, int rv) {
    Vector2f movement(0.0f, 0.0f);

    //srand((unsigned) time(0));

    // deciding random direction for npc to walk
    //int p1 = rand() % 5 + 1;

    // TODO add other directions

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

   // update the character rectangle
   body.setTextureRect(animation.uvRect);
   FoV.setTextureRect(animation.uvRect);

   // move the character
   body.move(movement);

   // move the characters field of vision
   FoV.move(movement);
}

void Enemy::setRandPos() {

    // finding two random spawn coordinates
    int p1 = rand() % 1000 + 1;
    int p2 = rand() % 1000 + 1;

    body.setPosition(p1, p2);

    // reset enemy's outline to red
    FoV.setOutlineColor(sf::Color::Red);

    // ensure enemy's outline spawns with enemy
    FoV.setPosition(body.getPosition());
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

    // update the character rectangle
    body.setTextureRect(animation.uvRect);
    FoV.setTextureRect(animation.uvRect);

    // move the character
    body.move(movement);

    // move the characters field of vision
    FoV.move(movement);
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
   float damage = other.getTotalHealth() - getAttackValue();
   other.setTotalHealth(damage);
   std::cout << "  Post Attack Player Health: " << other.getTotalHealth() << std::endl;
}

#endif  // ENEMY_H