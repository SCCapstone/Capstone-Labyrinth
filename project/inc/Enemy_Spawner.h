/* Copyright 2020 Samuel Dunny */
/* Player class (in header file) */

#ifndef ENEMY_SPAWNER_H
#define ENEMY_SPAWNER_H

#include "Enemy.h"
#include "Player.h"

class Enemy_Spawner {
// private attributes
private:
    int type;
    int amount;
    int timeToSpawn;

    // array of enemy pointer objects
    Enemy** enemies;
    
// public attributes
public:
    Enemy_Spawner(int us_amount, int us_time, int attVal, Texture* texture, Vector2u imageCount, float switchTime, float speed);
    ~Enemy_Spawner();

    void Populate(Texture* texture, Vector2u imageCount, float switchTime, float speed, int attVal);

    void Spawn(RenderWindow& window);

    // TODO add chase
    void Chase(Player& player, float deltaTime);

    void Update(float deltaTime);
};

Enemy_Spawner::Enemy_Spawner(int us_amount, int us_time, int attVal, Texture* texture, Vector2u imageCount, float switchTime, float speed) {
    this->amount = us_amount;
    this->timeToSpawn = us_time;

    // dynamically allocate new array
    enemies = new Enemy*[amount];

    Populate(texture, imageCount, switchTime, speed, attVal);    
}

// responsible for deleting all enemies in array, then array itself
Enemy_Spawner::~Enemy_Spawner() {
    for (int i = 0; i < amount; i++) {
        delete enemies[i];
    }
    delete enemies;
}

// responsible for dynamically allocating memory for all enemies and setting their attack values
void Enemy_Spawner::Populate(Texture* texture, Vector2u imageCount, float switchTime, float speed, int attVal) {
    for (int i = 0; i < amount; i++) {
        enemies[i] = new Enemy(texture, imageCount, switchTime, speed);
        enemies[i]->setAttackValue(attVal);
    }
}

// responsible for placing all enemy objects randomly in window
void Enemy_Spawner::Spawn(RenderWindow& window) {
    for (int i = 0; i < amount; i++) {
        enemies[i]->setRandPos();
        //enemies[i]->Draw(window);
    }
}

// responsible for updating enemies (movement and animatio)
void Enemy_Spawner::Update(float deltaTime) {
    for (int i = 0; i < amount; i++) {
        enemies[i]->Update(deltaTime);
    }
}

#endif  // ENEMY_SPAWNER_H