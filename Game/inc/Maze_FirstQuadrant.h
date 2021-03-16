/* Copyright 2021 Samuel Dunny */
/* Maze_FirstQuadrant (in header file) */

#ifndef MAZE_FIRSTQUADRANT_H
#define MAZE_FIRSTQUADRANT_H

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

class Maze_FirstQuadrant {
protected:
    // wall variables

    // corners
    Maze_Component* SAMS_c1;
    Maze_Component* SAMS_c2;
    Maze_Component* SAMS_c3;
    Maze_Component* SAMS_c4;
    Maze_Component* SAMS_c5;
    Maze_Component* SAMS_c6;

    // four-ways
    Maze_Component* SAMS_fw1;
    Maze_Component* SAMS_fw2;
    Maze_Component* SAMS_fw3;
    Maze_Component* SAMS_fw4;

    // hallways
    Maze_Component* SAMS_hw1;
    Maze_Component* SAMS_hw2;
    Maze_Component* SAMS_hw3;
    Maze_Component* SAMS_hw4;
    Maze_Component* SAMS_hw5;
    Maze_Component* SAMS_hw6;
    Maze_Component* SAMS_hw7;

    // deadends
    Maze_Component* SAMS_de1;
    Maze_Component* SAMS_de2;
    Maze_Component* SAMS_de3;
    Maze_Component* SAMS_de4;
    Maze_Component* SAMS_de5;
    Maze_Component* SAMS_de6;
    Maze_Component* SAMS_de7;

    // t-junction
    Maze_Component* SAMS_tj1;
    Maze_Component* SAMS_tj2;
    Maze_Component* SAMS_tj3;
    Maze_Component* SAMS_tj4;
    Maze_Component* SAMS_tj5;
    Maze_Component* SAMS_tj6;
    Maze_Component* SAMS_tj7;

    // filler strips
    Maze_Component* SAMS_fs1;
    Maze_Component* SAMS_fs2;
    Maze_Component* SAMS_fs3;
    Maze_Component* SAMS_fs4;
    Maze_Component* SAMS_fs5;
    Maze_Component* SAMS_fs6;
    Maze_Component* SAMS_fs7;
    Maze_Component* SAMS_fs8;
    Maze_Component* SAMS_fs9;
    Maze_Component* SAMS_fs10;

    // boss room
    Maze_Component* SAMS_boss_room;
    Vector2f br_coords;

    // textures used for wall and background
    Texture brickwall_big;

public:
    // constructor
    Maze_FirstQuadrant(sf::Vector2f size);

    // destructor
    ~Maze_FirstQuadrant();

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
};

