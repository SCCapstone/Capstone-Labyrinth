/* Copyright 2020 Samuel Dunny */
/* Enemy_Spawner class (in header file) */

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

    // true if player needs to be killed
    bool killPlayer;

    // vector of enemy pointer objects
    std::vector<Enemy*> enemies;

    void deleteEnemy(int index);

// public attributes
public:
    Enemy_Spawner(int us_amount, int attVal, Texture* texture, Vector2u imageCount, float switchTime, float speed);

    ~Enemy_Spawner();

    void Update(float deltaTime);

    void Populate(Texture* texture, Vector2u imageCount, float switchTime, float speed, int attVal);

    void Spawn(RenderWindow& window);

    void UpdateEnemyChase(Player& player, float deltaTime);

    void UpdateEnemyContact(Player& player);

    void UpdateWallCollisions(Wall* aWall, float push);

    //accessors
    int getAmount() { return this->amount; }
    int getVectSize() { return enemies.size(); }
    int getAttackValue() { return this->attackValue; }
    bool getKillStatus() { return this->killPlayer; }
    Enemy* getEnemy(int index) { return enemies.at(index); }

    // mutators
    void setAmount(int am) { this->amount = am; }

    // checks for elements
    bool Empty() { return (amount == 0); }
};

/* Public Functions in order:
 * Enemy_Spawner:       default constructor, initializes class variables and calls Populate()
 * ~Enemy_spawner:      destructor, clears vector and deltes reference
 * Update:              updates all enemies in the vector (movement and animation), enables random movement
 * Populate:            dynamically allocates memory for all enemies, sets attack value and position of all enemies in vector
 * Spawn:               responsible for drawing enemies in window
 * UpdateEnemyChase:    if player-enemy vision ranges collide, chase is implemented
 * UpdateEnemyContact:  if player-enemy collide, attack is implemented on both sides
 * UpdateWallCollsion:  ensures all enemies maintain proper collision with walls
 * deleteEnemy:          erases enemy at given index
 */
Enemy_Spawner::Enemy_Spawner(int us_amount, int attVal, Texture* texture, Vector2u imageCount, float switchTime, float speed) {
    this->amount = us_amount;
    this->attackValue = attVal;
    this->killPlayer = false;

    Populate(texture, imageCount, switchTime, speed, attVal); 
}

Enemy_Spawner::~Enemy_Spawner() {
    enemies.clear();
    delete &enemies;
}

void Enemy_Spawner::Update(float deltaTime) {
    // this srand seed needs to be here for random walk
    srand((unsigned) time(0));
    for (int i = 0; i < amount; i++) {
        int rv = rand() % 5 + 1;
        enemies.at(i)->Update(deltaTime, rv);
    }
}

void Enemy_Spawner::Populate(Texture* texture, Vector2u imageCount, float switchTime, float speed, int attVal) {
    //srand((unsigned) time(0));
    for (int i = 0; i < amount; i++) {
        Enemy* nE = new Enemy(texture, imageCount, switchTime, speed);
        nE->setAttackValue(attVal);
        nE->setRandPos();
        enemies.push_back(nE);
    }
    std::cout << "[3] Initialized Enemy Spawner" << std::endl;
    for (int i = 0; i < (int) enemies.size(); i++) {
        std::cout << "\t**Enemy " << i << "**" << std::endl;
        std::cout << "\t\tHealth: " << getEnemy(i)->getTotalHealth() << "\n\t\tAttack Value: " << getEnemy(i)->getAttackValue() << std::endl;
    }
}

void Enemy_Spawner::Spawn(RenderWindow& window) {
    for (int i = 0; i < amount; i++) {
        enemies.at(i)->Draw(window);
    }
}

void Enemy_Spawner::UpdateEnemyChase(Player& player, float deltaTime) {
    for (int i = 0; i < (int) enemies.size(); i++) {
        // 0.0f to show that field of view is not hard contact
        if (player.VisionColliderCheck(enemies.at(i)->GetCollider(), 0.0f)) {
            enemies.at(i)->Chase(player, deltaTime);
        }
    }
}

void Enemy_Spawner::UpdateEnemyContact(Player& player) {
    for (int i = 0; i < (int) enemies.size(); i++) {
        // 0.5f to show that enemies and player have same force on each other
        if (player.ColliderCheck(getEnemy(i)->GetCollider(), 0.5f)) {

            // player attacking enemy
            if (getEnemy(i)->getTotalHealth() > player.getAttackValue()) {
                player.Attack(*getEnemy(i));
            }
            else {
                deleteEnemy(i);
                std::cout << "\nEnemy deleted: " << std::endl;
                break;
            }

            // enemy attacking player
            if (player.getTotalHealth() > getAttackValue()) {
                getEnemy(i)->ConstantAttack(player);
                break;
            }
            else
                killPlayer = true;
            break;
        }
    }
}

void Enemy_Spawner::UpdateWallCollisions(Wall* aWall, float push) {
    for (int i = 0; i < amount; i++) {
        aWall->ColliderCheck(enemies.at(i)->GetCollider(), push);
    }
}

void Enemy_Spawner::deleteEnemy(int ind) {
    enemies.erase(enemies.begin()+ind);
    this->amount -= 1; 
}

#endif // ENEMY_SPAWNER_H