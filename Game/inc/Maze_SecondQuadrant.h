/* Copyright 2021 Samuel Dunny and Caila Buckhaults The Great */
/* Maze_SecondQuadrant (in header file) */

#ifndef MAZE_SECONDQUADRANT_H
#define MAZE_SECONDQUADRANT_H

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

class Maze_SecondQuadrant {
protected:
    // wall variables

    // corners
    Maze_Component* CAILAS_c1;
    Maze_Component* CAILAS_c2;
    Maze_Component* CAILAS_c3;
    Maze_Component* CAILAS_c4;
    Maze_Component* CAILAS_c5;
    Maze_Component* CAILAS_c6;
    Maze_Component* CAILAS_c7;
    Maze_Component* CAILAS_c8;

    // four-ways
    Maze_Component* CAILAS_fw1;

    // hallways
    Maze_Component* CAILAS_hw1;
    Maze_Component* CAILAS_hw2;
    Maze_Component* CAILAS_hw3;
    Maze_Component* CAILAS_hw4;
    Maze_Component* CAILAS_hw5;
    Maze_Component* CAILAS_hw6;
    Maze_Component* CAILAS_hw7;


    // deadends
    Maze_Component* CAILAS_de1;
    Maze_Component* CAILAS_de2;
    Maze_Component* CAILAS_de3;
    Maze_Component* CAILAS_de4;
    Maze_Component* CAILAS_de5;
    Maze_Component* CAILAS_de6;
    Maze_Component* CAILAS_de7;
    Maze_Component* CAILAS_de8;
    Maze_Component* CAILAS_de9;
    Maze_Component* CAILAS_de10;
    Maze_Component* CAILAS_de11;
    Maze_Component* CAILAS_de12;

    // t-junction
    Maze_Component* CAILAS_tj1;
    Maze_Component* CAILAS_tj2;
    Maze_Component* CAILAS_tj3;
    Maze_Component* CAILAS_tj4;

    // filler strips
    Maze_Component* SAMS_fs1;
    Maze_Component* SAMS_fs2;
    Maze_Component* SAMS_fs3;
    Maze_Component* SAMS_fs4;
    Maze_Component* SAMS_fs5;
    Maze_Component* SAMS_fs6;
    Maze_Component* SAMS_fs9;
    Maze_Component* SAMS_fs10;

    // boss room
    Maze_Component* CAILAS_boss_room;
    Vector2f br_coords;

    // textures used for wall and background
    Texture docks_wall;
    Texture docks_background;

    Vector2f sizeFactor;

public:
    // constructor
    Maze_SecondQuadrant(sf::Vector2f size);

    // destructor
    ~Maze_SecondQuadrant();

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

    Vector2f getBossRoomCoords() { return br_coords; }
    Vector2f getQuadrantScale() { return sizeFactor; }
};