Maze_FirstQuadrant::Maze_FirstQuadrant(sf::Vector2f size) {
    // ensure all instance variables are empty
    this->SAMS_c1 = nullptr;
    this->SAMS_c2 = nullptr;
    this->SAMS_c3 = nullptr;
    this->SAMS_c4 = nullptr;
    this->SAMS_c5 = nullptr;
    this->SAMS_c6 = nullptr;

    this->SAMS_fw1 = nullptr;
    this->SAMS_fw2 = nullptr;
    this->SAMS_fw3 = nullptr;
    this->SAMS_fw4 = nullptr;

    this->SAMS_hw1 = nullptr;
    this->SAMS_hw2 = nullptr;
    this->SAMS_hw3 = nullptr;
    this->SAMS_hw4 = nullptr;
    this->SAMS_hw5 = nullptr;
    this->SAMS_hw6 = nullptr;
    this->SAMS_hw7 = nullptr;

    this->SAMS_de1 = nullptr;
    this->SAMS_de2 = nullptr;
    this->SAMS_de3 = nullptr;
    this->SAMS_de4 = nullptr;
    this->SAMS_de5 = nullptr;
    this->SAMS_de6 = nullptr;
    this->SAMS_de7 = nullptr;

    this->SAMS_tj1 = nullptr;
    this->SAMS_tj2 = nullptr;
    this->SAMS_tj3 = nullptr;
    this->SAMS_tj4 = nullptr;
    this->SAMS_tj5 = nullptr;
    this->SAMS_tj6 = nullptr;
    this->SAMS_tj7 = nullptr;

    this->SAMS_fs1 = nullptr;
    this->SAMS_fs2 = nullptr;
    this->SAMS_fs3 = nullptr;
    this->SAMS_fs4 = nullptr;
    this->SAMS_fs5 = nullptr;
    this->SAMS_fs6 = nullptr;
    this->SAMS_fs7 = nullptr;
    this->SAMS_fs8 = nullptr;
    this->SAMS_fs9 = nullptr;
    this->SAMS_fs10 = nullptr;

    this->SAMS_boss_room = nullptr;

    // scale defined in Wall_Component class

    // load wall texture from img/ directory
    // not in parameter so we have the freedom to have multiple textures for walls
    brickwall_big.loadFromFile("imgs/wall_texture.png");

    // corners
    SAMS_c1 = new Maze_Corner(&brickwall_big, size, Vector2f(0.0f * scale, -11.0f * scale), true, false);
    SAMS_c2 = new Maze_Corner(&brickwall_big, size, Vector2f(0.0f * scale, -15.0f * scale), true, true);
    SAMS_c3 = new Maze_Corner(&brickwall_big, size, Vector2f(15.0f * scale, -16.0f * scale), false, true);
    SAMS_c4 = new Maze_Corner(&brickwall_big, size, Vector2f(15.0f * scale, -4.0f * scale), false, true);
    SAMS_c5 = new Maze_Corner(&brickwall_big, size, Vector2f(15.0f * scale, -11.0f * scale), false, false);
    SAMS_c6 = new Maze_Corner(&brickwall_big, size, Vector2f(15.0f * scale, -19.0f * scale), true, false);

    // four-way intersections
    SAMS_fw1 = new Maze_FourWay(&brickwall_big, size, Vector2f(7.0f * scale, 0.0f * scale));
    SAMS_fw2 = new Maze_FourWay(&brickwall_big, size, Vector2f(0.0f * scale, -7.0f * scale));
    SAMS_fw3 = new Maze_FourWay(&brickwall_big, size, Vector2f(11.0f * scale, 0.0f * scale));
    SAMS_fw4 = new Maze_FourWay(&brickwall_big, size, Vector2f(11.0f * scale, -11.0f * scale));

    // 3-wall length hallways
    SAMS_hw1 = new Maze_Hallway(&brickwall_big, size, Vector2f(5.0f * scale, -7.0f * scale), true);
    SAMS_hw2 = new Maze_Hallway(&brickwall_big, size, Vector2f(7.0f * scale, -2.0f * scale), false);
    SAMS_hw3 = new Maze_Hallway(&brickwall_big, size, Vector2f(7.0f * scale, -11.0f * scale), false);
    SAMS_hw4 = new Maze_Hallway(&brickwall_big, size, Vector2f(11.0f * scale, 3.0f * scale), false);
    SAMS_hw5 = new Maze_Hallway(&brickwall_big, size, Vector2f(11.0f * scale, -19.0f * scale), false);
    SAMS_hw6 = new Maze_Hallway(&brickwall_big, size, Vector2f(15.0f * scale, -9.0f * scale), false);
    SAMS_hw7 = new Maze_Hallway(&brickwall_big, size, Vector2f(13.0f * scale, -16.0f * scale), true);

    // deadend
    SAMS_de1 = new Maze_DeadEnd(&brickwall_big, size, Vector2f(7.0f * scale, 3.0f * scale), false, true);
    SAMS_de2 = new Maze_DeadEnd(&brickwall_big, size, Vector2f(14.0f * scale, 0.0f * scale), true, false);
    SAMS_de3 = new Maze_DeadEnd(&brickwall_big, size, Vector2f(11.0f * scale, -13.0f * scale), false, true);
    SAMS_de4 = new Maze_DeadEnd(&brickwall_big, size, Vector2f(4.0f * scale, -19.0f * scale), true, true);
    SAMS_de5 = new Maze_DeadEnd(&brickwall_big, size, Vector2f(0.0f * scale, -19.0f * scale), false, false);
    SAMS_de6 = new Maze_DeadEnd(&brickwall_big, size, Vector2f(17.0f * scale, -7.0f * scale), true, false);
    SAMS_de7 = new Maze_DeadEnd(&brickwall_big, size, Vector2f(11.0f * scale, -21.0f * scale), false, false);

    // T-junction intersections
    SAMS_tj1 = new Maze_TJunction(&brickwall_big, size, Vector2f(8.0f * scale, -15.0f * scale), true, true);
    SAMS_tj2 = new Maze_TJunction(&brickwall_big, size, Vector2f(7.0f * scale, -7.0f * scale), true, false);
    SAMS_tj3 = new Maze_TJunction(&brickwall_big, size, Vector2f(11.0f * scale, -7.0f * scale), false, false);
    SAMS_tj4 = new Maze_TJunction(&brickwall_big, size, Vector2f(11.0f * scale, -4.0f * scale), false, true);
    SAMS_tj5 = new Maze_TJunction(&brickwall_big, size, Vector2f(3.0f * scale, -11.0f * scale), true, true);
    SAMS_tj6 = new Maze_TJunction(&brickwall_big, size, Vector2f(3.0f * scale, -15.0f * scale), true, false);
    SAMS_tj7 = new Maze_TJunction(&brickwall_big, size, Vector2f(8.0f * scale, -19.0f * scale), true, false);

    // filler segments (used her to fill extra maze space within enemy spawn bounds that we dont want enemies to spawn in)
    SAMS_fs1 = new Maze_FiveBlockFiller(&brickwall_big, size, Vector2f(13.0f * scale, -20.0f * scale), false);
    SAMS_fs2 = new Maze_FiveBlockFiller(&brickwall_big, size, Vector2f(4.0f * scale, -17.0f * scale), true);
    SAMS_fs3 = new Maze_FiveBlockFiller(&brickwall_big, size, Vector2f(2.0f * scale, -18.0f * scale), false);
    SAMS_fs4 = new Maze_FiveBlockFiller(&brickwall_big, size, Vector2f(14.0f * scale, -2.0f * scale), true);
    SAMS_fs5 = new Maze_FiveBlockFiller(&brickwall_big, size, Vector2f(14.0f * scale, -14.0f * scale), true);
    SAMS_fs6 = new Maze_FiveBlockFiller(&brickwall_big, size, Vector2f(14.0f * scale, -13.0f * scale), true);
    SAMS_fs7 = new Maze_FiveBlockFiller(&brickwall_big, size, Vector2f(16.0f * scale, 1.0f * scale), false);
    SAMS_fs8 = new Maze_FiveBlockFiller(&brickwall_big, size, Vector2f(14.0f * scale, 2.0f * scale), true);
    SAMS_fs9 = new Maze_FiveBlockFiller(&brickwall_big, size, Vector2f(14.0f * scale, 3.0f * scale), true);
    SAMS_fs10 = new Maze_FiveBlockFiller(&brickwall_big, size, Vector2f(14.0f * scale, 4.0f * scale), true);

    // creates room for maze section boss
    this->br_coords = Vector2f(20.0f * scale, -19.0f * scale);
    SAMS_boss_room = new Maze_BossRoom(&brickwall_big, size, br_coords, true, false);
}

