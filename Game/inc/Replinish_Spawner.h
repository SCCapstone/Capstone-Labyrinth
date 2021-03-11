/* Copyright 2020 Samuel Dunny */
/* Replinish_Spawner class (in header file) */

#ifndef REPLINISH_SPAWNER_H
#define REPLINISH_SPAWNER_H

#include "Health_Replinish.h"
#include <ctime>

class Replinish_Spawner {
    // private attributes
private:
    int amount;
    Vector2f size;
    Vector2f x_bounds;
    Vector2f y_bounds;

    // vector of enemy pointer objects
    std::vector<Health_Replinish*> hearts;

    void deleteHeart(int index);

    // public attributes
public:
    Replinish_Spawner(int us_amount, Vector2f size, Texture* texture, Vector2u imageCount, float switchTime, Vector2f x_bounds, Vector2f y_bounds);

    ~Replinish_Spawner();

    void Update(float deltaTime);

    void Populate(Texture* texture, Vector2u imageCount, float switchTime, Vector2f x_bounds, Vector2f y_bounds);

    void Spawn(RenderWindow& window);

    void UpdatePlayerContact(Player& player);

    //accessors
    int getAmount() { return this->amount; }
    int getVectSize() { return hearts.size(); }
    Health_Replinish* getHeart(int index) { return hearts.at(index); }

    // mutators
    void setAmount(int am) { this->amount = am; }

    // checks for elements
    bool Empty() { return (amount == 0); }
};

/* Public Functions in order:
 * Enemy_Spawner:           default constructor, initializes class variables and calls Populate()
 * ~Enemy_spawner:          destructor, clears vector and deltes reference
 * Update:                  updates all enemies in the vector (movement and animation), enables random movement
 * Populate:                dynamically allocates memory for all enemies, sets attack value and position of all enemies in vector
 * Spawn:                   responsible for drawing enemies in window
 * UpdateHealthBarContact   stops the health bar from moving when making contact with solid objects
 * UpdateEnemyChase:        if player-enemy vision ranges collide, chase is implemented
 * UpdateEnemyContact:      if player-enemy collide, attack is implemented on both sides
 * UpdateWallCollsion:      ensures all enemies maintain proper collision with walls
 * deleteEnemy:             erases enemy at given index
 */
Replinish_Spawner::Replinish_Spawner(int us_amount, Vector2f size, Texture* texture, Vector2u imageCount, float switchTime, Vector2f x_bounds, Vector2f y_bounds) {

    this->amount = us_amount;
    this->size = size;

    this->x_bounds = x_bounds;
    this->y_bounds = y_bounds;

    Populate(texture, imageCount, switchTime, x_bounds, y_bounds);
}

Replinish_Spawner::~Replinish_Spawner() {
    hearts.clear();
    delete& hearts;
}

void Replinish_Spawner::Update(float deltaTime) {
    for (int i = 0; i < amount; i++) {
        hearts.at(i)->Update(deltaTime);
    }
}

void Replinish_Spawner::Populate(Texture* texture, Vector2u imageCount, float switchTime, Vector2f x_bounds, Vector2f y_bounds) {
    hearts.clear();
    for (int i = 0; i < amount; i++) {
        Health_Replinish* nH = new Health_Replinish(texture, size, Vector2f(0.0f, 0.0f), imageCount, switchTime);
        nH->setRandPos(x_bounds, y_bounds);
        hearts.push_back(nH);
    }
    std::cout << "[4] Initialized Health Replinish Spawner" << std::endl;
    /*
    for (int i = 0; i < amount; i++) {
        std::cout << "\t**Heart " << i << "**" << std::endl;
        std::cout << "\t\tPosition: [" << getHeart(i)->GetHeartPosition().x << ", " << getHeart(i)->GetHeartPosition().y << "]" << std::endl;
    }
    */
}

void Replinish_Spawner::Spawn(RenderWindow& window) {
    for (int i = 0; i < amount; i++) {
        hearts.at(i)->Draw(window);
    }
}

void Replinish_Spawner::UpdatePlayerContact(Player& player) {
    int play_dmgd_health = player.getTotalHealth();
    for (int i = 0; i < amount; i++) {
        if (getHeart(i)->Replinish(&player)) {
            deleteHeart(i);
            std::cout << "Health refilled to max (" << player.getTotalHealth() << ") from (" << play_dmgd_health << ")" << std::endl;
        }
    }
}

void Replinish_Spawner::deleteHeart(int ind) {
    hearts.erase(hearts.begin() + ind);
    this->amount -= 1;
}


#endif // REPLINISH_SPAWNER_H