Maze_SecondQuadrant::Maze_SecondQuadrant(sf::Vector2f size) {
    // ensure all instance variables are empty
    this->CAILAS_c1 = nullptr;
    this->CAILAS_c2 = nullptr;
    this->CAILAS_c3 = nullptr;
    this->CAILAS_c4 = nullptr;
    this->CAILAS_c5 = nullptr;
    this->CAILAS_c6 = nullptr;
    this->CAILAS_c7 = nullptr;
    this->CAILAS_c8 = nullptr;

    this->CAILAS_fw1 = nullptr;

    this->CAILAS_hw1 = nullptr;
    this->CAILAS_hw2 = nullptr;
    this->CAILAS_hw3 = nullptr;
    this->CAILAS_hw4 = nullptr;
    this->CAILAS_hw5 = nullptr;
    this->CAILAS_hw6 = nullptr;
    this->CAILAS_hw7 = nullptr;


    this->CAILAS_de1 = nullptr;
    this->CAILAS_de2 = nullptr;
    this->CAILAS_de3 = nullptr;
    this->CAILAS_de4 = nullptr;
    this->CAILAS_de5 = nullptr;
    this->CAILAS_de6 = nullptr;
    this->CAILAS_de7 = nullptr;
    this->CAILAS_de8 = nullptr;
    this->CAILAS_de9 = nullptr;
    this->CAILAS_de10 = nullptr;
    this->CAILAS_de11 = nullptr;
    this->CAILAS_de12 = nullptr;

    this->CAILAS_tj1 = nullptr;
    this->CAILAS_tj2 = nullptr;
    this->CAILAS_tj3 = nullptr;
    this->CAILAS_tj4 = nullptr;

    this->SAMS_fs1 = nullptr;
    this->SAMS_fs2 = nullptr;
    this->SAMS_fs3 = nullptr;
    this->SAMS_fs4 = nullptr;
    this->SAMS_fs5 = nullptr;
    this->SAMS_fs6 = nullptr;
    this->SAMS_fs9 = nullptr;
    this->SAMS_fs10 = nullptr;

    this->CAILAS_boss_room = nullptr;

    // load wall texture from img/ directory
    docks_wall.loadFromFile("imgs/docks_wallV1.png");
    docks_background.loadFromFile("imgs/docks_floorV2.png");

    this->sizeFactor = size;

    // corners
    CAILAS_c1 = new Maze_Corner(&docks_wall, size, Vector2f(0.0f * scale, 7.0f * scale), true, true);
    CAILAS_c2 = new Maze_Corner(&docks_wall, size, Vector2f(11.0f * scale, 7.0f * scale), false, true);
    CAILAS_c3 = new Maze_Corner(&docks_wall, size, Vector2f(-4.0f * scale, 9.0f * scale), true, false);
    CAILAS_c4 = new Maze_Corner(&docks_wall, size, Vector2f(9.0f * scale, 15.0f * scale), false, false);
    CAILAS_c5 = new Maze_Corner(&docks_wall, size, Vector2f(16.0f * scale, 16.0f * scale), false, false);
    CAILAS_c6 = new Maze_Corner(&docks_wall, size, Vector2f(16.0f * scale, 16.0f * scale), false, false);
    CAILAS_c7 = new Maze_Corner(&docks_wall, size, Vector2f(-4.0f * scale, 21.0f * scale), true, true);
    CAILAS_c8 = new Maze_Corner(&docks_wall, size, Vector2f(11.0f * scale, 23.0f * scale), true, true);


    // four-way intersections
    CAILAS_fw1 = new Maze_FourWay(&docks_wall, size, Vector2f(1.0f * scale, 17.0f * scale));

    // 3-wall length hallways
    CAILAS_hw1 = new Maze_Hallway(&docks_wall, size, Vector2f(4.0f * scale, 11.0f * scale), true);
    CAILAS_hw2 = new Maze_Hallway(&docks_wall, size, Vector2f(8.0f * scale, 11.0f * scale), true);
    CAILAS_hw3 = new Maze_Hallway(&docks_wall, size, Vector2f(6.0f * scale, 15.0f * scale), true);
    CAILAS_hw4 = new Maze_Hallway(&docks_wall, size, Vector2f(-2.0f * scale, 14.0f * scale), true);
    CAILAS_hw5 = new Maze_Hallway(&docks_wall, size, Vector2f(-5.0f * scale, 14.0f * scale), true);
    CAILAS_hw6 = new Maze_Hallway(&docks_wall, size, Vector2f(-1.0f * scale, 21.0f * scale), true);
    CAILAS_hw7 = new Maze_Hallway(&docks_wall, size, Vector2f(9.0f * scale, 18.0f * scale), false);


    // deadend
    CAILAS_de1 = new Maze_DeadEnd(&docks_wall, size, Vector2f(13.0f * scale, 8.0f * scale), false, false);
    CAILAS_de2 = new Maze_DeadEnd(&docks_wall, size, Vector2f(13.0f * scale, 14.0f * scale), false, true);
    CAILAS_de3 = new Maze_DeadEnd(&docks_wall, size, Vector2f(13.0f * scale, 16.0f * scale), true, true);
    CAILAS_de4 = new Maze_DeadEnd(&docks_wall, size, Vector2f(-4.0f * scale, 18.0f * scale), false, false);
    CAILAS_de5 = new Maze_DeadEnd(&docks_wall, size, Vector2f(1.0f * scale, 23.0f * scale), false, true);
    CAILAS_de6 = new Maze_DeadEnd(&docks_wall, size, Vector2f(3.0f * scale, 21.0f * scale), false, true);
    CAILAS_de7 = new Maze_DeadEnd(&docks_wall, size, Vector2f(7.0f * scale, 19.0f * scale), true, false);
    CAILAS_de8 = new Maze_DeadEnd(&docks_wall, size, Vector2f(11.0f * scale, 20.0f * scale), false, false);
    CAILAS_de9 = new Maze_DeadEnd(&docks_wall, size, Vector2f(14.0f * scale, 26.0f * scale), false, true);
    CAILAS_de10 = new Maze_DeadEnd(&docks_wall, size, Vector2f(16.0f * scale, 26.0f * scale), false, true);
    CAILAS_de11 = new Maze_DeadEnd(&docks_wall, size, Vector2f(9.0f * scale, 24.0f * scale), false, true);
    CAILAS_de12 = new Maze_DeadEnd(&docks_wall, size, Vector2f(18.0f * scale, 24.0f * scale), true, false);

    // T-junction intersections
    CAILAS_tj1 = new Maze_TJunction(&docks_wall, size, Vector2f(6.0f * scale, 7.0f * scale), true, false);
    CAILAS_tj2 = new Maze_TJunction(&docks_wall, size, Vector2f(1.0f * scale, 11.0f * scale), true, false);
    CAILAS_tj3 = new Maze_TJunction(&docks_wall, size, Vector2f(13.0f * scale, 11.0f * scale), false, false);
    CAILAS_tj4 = new Maze_TJunction(&docks_wall, size, Vector2f(16.0f * scale, 21.0f * scale), false, false);

    // filler segments (used her to fill extra maze space within enemy spawn bounds that we dont want enemies to spawn in)
    SAMS_fs1 = new Maze_FiveBlockFiller(&docks_wall, size, Vector2f(15.0f * scale, 9.0f * scale), false);
    SAMS_fs2 = new Maze_FiveBlockFiller(&docks_wall, size, Vector2f(15.0f * scale, 5.0f * scale), true);
    SAMS_fs3 = new Maze_FiveBlockFiller(&docks_wall, size, Vector2f(15.0f * scale, 12.0f * scale), false);
    SAMS_fs4 = new Maze_FiveBlockFiller(&docks_wall, size, Vector2f(15.0f * scale, 6.0f * scale), true);
    SAMS_fs5 = new Maze_FiveBlockFiller(&docks_wall, size, Vector2f(10.0f * scale, 25.0f * scale), true);
    SAMS_fs6 = new Maze_FiveBlockFiller(&docks_wall, size, Vector2f(10.0f * scale, 26.0f * scale), true);
    SAMS_fs9 = new Maze_FiveBlockFiller(&docks_wall, size, Vector2f(6.0f * scale, 25.0f * scale), true);
    SAMS_fs10 = new Maze_FiveBlockFiller(&docks_wall, size, Vector2f(6.0f * scale, 26.0f * scale), true);

    // creates room for maze section boss
    this->br_coords = Vector2f(6.0f * scale, 22.0f * scale);
    CAILAS_boss_room = new Maze_BossRoom(&docks_wall, size, br_coords, true, true);
}