Maze_FirstQuadrant::~Maze_FirstQuadrant() { /* empty */ }

void Maze_FirstQuadrant::MazeContactUpdate_Player(Player* character, float push) {
    // a value of 1.0f is an immovable object, wheres 0.0f would move quickly
    SAMS_c1->ColliderCheck(character->GetCollider(), push);
    SAMS_c2->ColliderCheck(character->GetCollider(), push);
    SAMS_c3->ColliderCheck(character->GetCollider(), push);
    SAMS_c4->ColliderCheck(character->GetCollider(), push);
    SAMS_c5->ColliderCheck(character->GetCollider(), push);
    SAMS_c6->ColliderCheck(character->GetCollider(), push);

    SAMS_fw1->ColliderCheck(character->GetCollider(), push);
    SAMS_fw2->ColliderCheck(character->GetCollider(), push);
    SAMS_fw3->ColliderCheck(character->GetCollider(), push);
    SAMS_fw4->ColliderCheck(character->GetCollider(), push);

    SAMS_hw1->ColliderCheck(character->GetCollider(), push);
    SAMS_hw2->ColliderCheck(character->GetCollider(), push);
    SAMS_hw3->ColliderCheck(character->GetCollider(), push);
    SAMS_hw4->ColliderCheck(character->GetCollider(), push);
    SAMS_hw5->ColliderCheck(character->GetCollider(), push);
    SAMS_hw6->ColliderCheck(character->GetCollider(), push);
    SAMS_hw7->ColliderCheck(character->GetCollider(), push);

    SAMS_de1->ColliderCheck(character->GetCollider(), push);
    SAMS_de2->ColliderCheck(character->GetCollider(), push);
    SAMS_de3->ColliderCheck(character->GetCollider(), push);
    SAMS_de4->ColliderCheck(character->GetCollider(), push);
    SAMS_de5->ColliderCheck(character->GetCollider(), push);
    SAMS_de6->ColliderCheck(character->GetCollider(), push);
    SAMS_de7->ColliderCheck(character->GetCollider(), push);

    SAMS_tj1->ColliderCheck(character->GetCollider(), push);
    SAMS_tj2->ColliderCheck(character->GetCollider(), push);
    SAMS_tj3->ColliderCheck(character->GetCollider(), push);
    SAMS_tj4->ColliderCheck(character->GetCollider(), push);
    SAMS_tj5->ColliderCheck(character->GetCollider(), push);
    SAMS_tj6->ColliderCheck(character->GetCollider(), push);
    SAMS_tj7->ColliderCheck(character->GetCollider(), push);

    SAMS_fs1->ColliderCheck(character->GetCollider(), push);
    SAMS_fs2->ColliderCheck(character->GetCollider(), push);
    SAMS_fs3->ColliderCheck(character->GetCollider(), push);
    SAMS_fs4->ColliderCheck(character->GetCollider(), push);
    SAMS_fs5->ColliderCheck(character->GetCollider(), push);
    SAMS_fs6->ColliderCheck(character->GetCollider(), push);
    SAMS_fs7->ColliderCheck(character->GetCollider(), push);
    SAMS_fs8->ColliderCheck(character->GetCollider(), push);
    SAMS_fs9->ColliderCheck(character->GetCollider(), push);
    SAMS_fs10->ColliderCheck(character->GetCollider(), push);

    SAMS_boss_room->ColliderCheck(character->GetCollider(), push);
}

