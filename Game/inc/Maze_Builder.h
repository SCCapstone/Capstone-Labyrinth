/* Copyright 2021 Samuel Dunny */
/* Maze_Builder (in header file) */

#ifndef MAZE_BUILDER_H
#define MAZE_BUILDER_H

#include "Maze_Corner.h"

/* Purpose:
 *  This class instantiates many maze components into one maze (step up from maze components)
 */

class Maze_Builder {
protected:
    // wall variables
    Maze_Component* rd;
    Maze_Component* ru;
    Maze_Component* ld;
    Maze_Component* lu;
    Texture brickwall_big;

public:
    // constructor
    Maze_Builder(sf::Vector2f size);

    // destructor
    ~Maze_Builder();

    // contact update functions between walls and the player
    void MazeContactUpdate_Player(Player* player, float push);

    // contact update function between walls and enemies
    void MazeContactUpdate_Enemies(Enemy_Spawner* enemies, float push);

    // Draw method, draws all walls into referenced window (virtual so it gets overriden)
    void Draw(sf::RenderWindow& window);

    // returns true if Individual's Collider is many contact with any of part of the maze
    bool ColliderCheck(Collider other, float push);
};

Maze_Builder::Maze_Builder(sf::Vector2f size) {
    // ensure all instance variables are empty
    this->rd = nullptr;
    this->ru = nullptr;
    this->ld = nullptr;
    this->lu = nullptr;

    // scale defined in Wall_Component class

    // load wall texture from img/ directory
    // not in parameter so we have the freedom to have multiple textures for walls
    brickwall_big.loadFromFile("imgs/wall_texture.png");

    /* Initializing walls
     * &brickwall:              reference to texture
     * Vector2f(float, float):  size of object
     * Vector2f(float, float):  position in the window
     * bool:                    if corner is facing right
     * bool:                    if corner is facing up
     */

    // position is assumed to be centered at 0.0f, 0.0f
    rd = new Maze_Corner(&brickwall_big, size, Vector2f(-3.0f * scale, -3.0f * scale), true, false);
    ru = new Maze_Corner(&brickwall_big, size, Vector2f(-3.0f * scale, 3.0f * scale), true, true);
    ld = new Maze_Corner(&brickwall_big, size, Vector2f(3.0f * scale, -3.0f * scale), false, false);
    lu = new Maze_Corner(&brickwall_big, size, Vector2f(3.0f * scale, 3.0f * scale), false, true);

    std::cout << "[4] Initialized Walls" << std::endl;
}

Maze_Builder::~Maze_Builder() { /* empty */ }

void Maze_Builder::MazeContactUpdate_Player(Player* character, float push) {
    // a value of 1.0f is an immovable object, wheres 0.0f would move quickly
    rd->ColliderCheck(character->GetCollider(), push);
    ru->ColliderCheck(character->GetCollider(), push);
    ld->ColliderCheck(character->GetCollider(), push);
    lu->ColliderCheck(character->GetCollider(), push);
}

void Maze_Builder::MazeContactUpdate_Enemies(Enemy_Spawner* enemies, float push) {
    // makes wall the immovable object to minotaur
    enemies->UpdateWallCollisions(rd, 1.0f);
    enemies->UpdateWallCollisions(ru, 1.0f);
    enemies->UpdateWallCollisions(ld, 1.0f);
    enemies->UpdateWallCollisions(lu, 1.0f);
}

void Maze_Builder::Draw(sf::RenderWindow& window) {
    // draws all walls
    rd->Draw(window);
    ru->Draw(window);
    ld->Draw(window);
    lu->Draw(window);
}

// don't think we'll need this
bool Maze_Builder::ColliderCheck(Collider other, float push) {
    bool piece1_cond = rd->ColliderCheck(other, push);
    bool piece2_cond = ru->ColliderCheck(other, push);
    bool piece3_cond = ld->ColliderCheck(other, push);
    bool piece4_cond = lu->ColliderCheck(other, push);

    // seems to work just as well
    if (piece1_cond || piece2_cond || piece3_cond || piece4_cond)
        return true;

    return false;
    
}
#endif  // WALL_COMPONENT_H