Maze_SecondQuadrant::~Maze_SecondQuadrant() { /* empty */ }

void Maze_SecondQuadrant::MazeContactUpdate_Player(Player* character, float push) {
    // a value of 1.0f is an immovable object, wheres 0.0f would move quickly
    CAILAS_c1->ColliderCheck(character->GetCollider(), push);
    CAILAS_c2->ColliderCheck(character->GetCollider(), push);
    CAILAS_c3->ColliderCheck(character->GetCollider(), push);
    CAILAS_c4->ColliderCheck(character->GetCollider(), push);
    CAILAS_c5->ColliderCheck(character->GetCollider(), push);
    CAILAS_c6->ColliderCheck(character->GetCollider(), push);
    CAILAS_c7->ColliderCheck(character->GetCollider(), push);
    CAILAS_c8->ColliderCheck(character->GetCollider(), push);

    CAILAS_fw1->ColliderCheck(character->GetCollider(), push);

    CAILAS_hw1->ColliderCheck(character->GetCollider(), push);
    CAILAS_hw2->ColliderCheck(character->GetCollider(), push);
    CAILAS_hw3->ColliderCheck(character->GetCollider(), push);
    CAILAS_hw4->ColliderCheck(character->GetCollider(), push);
    CAILAS_hw5->ColliderCheck(character->GetCollider(), push);
    CAILAS_hw6->ColliderCheck(character->GetCollider(), push);
    CAILAS_hw7->ColliderCheck(character->GetCollider(), push);


    CAILAS_de1->ColliderCheck(character->GetCollider(), push);
    CAILAS_de2->ColliderCheck(character->GetCollider(), push);
    CAILAS_de3->ColliderCheck(character->GetCollider(), push);
    CAILAS_de4->ColliderCheck(character->GetCollider(), push);
    CAILAS_de5->ColliderCheck(character->GetCollider(), push);
    CAILAS_de6->ColliderCheck(character->GetCollider(), push);
    CAILAS_de7->ColliderCheck(character->GetCollider(), push);
    CAILAS_de8->ColliderCheck(character->GetCollider(), push);
    CAILAS_de9->ColliderCheck(character->GetCollider(), push);
    CAILAS_de10->ColliderCheck(character->GetCollider(), push);
    CAILAS_de11->ColliderCheck(character->GetCollider(), push);
    CAILAS_de12->ColliderCheck(character->GetCollider(), push);


    CAILAS_tj1->ColliderCheck(character->GetCollider(), push);
    CAILAS_tj2->ColliderCheck(character->GetCollider(), push);
    CAILAS_tj3->ColliderCheck(character->GetCollider(), push);
    CAILAS_tj4->ColliderCheck(character->GetCollider(), push);

    SAMS_fs1->ColliderCheck(character->GetCollider(), push);
    SAMS_fs2->ColliderCheck(character->GetCollider(), push);
    SAMS_fs3->ColliderCheck(character->GetCollider(), push);
    SAMS_fs4->ColliderCheck(character->GetCollider(), push);
    SAMS_fs5->ColliderCheck(character->GetCollider(), push);
    SAMS_fs6->ColliderCheck(character->GetCollider(), push);
    SAMS_fs9->ColliderCheck(character->GetCollider(), push);
    SAMS_fs10->ColliderCheck(character->GetCollider(), push);

    CAILAS_boss_room->ColliderCheck(character->GetCollider(), push);

}

