/* Copyright 2021 Samuel Dunny */
/* Maze_FourthQuadrant (in header file) */

#ifndef MAZE_FOURTHQUADRANT_H
#define MAZE_FOURTHQUADRANT_H

#include "Maze_Corner.h"
#include "Maze_FourWay.h"
#include "Maze_Hallway.h"
#include "Maze_DeadEnd.h"
#include "Maze_TJunction.h"
#include "Maze_BossRoom.h"
#include "Maze_FiveBlockFiller.h"

/* Purpose:
 *  This class instantiates many maze components into one maze quadrant(step up from maze components)
 *  All cordinate placements assume center is at 0,0 in the window
 */

class Maze_FourthQuadrant {
protected:
    // wall variables

    // corners

    // four-ways

    // hallways

    // deadends

    // t-junction

    // filler strips

    // boss room

    // textures used for wall and background

public:
    // constructor
    Maze_FourthQuadrant(sf::Vector2f size);

    // destructor
    ~Maze_FourthQuadrant();

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

Maze_FourthQuadrant::Maze_FourthQuadrant(sf::Vector2f size) {
    // ensure all instance variables are empty

    // load wall texture from img/ directory

    // corners

    // four-way intersections

    // 3-wall length hallways

    // deadend

    // T-junction intersections

    // filler segments (used her to fill extra maze space within enemy spawn bounds that we dont want enemies to spawn in)

    // creates room for maze section boss
}

Maze_FourthQuadrant::~Maze_FourthQuadrant() { /* empty */ }

void Maze_FourthQuadrant::MazeContactUpdate_Player(Player* character, float push) {
    // a value of 1.0f is an immovable object, wheres 0.0f would move quickly

}

void Maze_FourthQuadrant::MazeContactUpdate_Enemies(Enemy_Spawner* enemies, float push) {
    // makes wall the immovable object to minotaur

}

void Maze_FourthQuadrant::Draw(sf::RenderWindow& window) {
    // draws all walls

}

bool Maze_FourthQuadrant::ColliderCheck(Collider other, float push) {
    // default filler value
    return false;
}

bool Maze_FourthQuadrant::inMazeWalls(Vector2f coords) {
    // default filler value
    return false;
}

#endif  // MAZE_FOURTHQUADRANT_H