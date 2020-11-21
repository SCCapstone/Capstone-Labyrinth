/* Copyright 2020 Samuel Dunny */
/* Player class (in header file) */

#ifndef ENEMY_SPAWNER_H
#define ENEMY_SPAWNER_H

#include "Enemy.h"
#include "Player.h"
#include "Wall.h"
#include <ctime>

class Enemy_Spawner {
// private attributes
private:
int amount;
int attackValue;

// vector of enemy pointer objects
std::vector<Enemy*> enemies;
// public attributes
public:
    Enemy_Spawner(int us_amount, int attVal, Texture* texture, Vector2u imageCount, float switchTime, float speed);
    ~Enemy_Spawner();

    void Populate(Texture* texture, Vector2u imageCount, float switchTime, float speed, int attVal);

    void Spawn(RenderWindow& window);

    void UpdateEnemyChase(Player& player, float deltaTime);

    void UpdateWallCollisions(Wall* aWall, float push);

    Enemy* getEnemy(int index) { return enemies.at(index); }

    //TODO add remove enemy method

    void Update(float deltaTime);

    //accessors
    int getAmount() { return this->amount; }
    int getVectSize() { return enemies.size(); }
    int getAttackValue() { return this->attackValue; }

    // checks for elements
    bool Empty() { return enemies.empty(); }
};

Enemy_Spawner::Enemy_Spawner(int us_amount, int attVal, Texture* texture, Vector2u imageCount, float switchTime, float speed) {
    this->amount = us_amount;
    this->attackValue = attVal;

    Populate(texture, imageCount, switchTime, speed, attVal); 
}

// responsible for deleting all enemies in array, then array itself
Enemy_Spawner::~Enemy_Spawner() {
    enemies.clear();
    delete &enemies;
}

// responsible for dynamically allocating memory for all enemies, setting a random position, and setting their attack values
// gets called in Game_Engine::initEnemies
void Enemy_Spawner::Populate(Texture* texture, Vector2u imageCount, float switchTime, float speed, int attVal) {
    //srand((unsigned) time(0));
    for (int i = 0; i < amount; i++) {
        Enemy* nE = new Enemy(texture, imageCount, switchTime, speed);
        nE->setAttackValue(attVal);
        nE->setRandPos();
        enemies.push_back(nE);
    }
    std::cout << "Initialized Enemy Vector" << std::endl;
    for (int i = 0; i < (int) enemies.size(); i++) {
        std::cout << "\tEnemy " << i << std::endl;
    }
}

// responsible for placing all enemy objects in window
// gets called in Game_Engine::Render
void Enemy_Spawner::Spawn(RenderWindow& window) {
    for (int i = 0; i < amount; i++) {
        enemies.at(i)->Draw(window);
    }
}

// if player-enemy vision ranges collide, chase is implemented
void Enemy_Spawner::UpdateEnemyChase(Player& player, float deltaTime) {
    for (int i = 0; i < amount; i++) {
        if (player.VisionColliderCheck(enemies.at(i)->GetCollider(), 0.0f)) {
            enemies.at(i)->Chase(player, deltaTime);
        }
    }
}

// ensures all enemies maintain proper collision with walls
void Enemy_Spawner::UpdateWallCollisions(Wall* aWall, float push) {
    for (int i = 0; i < amount; i++) {
        aWall->ColliderCheck(enemies.at(i)->GetCollider(), push);
    }
}

// responsible for updating enemies (movement and animation)
// gets called in Game_Engine::Update
void Enemy_Spawner::Update(float deltaTime) {
    // this srand seed needs to be here for random walk
    srand((unsigned) time(0));
    for (int i = 0; i < amount; i++) {
        int rv = rand() % 5 + 1;
        enemies.at(i)->Update(deltaTime, rv);
    }
}

#endif // ENEMY_SPAWNER_H