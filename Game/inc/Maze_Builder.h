/* Copyright 2021 Samuel Dunny */
/* Maze_Builder (in header file) */

#ifndef MAZE_BUILDER_H
#define MAZE_BUILDER_H

#include "Maze_FirstQuadrant.h"
#include "Maze_SpawnChamber.h"
#include "Background_Map.h"

/* Purpose:
 *  This class instantiates 4 maze quadrants into one maze (step up from maze quadrants)
 */

class Maze_Builder {
protected:    
    // spawn chamber
    Maze_Component* spawnChamber;

    // Sam Dunny's portion of the maze
    Maze_FirstQuadrant* Sams_Quad;

    // create tile map for background scene
    Background_Map* bg;

    // textures used for spawn chamber and background
    Texture brickwall_big;
    Texture background;

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

    // function that returns true if given coordinates are in a wall component
    bool inMazeWalls(Vector2f coords);
};

Maze_Builder::Maze_Builder(sf::Vector2f size) {
    // ensure all instance variables are empty
    this->spawnChamber = nullptr;
    this->Sams_Quad = nullptr;
    this->bg = nullptr;

    // scale defined in Wall_Component class

    // load wall and background texture from img/ directory
    // not in parameter so we have the freedom to have multiple textures for walls
    brickwall_big.loadFromFile("imgs/wall_texture.png");
    background.loadFromFile("imgs/sand.png");

    // smallest co-ordinate to largest co-ordinate for both x and y
    // all range parameters defined in Wall.h
    bg = new Background_Map(&background, size, X_NEG_RANGE, X_POS_RANGE, Y_NEG_RANGE, Y_POS_RANGE);

    // position is assumed to be centered at 0.0f, 0.0f, creates starting chamber
    spawnChamber = new Maze_SpawnChamber(&brickwall_big, size, Vector2f(0.0f * scale, 0.0f * scale));

    // position is assumed to be centered at 0.0f, 0.0f, creates upper right quadrant
    Sams_Quad = new Maze_FirstQuadrant(size);
}

Maze_Builder::~Maze_Builder() { /* empty */ }

void Maze_Builder::MazeContactUpdate_Player(Player* character, float push) {
    // a value of 1.0f is an immovable object, wheres 0.0f would move quickly
    spawnChamber->ColliderCheck(character->GetCollider(), push);
    Sams_Quad->ColliderCheck(character->GetCollider(), push);
}

void Maze_Builder::MazeContactUpdate_Enemies(Enemy_Spawner* enemies, float push) {
    // makes wall the immovable object to minotaur
    enemies->UpdateWallCollisions(spawnChamber, 1.0f);
    Sams_Quad->MazeContactUpdate_Enemies(enemies, push);
}

void Maze_Builder::Draw(sf::RenderWindow& window) {
    // draw background first, so it gets drawn over
    bg->Draw(window);

    // draws all walls
    spawnChamber->Draw(window);
    Sams_Quad->Draw(window);
}

bool Maze_Builder::ColliderCheck(Collider other, float push) {
    
    // all solid objects need a collider
    bool piece1_cond = spawnChamber->ColliderCheck(other, push);
    bool piece2_cond = Sams_Quad->ColliderCheck(other, push);

    // return true if anything is in contact with walls
    if (piece1_cond || piece2_cond)
        return true;

    return false;
}

bool Maze_Builder::inMazeWalls(Vector2f coords) {
    return spawnChamber->inWallStructure(coords) ||
            Sams_Quad->inMazeWalls(coords);
}

#endif  // MAZE_BUILDER_H