void Maze_FirstQuadrant::MazeContactUpdate_Enemies(Enemy_Spawner* enemies, float push) {
    // makes wall the immovable object to minotaur
    enemies->UpdateWallCollisions(SAMS_c1, push);
    enemies->UpdateWallCollisions(SAMS_c2, push);
    enemies->UpdateWallCollisions(SAMS_c3, push);
    enemies->UpdateWallCollisions(SAMS_c4, push);
    enemies->UpdateWallCollisions(SAMS_c5, push);
    enemies->UpdateWallCollisions(SAMS_c6, push);

    enemies->UpdateWallCollisions(SAMS_fw1, push);
    enemies->UpdateWallCollisions(SAMS_fw2, push);
    enemies->UpdateWallCollisions(SAMS_fw3, push);
    enemies->UpdateWallCollisions(SAMS_fw4, push);

    enemies->UpdateWallCollisions(SAMS_hw1, push);
    enemies->UpdateWallCollisions(SAMS_hw2, push);
    enemies->UpdateWallCollisions(SAMS_hw3, push);
    enemies->UpdateWallCollisions(SAMS_hw4, push);
    enemies->UpdateWallCollisions(SAMS_hw5, push);
    enemies->UpdateWallCollisions(SAMS_hw6, push);
    enemies->UpdateWallCollisions(SAMS_hw7, push);

    enemies->UpdateWallCollisions(SAMS_de1, push);
    enemies->UpdateWallCollisions(SAMS_de2, push);
    enemies->UpdateWallCollisions(SAMS_de3, push);
    enemies->UpdateWallCollisions(SAMS_de4, push);
    enemies->UpdateWallCollisions(SAMS_de5, push);
    enemies->UpdateWallCollisions(SAMS_de6, push);
    enemies->UpdateWallCollisions(SAMS_de7, push);

    enemies->UpdateWallCollisions(SAMS_tj1, push);
    enemies->UpdateWallCollisions(SAMS_tj2, push);
    enemies->UpdateWallCollisions(SAMS_tj3, push);
    enemies->UpdateWallCollisions(SAMS_tj4, push);
    enemies->UpdateWallCollisions(SAMS_tj5, push);
    enemies->UpdateWallCollisions(SAMS_tj6, push);
    enemies->UpdateWallCollisions(SAMS_tj7, push);

    enemies->UpdateWallCollisions(SAMS_fs1, push);
    enemies->UpdateWallCollisions(SAMS_fs2, push);
    enemies->UpdateWallCollisions(SAMS_fs3, push);
    enemies->UpdateWallCollisions(SAMS_fs4, push);
    enemies->UpdateWallCollisions(SAMS_fs5, push);
    enemies->UpdateWallCollisions(SAMS_fs6, push);
    enemies->UpdateWallCollisions(SAMS_fs7, push);
    enemies->UpdateWallCollisions(SAMS_fs8, push);
    enemies->UpdateWallCollisions(SAMS_fs9, push);
    enemies->UpdateWallCollisions(SAMS_fs10, push);

    enemies->UpdateWallCollisions(SAMS_boss_room, push);
}