void Maze_SecondQuadrant::MazeContactUpdate_Enemies(Enemy_Spawner* enemies, float push) {
    // makes wall the immovable object to minotaur
    enemies->UpdateWallCollisions(CAILAS_c1, push);
    enemies->UpdateWallCollisions(CAILAS_c2, push);
    enemies->UpdateWallCollisions(CAILAS_c3, push);
    enemies->UpdateWallCollisions(CAILAS_c4, push);
    enemies->UpdateWallCollisions(CAILAS_c5, push);
    enemies->UpdateWallCollisions(CAILAS_c6, push);
    enemies->UpdateWallCollisions(CAILAS_c7, push);
    enemies->UpdateWallCollisions(CAILAS_c8, push);

    enemies->UpdateWallCollisions(CAILAS_fw1, push);

    enemies->UpdateWallCollisions(CAILAS_hw1, push);
    enemies->UpdateWallCollisions(CAILAS_hw2, push);
    enemies->UpdateWallCollisions(CAILAS_hw3, push);
    enemies->UpdateWallCollisions(CAILAS_hw4, push);
    enemies->UpdateWallCollisions(CAILAS_hw5, push);
    enemies->UpdateWallCollisions(CAILAS_hw6, push);
    enemies->UpdateWallCollisions(CAILAS_hw7, push);

    enemies->UpdateWallCollisions(CAILAS_de1, push);
    enemies->UpdateWallCollisions(CAILAS_de2, push);
    enemies->UpdateWallCollisions(CAILAS_de3, push);
    enemies->UpdateWallCollisions(CAILAS_de4, push);
    enemies->UpdateWallCollisions(CAILAS_de5, push);
    enemies->UpdateWallCollisions(CAILAS_de6, push);
    enemies->UpdateWallCollisions(CAILAS_de7, push);
    enemies->UpdateWallCollisions(CAILAS_de8, push);
    enemies->UpdateWallCollisions(CAILAS_de9, push);
    enemies->UpdateWallCollisions(CAILAS_de10, push);
    enemies->UpdateWallCollisions(CAILAS_de11, push);
    enemies->UpdateWallCollisions(CAILAS_de12, push);


    enemies->UpdateWallCollisions(CAILAS_tj1, push);
    enemies->UpdateWallCollisions(CAILAS_tj2, push);
    enemies->UpdateWallCollisions(CAILAS_tj3, push);
    enemies->UpdateWallCollisions(CAILAS_tj4, push);

    enemies->UpdateWallCollisions(SAMS_fs1, push);
    enemies->UpdateWallCollisions(SAMS_fs2, push);
    enemies->UpdateWallCollisions(SAMS_fs3, push);
    enemies->UpdateWallCollisions(SAMS_fs4, push);
    enemies->UpdateWallCollisions(SAMS_fs5, push);
    enemies->UpdateWallCollisions(SAMS_fs6, push);
    enemies->UpdateWallCollisions(SAMS_fs9, push);
    enemies->UpdateWallCollisions(SAMS_fs10, push);

    enemies->UpdateWallCollisions(CAILAS_boss_room, push);

}

