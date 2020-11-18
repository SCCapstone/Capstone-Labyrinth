/* Copyright 2020 Samuel Dunny */
/* Player class (in header file) */

#ifndef ENEMY_SPAWNER_H
#define ENEMY_SPAWNER_H

#include "Enemy.h"

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
    Enemy_Spawner(int us_type, int us_amount, int us_time);
    ~Enemy_Spawner();

    void Populate(Texture* texture, Vector2u imageCount, float switchTime, float speed);

    void Spawn();

    void Update(float deltaTime);
    
};

Enemy_Spawner::Enemy_Spawner(int us_type, int us_amount, int us_time) {
    this->type = us_type;
    this->amount = us_amount;
    this->timeToSpawn = us_time;

    // dynamically allocate new array
    enemies = new Enemy*[amount];
}

Enemy_Spawner::~Enemy_Spawner() {
    delete enemies;
}

void Enemy_Spawner::Populate(Texture* texture, Vector2u imageCount, float switchTime, float speed) {
    for (int i = 0; i < amount; i++) {
        enemies[i] = new Enemy(texture, imageCount, switchTime, speed);
    }
}

void Enemy_Spawner::Spawn() {
    
}

void Enemy_Spawner::Update(float deltaTime) {
    for (int i = 0; i < amount; i++) {
        enemies[i]->Update(deltaTime);
    }

}

#endif  // ENEMY_SPAWNER_H