void Maze_FirstQuadrant::Draw(sf::RenderWindow& window) {
    // draws all walls
    SAMS_c1->Draw(window);
    SAMS_c2->Draw(window);
    SAMS_c3->Draw(window);
    SAMS_c4->Draw(window);
    SAMS_c5->Draw(window);
    SAMS_c6->Draw(window);

    SAMS_fw1->Draw(window);
    SAMS_fw2->Draw(window);
    SAMS_fw3->Draw(window);
    SAMS_fw4->Draw(window);

    SAMS_hw1->Draw(window);
    SAMS_hw2->Draw(window);
    SAMS_hw3->Draw(window);
    SAMS_hw4->Draw(window);
    SAMS_hw5->Draw(window);
    SAMS_hw6->Draw(window);
    SAMS_hw7->Draw(window);

    SAMS_de1->Draw(window);
    SAMS_de2->Draw(window);
    SAMS_de3->Draw(window);
    SAMS_de4->Draw(window);
    SAMS_de5->Draw(window);
    SAMS_de6->Draw(window);
    SAMS_de7->Draw(window);

    SAMS_tj1->Draw(window);
    SAMS_tj2->Draw(window);
    SAMS_tj3->Draw(window);
    SAMS_tj4->Draw(window);
    SAMS_tj5->Draw(window);
    SAMS_tj6->Draw(window);
    SAMS_tj7->Draw(window);

    SAMS_fs1->Draw(window);
    SAMS_fs2->Draw(window);
    SAMS_fs3->Draw(window);
    SAMS_fs4->Draw(window);
    SAMS_fs5->Draw(window);
    SAMS_fs6->Draw(window);
    SAMS_fs7->Draw(window);
    SAMS_fs8->Draw(window);
    SAMS_fs9->Draw(window);
    SAMS_fs10->Draw(window);

    SAMS_boss_room->Draw(window);
}

bool Maze_FirstQuadrant::ColliderCheck(Collider other, float push) {

    bool piece15_cond = SAMS_c1->ColliderCheck(other, push);
    bool piece20_cond = SAMS_c2->ColliderCheck(other, push);
    bool piece28_cond = SAMS_c3->ColliderCheck(other, push);
    bool piece29_cond = SAMS_c4->ColliderCheck(other, push);
    bool piece30_cond = SAMS_c5->ColliderCheck(other, push);
    bool piece33_cond = SAMS_c6->ColliderCheck(other, push);

    bool piece5_cond = SAMS_fw1->ColliderCheck(other, push);
    bool piece9_cond = SAMS_fw2->ColliderCheck(other, push);
    bool piece13_cond = SAMS_fw3->ColliderCheck(other, push);
    bool piece16_cond = SAMS_fw4->ColliderCheck(other, push);

    bool piece6_cond = SAMS_hw1->ColliderCheck(other, push);
    bool piece12_cond = SAMS_hw2->ColliderCheck(other, push);
    bool piece19_cond = SAMS_hw3->ColliderCheck(other, push);
    bool piece22_cond = SAMS_hw4->ColliderCheck(other, push);
    bool piece26_cond = SAMS_hw5->ColliderCheck(other, push);
    bool piece31_cond = SAMS_hw6->ColliderCheck(other, push);
    bool piece35_cond = SAMS_hw7->ColliderCheck(other, push);

    bool piece7_cond = SAMS_de1->ColliderCheck(other, push);
    bool piece17_cond = SAMS_de2->ColliderCheck(other, push);
    bool piece24_cond = SAMS_de3->ColliderCheck(other, push);
    bool piece25_cond = SAMS_de4->ColliderCheck(other, push);
    bool piece27_cond = SAMS_de5->ColliderCheck(other, push);
    bool piece32_cond = SAMS_de6->ColliderCheck(other, push);
    bool piece34_cond = SAMS_de7->ColliderCheck(other, push);

    bool piece8_cond = SAMS_tj1->ColliderCheck(other, push);
    bool piece10_cond = SAMS_tj2->ColliderCheck(other, push);
    bool piece11_cond = SAMS_tj3->ColliderCheck(other, push);
    bool piece14_cond = SAMS_tj4->ColliderCheck(other, push);
    bool piece18_cond = SAMS_tj5->ColliderCheck(other, push);
    bool piece21_cond = SAMS_tj6->ColliderCheck(other, push);
    bool piece23_cond = SAMS_tj7->ColliderCheck(other, push);

    bool piece37_cond = SAMS_fs1->ColliderCheck(other, push);
    bool piece38_cond = SAMS_fs2->ColliderCheck(other, push);
    bool piece39_cond = SAMS_fs3->ColliderCheck(other, push);
    bool piece40_cond = SAMS_fs4->ColliderCheck(other, push);
    bool piece41_cond = SAMS_fs5->ColliderCheck(other, push);
    bool piece42_cond = SAMS_fs6->ColliderCheck(other, push);
    bool piece43_cond = SAMS_fs7->ColliderCheck(other, push);
    bool piece44_cond = SAMS_fs8->ColliderCheck(other, push);
    bool piece45_cond = SAMS_fs9->ColliderCheck(other, push);
    bool piece46_cond = SAMS_fs10->ColliderCheck(other, push);

    bool piece36_cond = SAMS_boss_room->ColliderCheck(other, push);

    // seems to work just as well
    if (piece5_cond ||
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
        piece40_cond ||
        piece41_cond ||
        piece42_cond ||
        piece43_cond ||
        piece44_cond ||
        piece45_cond ||
        piece46_cond)
        return true;

    return false;

}