void Maze_SecondQuadrant::Draw(sf::RenderWindow& window) {
    // draws all walls
    CAILAS_c1->Draw(window);
    CAILAS_c2->Draw(window);
    CAILAS_c3->Draw(window);
    CAILAS_c4->Draw(window);
    CAILAS_c5->Draw(window);
    CAILAS_c6->Draw(window);
    CAILAS_c7->Draw(window);
    CAILAS_c8->Draw(window);

    CAILAS_fw1->Draw(window);

    CAILAS_hw1->Draw(window);
    CAILAS_hw2->Draw(window);
    CAILAS_hw3->Draw(window);
    CAILAS_hw4->Draw(window);
    CAILAS_hw5->Draw(window);
    CAILAS_hw6->Draw(window);
    CAILAS_hw7->Draw(window);

    CAILAS_de1->Draw(window);
    CAILAS_de2->Draw(window);
    CAILAS_de3->Draw(window);
    CAILAS_de4->Draw(window);
    CAILAS_de5->Draw(window);
    CAILAS_de6->Draw(window);
    CAILAS_de7->Draw(window);
    CAILAS_de8->Draw(window);
    CAILAS_de9->Draw(window);
    CAILAS_de10->Draw(window);
    CAILAS_de11->Draw(window);
    CAILAS_de12->Draw(window);

    CAILAS_tj1->Draw(window);
    CAILAS_tj2->Draw(window);
    CAILAS_tj3->Draw(window);
    CAILAS_tj4->Draw(window);

    SAMS_fs1->Draw(window);
    SAMS_fs2->Draw(window);
    SAMS_fs3->Draw(window);
    SAMS_fs4->Draw(window);
    SAMS_fs5->Draw(window);
    SAMS_fs6->Draw(window);
    SAMS_fs9->Draw(window);
    SAMS_fs10->Draw(window);

    CAILAS_boss_room->Draw(window);
}

bool Maze_SecondQuadrant::ColliderCheck(Collider other, float push) {
    // default filler value
    bool piece1_cond = CAILAS_c1->ColliderCheck(other, push);
    bool piece2_cond = CAILAS_c2->ColliderCheck(other, push);
    bool piece3_cond = CAILAS_c3->ColliderCheck(other, push);
    bool piece4_cond = CAILAS_c4->ColliderCheck(other, push);
    bool piece5_cond = CAILAS_c5->ColliderCheck(other, push);
    bool piece6_cond = CAILAS_c6->ColliderCheck(other, push);
    bool piece7_cond = CAILAS_c7->ColliderCheck(other, push);
    bool piece8_cond = CAILAS_c8->ColliderCheck(other, push);

    bool piece9_cond = CAILAS_tj1->ColliderCheck(other, push);
    bool piece10_cond = CAILAS_tj2->ColliderCheck(other, push);
    bool piece11_cond = CAILAS_tj3->ColliderCheck(other, push);
    bool piece12_cond = CAILAS_tj4->ColliderCheck(other, push);

    bool piece13_cond = CAILAS_fw1->ColliderCheck(other, push);

    bool piece14_cond = CAILAS_de1->ColliderCheck(other, push);
    bool piece15_cond = CAILAS_de2->ColliderCheck(other, push);
    bool piece16_cond = CAILAS_de3->ColliderCheck(other, push);
    bool piece17_cond = CAILAS_de4->ColliderCheck(other, push);
    bool piece18_cond = CAILAS_de5->ColliderCheck(other, push);
    bool piece19_cond = CAILAS_de6->ColliderCheck(other, push);
    bool piece20_cond = CAILAS_de7->ColliderCheck(other, push);
    bool piece21_cond = CAILAS_de8->ColliderCheck(other, push);
    bool piece22_cond = CAILAS_de9->ColliderCheck(other, push);
    bool piece23_cond = CAILAS_de10->ColliderCheck(other, push);
    bool piece24_cond = CAILAS_de11->ColliderCheck(other, push);
    bool piece25_cond = CAILAS_de12->ColliderCheck(other, push);

    bool piece26_cond = CAILAS_hw1->ColliderCheck(other, push);
    bool piece27_cond = CAILAS_hw2->ColliderCheck(other, push);
    bool piece28_cond = CAILAS_hw3->ColliderCheck(other, push);
    bool piece29_cond = CAILAS_hw4->ColliderCheck(other, push);
    bool piece30_cond = CAILAS_hw5->ColliderCheck(other, push);
    bool piece31_cond = CAILAS_hw6->ColliderCheck(other, push);
    bool piece32_cond = CAILAS_hw7->ColliderCheck(other, push);

    bool piece34_cond = SAMS_fs1->ColliderCheck(other, push);
    bool piece35_cond = SAMS_fs2->ColliderCheck(other, push);
    bool piece36_cond = SAMS_fs3->ColliderCheck(other, push);
    bool piece37_cond = SAMS_fs4->ColliderCheck(other, push);
    bool piece38_cond = SAMS_fs5->ColliderCheck(other, push);
    bool piece39_cond = SAMS_fs6->ColliderCheck(other, push);
    bool piece42_cond = SAMS_fs9->ColliderCheck(other, push);
    bool piece43_cond = SAMS_fs10->ColliderCheck(other, push);

    bool piece33_cond = CAILAS_boss_room->ColliderCheck(other, push);

    if (piece1_cond ||
        piece2_cond ||
        piece3_cond ||
        piece4_cond ||
        piece5_cond ||
        piece6_cond ||
        piece7_cond ||
        piece8_cond ||
        piece9_cond ||
        piece10_cond ||
        piece11_cond ||
        piece12_cond ||
        piece13_cond ||
        piece14_cond ||
        piece15_cond ||
        piece16_cond ||
        piece17_cond ||
        piece18_cond ||
        piece19_cond ||
        piece20_cond ||
        piece21_cond ||
        piece22_cond ||
        piece23_cond ||
        piece24_cond ||
        piece25_cond ||
        piece26_cond ||
        piece27_cond ||
        piece28_cond ||
        piece29_cond ||
        piece30_cond ||
        piece31_cond ||
        piece32_cond ||
        piece33_cond ||
        piece34_cond ||
        piece35_cond ||
        piece36_cond ||
        piece37_cond ||
        piece38_cond ||
        piece39_cond ||
        piece42_cond ||
        piece43_cond)
        return true;

    return false;
}