bool Maze_FirstQuadrant::inMazeWalls(Vector2f coords) {
    return SAMS_c1->inWallStructure(coords) ||
            SAMS_c2->inWallStructure(coords) ||
            SAMS_c3->inWallStructure(coords) ||
            SAMS_c4->inWallStructure(coords) ||
            SAMS_c5->inWallStructure(coords) ||
            SAMS_c6->inWallStructure(coords) ||
            SAMS_fw1->inWallStructure(coords) ||
            SAMS_fw2->inWallStructure(coords) ||
            SAMS_fw3->inWallStructure(coords) ||
            SAMS_fw4->inWallStructure(coords) ||
            SAMS_hw1->inWallStructure(coords) ||
            SAMS_hw2->inWallStructure(coords) ||
            SAMS_hw3->inWallStructure(coords) ||
            SAMS_hw4->inWallStructure(coords) ||
            SAMS_hw5->inWallStructure(coords) ||
            SAMS_hw6->inWallStructure(coords) ||
            SAMS_hw7->inWallStructure(coords) ||
            SAMS_de1->inWallStructure(coords) ||
            SAMS_de2->inWallStructure(coords) ||
            SAMS_de3->inWallStructure(coords) ||
            SAMS_de4->inWallStructure(coords) ||
            SAMS_de5->inWallStructure(coords) ||
            SAMS_de6->inWallStructure(coords) ||
            SAMS_de7->inWallStructure(coords) ||
            SAMS_tj1->inWallStructure(coords) ||
            SAMS_tj2->inWallStructure(coords) ||
            SAMS_tj3->inWallStructure(coords) ||
            SAMS_tj4->inWallStructure(coords) ||
            SAMS_tj5->inWallStructure(coords) ||
            SAMS_tj6->inWallStructure(coords) ||
            SAMS_tj7->inWallStructure(coords) ||
            SAMS_fs1->inWallStructure(coords) ||
            SAMS_fs2->inWallStructure(coords) ||
            SAMS_fs3->inWallStructure(coords) ||
            SAMS_fs4->inWallStructure(coords) ||
            SAMS_fs5->inWallStructure(coords) ||
            SAMS_fs6->inWallStructure(coords) ||
            SAMS_fs7->inWallStructure(coords) ||
            SAMS_fs8->inWallStructure(coords) ||
            SAMS_fs9->inWallStructure(coords) ||
            SAMS_fs10->inWallStructure(coords) ||
            SAMS_boss_room->inWallStructure(coords);
}   

#endif  // MAZE_FIRSTQUADRANT_H