bool Maze_SecondQuadrant::inMazeWalls(Vector2f coords) {
    // default filler value
    return CAILAS_c1->inWallStructure(coords) ||
        CAILAS_c2->inWallStructure(coords) ||
        CAILAS_c3->inWallStructure(coords) ||
        CAILAS_c4->inWallStructure(coords) ||
        CAILAS_c5->inWallStructure(coords) ||
        CAILAS_c6->inWallStructure(coords) ||
        CAILAS_c7->inWallStructure(coords) ||
        CAILAS_c8->inWallStructure(coords) ||
        CAILAS_tj1->inWallStructure(coords) ||
        CAILAS_tj2->inWallStructure(coords) ||
        CAILAS_tj3->inWallStructure(coords) ||
        CAILAS_tj4->inWallStructure(coords) ||
        CAILAS_fw1->inWallStructure(coords) ||
        CAILAS_de1->inWallStructure(coords) ||
        CAILAS_de2->inWallStructure(coords) ||
        CAILAS_de3->inWallStructure(coords) ||
        CAILAS_de4->inWallStructure(coords) ||
        CAILAS_de5->inWallStructure(coords) ||
        CAILAS_de6->inWallStructure(coords) ||
        CAILAS_de7->inWallStructure(coords) ||
        CAILAS_de8->inWallStructure(coords) ||
        CAILAS_de9->inWallStructure(coords) ||
        CAILAS_de10->inWallStructure(coords) ||
        CAILAS_de11->inWallStructure(coords) ||
        CAILAS_de12->inWallStructure(coords) ||
        CAILAS_hw1->inWallStructure(coords) ||
        CAILAS_hw2->inWallStructure(coords) ||
        CAILAS_hw3->inWallStructure(coords) ||
        CAILAS_hw4->inWallStructure(coords) ||
        CAILAS_hw5->inWallStructure(coords) ||
        CAILAS_hw6->inWallStructure(coords) ||
        CAILAS_hw7->inWallStructure(coords) ||
        SAMS_fs1->inWallStructure(coords) ||
        SAMS_fs2->inWallStructure(coords) ||
        SAMS_fs3->inWallStructure(coords) ||
        SAMS_fs4->inWallStructure(coords) ||
        SAMS_fs5->inWallStructure(coords) ||
        SAMS_fs6->inWallStructure(coords) ||
        SAMS_fs9->inWallStructure(coords) ||
        SAMS_fs10->inWallStructure(coords) ||
        CAILAS_boss_room->inWallStructure(coords);
}

#endif  // MAZE_SECONDQUADRANT_H