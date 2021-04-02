/* Copyright 2021 Samuel Dunny and Caila Buckhaults The Great */
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
    Maze_Component* CAILAS3_c1;
    Maze_Component* CAILAS3_c2;
    Maze_Component* CAILAS3_c3;
    Maze_Component* CAILAS3_c4;
    Maze_Component* CAILAS3_c5;
    Maze_Component* CAILAS3_c6;
    Maze_Component* CAILAS3_c7;
    Maze_Component* CAILAS3_c8;
    Maze_Component* CAILAS3_c9;
    Maze_Component* CAILAS3_c10;
    Maze_Component* CAILAS3_c11;

    // four-ways
    Maze_Component* CAILAS3_fw1;

    // hallways
    Maze_Component* CAILAS3_hw1;
    Maze_Component* CAILAS3_hw2;
    Maze_Component* CAILAS3_hw3;

    // deadends
    Maze_Component* CAILAS3_de1;
    Maze_Component* CAILAS3_de2;
    Maze_Component* CAILAS3_de3;
    Maze_Component* CAILAS3_de4;
    Maze_Component* CAILAS3_de5;
    Maze_Component* CAILAS3_de6;
    Maze_Component* CAILAS3_de7;
    Maze_Component* CAILAS3_de8;
    Maze_Component* CAILAS3_de9;
    Maze_Component* CAILAS3_de10;
    Maze_Component* CAILAS3_de11;

    // t-junction
    Maze_Component* CAILAS3_tj1;
    Maze_Component* CAILAS3_tj2;
    Maze_Component* CAILAS3_tj3;
    Maze_Component* CAILAS3_tj4;

    // filler strips

    // boss room
    Maze_Component* CAILAS3_boss_room;
    Vector2f br_coords;

    // textures used for wall and background
    Texture brickwall_big;

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
    this->CAILAS3_c1 = nullptr;
    this->CAILAS3_c2 = nullptr;
    this->CAILAS3_c3 = nullptr;
    this->CAILAS3_c4 = nullptr;
    this->CAILAS3_c5 = nullptr;
    this->CAILAS3_c6 = nullptr;
    this->CAILAS3_c7 = nullptr;
    this->CAILAS3_c8 = nullptr;
    this->CAILAS3_c9 = nullptr;
    this->CAILAS3_c10 = nullptr;
    this->CAILAS3_c11 = nullptr;

    this->CAILAS3_fw1 = nullptr;

    this->CAILAS3_hw1 = nullptr;
    this->CAILAS3_hw2 = nullptr;
    this->CAILAS3_hw3 = nullptr;

    this->CAILAS3_de1 = nullptr;
    this->CAILAS3_de2 = nullptr;
    this->CAILAS3_de3 = nullptr;
    this->CAILAS3_de4 = nullptr;
    this->CAILAS3_de5 = nullptr;
    this->CAILAS3_de6 = nullptr;
    this->CAILAS3_de7 = nullptr;
    this->CAILAS3_de8 = nullptr;
    this->CAILAS3_de9 = nullptr;
    this->CAILAS3_de10 = nullptr;
    this->CAILAS3_de11 = nullptr;

    this->CAILAS3_tj1 = nullptr;
    this->CAILAS3_tj2 = nullptr;
    this->CAILAS3_tj3 = nullptr;
    this->CAILAS3_tj4 = nullptr;

    this->CAILAS3_boss_room = nullptr;

    // load wall texture from img/ directory
    brickwall_big.loadFromFile("imgs/wall_texture.png");

    // corners
    CAILAS3_c1 = new Maze_Corner(&brickwall_big, size, Vector2f(-12.0f * scale, -16.0f * scale), true, false);
    CAILAS3_c2 = new Maze_Corner(&brickwall_big, size, Vector2f(-3.0f * scale, -12.0f * scale), false, false);
    CAILAS3_c3 = new Maze_Corner(&brickwall_big, size, Vector2f(-5.0f * scale, -7.0f * scale), true, true);
    CAILAS3_c4 = new Maze_Corner(&brickwall_big, size, Vector2f(-7.0f * scale, -2.0f * scale), true, true);
    CAILAS3_c5 = new Maze_Corner(&brickwall_big, size, Vector2f(-11.0f * scale, -2.0f * scale), false, true);
    CAILAS3_c6 = new Maze_Corner(&brickwall_big, size, Vector2f(-23.0f * scale, -4.0f * scale), true, true);
    CAILAS3_c7 = new Maze_Corner(&brickwall_big, size, Vector2f(-31.0f * scale, -3.0f * scale), true, false);
    CAILAS3_c8 = new Maze_Corner(&brickwall_big, size, Vector2f(-31.0f * scale, 2.0f * scale), true, true);
    CAILAS3_c9 = new Maze_Corner(&brickwall_big, size, Vector2f(-28.0f * scale, 6.0f * scale), true, true);
    CAILAS3_c10 = new Maze_Corner(&brickwall_big, size, Vector2f(-23.0f * scale, 0.0f * scale), true, false);
    CAILAS3_c11 = new Maze_Corner(&brickwall_big, size, Vector2f(-20.0f * scale, 0.0f * scale), false, false);

    // four-way intersections
    CAILAS3_fw1 = new Maze_FourWay(&brickwall_big, size, Vector2f(-14.0f * scale, -11.0f * scale));

    // 3-wall length hallways
    CAILAS3_hw1 = new Maze_Hallway(&brickwall_big, size, Vector2f(-23.0f * scale, -8.0f * scale), false);
    CAILAS3_hw2 = new Maze_Hallway(&brickwall_big, size, Vector2f(-18.0f * scale, -8.0f * scale), false);
    CAILAS3_hw3 = new Maze_Hallway(&brickwall_big, size, Vector2f(-18.0f * scale, -5.0f * scale), false);


    // deadend
    CAILAS3_de1 = new Maze_DeadEnd(&brickwall_big, size, Vector2f(-8.0f * scale, -18.0f * scale), false, false);
    CAILAS3_de2 = new Maze_DeadEnd(&brickwall_big, size, Vector2f(-8.0f * scale, -14.0f * scale), true, true);
    CAILAS3_de3 = new Maze_DeadEnd(&brickwall_big, size, Vector2f(-10.0f * scale, -11.0f * scale), true, true);
    CAILAS3_de4 = new Maze_DeadEnd(&brickwall_big, size, Vector2f(-20.0f * scale, -16.0f * scale), true, true);
    CAILAS3_de5 = new Maze_DeadEnd(&brickwall_big, size, Vector2f(-23.0f * scale, -14.0f * scale), true, true);
    CAILAS3_de6 = new Maze_DeadEnd(&brickwall_big, size, Vector2f(-23.0f * scale, -11.0f * scale), false, false);
    CAILAS3_de7 = new Maze_DeadEnd(&brickwall_big, size, Vector2f(-18.0f * scale, -11.0f * scale), true, true);
    CAILAS3_de8 = new Maze_DeadEnd(&brickwall_big, size, Vector2f(-14.0f * scale, -6.0f * scale), true, true);
    CAILAS3_de9 = new Maze_DeadEnd(&brickwall_big, size, Vector2f(-15.0f * scale, -2.0f * scale), true, true);
    CAILAS3_de10 = new Maze_DeadEnd(&brickwall_big, size, Vector2f(-16.0f * scale, 1.0f * scale), false, false);
    CAILAS3_de11 = new Maze_DeadEnd(&brickwall_big, size, Vector2f(-26.0f * scale, 1.0f * scale), true, false);

    // T-junction intersections
    CAILAS3_tj1 = new Maze_TJunction(&brickwall_big, size, Vector2f(-16.0f * scale, -16.0f * scale), true, false);
    CAILAS3_tj2 = new Maze_TJunction(&brickwall_big, size, Vector2f(-4.0f * scale, -16.0f * scale), true, false);
    CAILAS3_tj3 = new Maze_TJunction(&brickwall_big, size, Vector2f(-10.0f * scale, -8.0f * scale), true, false);
    CAILAS3_tj4 = new Maze_TJunction(&brickwall_big, size, Vector2f(-27.0f * scale, -4.0f * scale), false, true);

    // filler segments (used her to fill extra maze space within enemy spawn bounds that we dont want enemies to spawn in)

    // creates room for maze section boss
    this->br_coords = Vector2f(-27.0f * scale, -9.0f * scale);
    CAILAS3_boss_room = new Maze_BossRoom(&brickwall_big, size, br_coords, false, false);
}

Maze_FourthQuadrant::~Maze_FourthQuadrant() { /* empty */ }

void Maze_FourthQuadrant::MazeContactUpdate_Player(Player* character, float push) {
    // a value of 1.0f is an immovable object, wheres 0.0f would move quickly
    CAILAS3_c1->ColliderCheck(character->GetCollider(), push);
    CAILAS3_c2->ColliderCheck(character->GetCollider(), push);
    CAILAS3_c3->ColliderCheck(character->GetCollider(), push);
    CAILAS3_c4->ColliderCheck(character->GetCollider(), push);
    CAILAS3_c5->ColliderCheck(character->GetCollider(), push);
    CAILAS3_c6->ColliderCheck(character->GetCollider(), push);
    CAILAS3_c7->ColliderCheck(character->GetCollider(), push);
    CAILAS3_c8->ColliderCheck(character->GetCollider(), push);
    CAILAS3_c9->ColliderCheck(character->GetCollider(), push);
    CAILAS3_c10->ColliderCheck(character->GetCollider(), push);
    CAILAS3_c11->ColliderCheck(character->GetCollider(), push);

    CAILAS3_fw1->ColliderCheck(character->GetCollider(), push);

    CAILAS3_hw1->ColliderCheck(character->GetCollider(), push);
    CAILAS3_hw2->ColliderCheck(character->GetCollider(), push);
    CAILAS3_hw3->ColliderCheck(character->GetCollider(), push);

    CAILAS3_de1->ColliderCheck(character->GetCollider(), push);
    CAILAS3_de2->ColliderCheck(character->GetCollider(), push);
    CAILAS3_de3->ColliderCheck(character->GetCollider(), push);
    CAILAS3_de4->ColliderCheck(character->GetCollider(), push);
    CAILAS3_de5->ColliderCheck(character->GetCollider(), push);
    CAILAS3_de6->ColliderCheck(character->GetCollider(), push);
    CAILAS3_de7->ColliderCheck(character->GetCollider(), push);
    CAILAS3_de8->ColliderCheck(character->GetCollider(), push);
    CAILAS3_de9->ColliderCheck(character->GetCollider(), push);
    CAILAS3_de10->ColliderCheck(character->GetCollider(), push);
    CAILAS3_de11->ColliderCheck(character->GetCollider(), push);


    CAILAS3_tj1->ColliderCheck(character->GetCollider(), push);
    CAILAS3_tj2->ColliderCheck(character->GetCollider(), push);
    CAILAS3_tj3->ColliderCheck(character->GetCollider(), push);
    CAILAS3_tj4->ColliderCheck(character->GetCollider(), push);

    CAILAS3_boss_room->ColliderCheck(character->GetCollider(), push);

}

void Maze_FourthQuadrant::MazeContactUpdate_Enemies(Enemy_Spawner* enemies, float push) {
    // makes wall the immovable object to minotaur
    enemies->UpdateWallCollisions(CAILAS3_c1, push);
    enemies->UpdateWallCollisions(CAILAS3_c2, push);
    enemies->UpdateWallCollisions(CAILAS3_c3, push);
    enemies->UpdateWallCollisions(CAILAS3_c4, push);
    enemies->UpdateWallCollisions(CAILAS3_c5, push);
    enemies->UpdateWallCollisions(CAILAS3_c6, push);
    enemies->UpdateWallCollisions(CAILAS3_c7, push);
    enemies->UpdateWallCollisions(CAILAS3_c8, push);
    enemies->UpdateWallCollisions(CAILAS3_c9, push);
    enemies->UpdateWallCollisions(CAILAS3_c10, push);
    enemies->UpdateWallCollisions(CAILAS3_c11, push);

    enemies->UpdateWallCollisions(CAILAS3_fw1, push);

    enemies->UpdateWallCollisions(CAILAS3_hw1, push);
    enemies->UpdateWallCollisions(CAILAS3_hw2, push);
    enemies->UpdateWallCollisions(CAILAS3_hw3, push);

    enemies->UpdateWallCollisions(CAILAS3_de1, push);
    enemies->UpdateWallCollisions(CAILAS3_de2, push);
    enemies->UpdateWallCollisions(CAILAS3_de3, push);
    enemies->UpdateWallCollisions(CAILAS3_de4, push);
    enemies->UpdateWallCollisions(CAILAS3_de5, push);
    enemies->UpdateWallCollisions(CAILAS3_de6, push);
    enemies->UpdateWallCollisions(CAILAS3_de7, push);
    enemies->UpdateWallCollisions(CAILAS3_de8, push);
    enemies->UpdateWallCollisions(CAILAS3_de9, push);
    enemies->UpdateWallCollisions(CAILAS3_de10, push);
    enemies->UpdateWallCollisions(CAILAS3_de11, push);


    enemies->UpdateWallCollisions(CAILAS3_tj1, push);
    enemies->UpdateWallCollisions(CAILAS3_tj2, push);
    enemies->UpdateWallCollisions(CAILAS3_tj3, push);
    enemies->UpdateWallCollisions(CAILAS3_tj4, push);

    enemies->UpdateWallCollisions(CAILAS3_boss_room, push);
}

void Maze_FourthQuadrant::Draw(sf::RenderWindow& window) {
    // draws all walls
    CAILAS3_c1->Draw(window);
    CAILAS3_c2->Draw(window);
    CAILAS3_c3->Draw(window);
    CAILAS3_c4->Draw(window);
    CAILAS3_c5->Draw(window);
    CAILAS3_c6->Draw(window);
    CAILAS3_c7->Draw(window);
    CAILAS3_c8->Draw(window);
    CAILAS3_c9->Draw(window);
    CAILAS3_c10->Draw(window);
    CAILAS3_c11->Draw(window);

    CAILAS3_fw1->Draw(window);

    CAILAS3_hw1->Draw(window);
    CAILAS3_hw2->Draw(window);
    CAILAS3_hw3->Draw(window);

    CAILAS3_de1->Draw(window);
    CAILAS3_de2->Draw(window);
    CAILAS3_de3->Draw(window);
    CAILAS3_de4->Draw(window);
    CAILAS3_de5->Draw(window);
    CAILAS3_de6->Draw(window);
    CAILAS3_de7->Draw(window);
    CAILAS3_de8->Draw(window);
    CAILAS3_de9->Draw(window);
    CAILAS3_de10->Draw(window);
    CAILAS3_de11->Draw(window);

    CAILAS3_tj1->Draw(window);
    CAILAS3_tj2->Draw(window);
    CAILAS3_tj3->Draw(window);
    CAILAS3_tj4->Draw(window);

    CAILAS3_boss_room->Draw(window);
}

bool Maze_FourthQuadrant::ColliderCheck(Collider other, float push) {
    //return all dis
    bool piece1_cond = CAILAS3_c1->ColliderCheck(other, push);
    bool piece2_cond = CAILAS3_c2->ColliderCheck(other, push);
    bool piece3_cond = CAILAS3_c3->ColliderCheck(other, push);
    bool piece4_cond = CAILAS3_c4->ColliderCheck(other, push);
    bool piece5_cond = CAILAS3_c5->ColliderCheck(other, push);
    bool piece6_cond = CAILAS3_c6->ColliderCheck(other, push);
    bool piece7_cond = CAILAS3_c7->ColliderCheck(other, push);
    bool piece8_cond = CAILAS3_c8->ColliderCheck(other, push);
    bool piece9_cond = CAILAS3_c9->ColliderCheck(other, push);
    bool piece10_cond = CAILAS3_c10->ColliderCheck(other, push);
    bool piece11_cond = CAILAS3_c11->ColliderCheck(other, push);

    bool piece12_cond = CAILAS3_fw1->ColliderCheck(other, push);

    bool piece13_cond = CAILAS3_hw1->ColliderCheck(other, push);
    bool piece14_cond = CAILAS3_hw2->ColliderCheck(other, push);
    bool piece15_cond = CAILAS3_hw3->ColliderCheck(other, push);

    bool piece16_cond = CAILAS3_de1->ColliderCheck(other, push);
    bool piece17_cond = CAILAS3_de2->ColliderCheck(other, push);
    bool piece18_cond = CAILAS3_de3->ColliderCheck(other, push);
    bool piece19_cond = CAILAS3_de4->ColliderCheck(other, push);
    bool piece20_cond = CAILAS3_de5->ColliderCheck(other, push);
    bool piece21_cond = CAILAS3_de6->ColliderCheck(other, push);
    bool piece22_cond = CAILAS3_de7->ColliderCheck(other, push);
    bool piece23_cond = CAILAS3_de8->ColliderCheck(other, push);
    bool piece24_cond = CAILAS3_de9->ColliderCheck(other, push);
    bool piece25_cond = CAILAS3_de10->ColliderCheck(other, push);
    bool piece26_cond = CAILAS3_de11->ColliderCheck(other, push);

    bool piece27_cond = CAILAS3_tj1->ColliderCheck(other, push);
    bool piece28_cond = CAILAS3_tj2->ColliderCheck(other, push);
    bool piece29_cond = CAILAS3_tj3->ColliderCheck(other, push);
    bool piece30_cond = CAILAS3_tj4->ColliderCheck(other, push);

    bool piece31_cond = CAILAS3_boss_room->ColliderCheck(other, push);

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
        piece31_cond)
        return true;

    return false;

}

bool Maze_FourthQuadrant::inMazeWalls(Vector2f coords) {
    // default filler value
    return CAILAS3_c1->inWallStructure(coords) ||
        CAILAS3_c2->inWallStructure(coords) ||
        CAILAS3_c3->inWallStructure(coords) ||
        CAILAS3_c4->inWallStructure(coords) ||
        CAILAS3_c5->inWallStructure(coords) ||
        CAILAS3_c6->inWallStructure(coords) ||
        CAILAS3_c7->inWallStructure(coords) ||
        CAILAS3_c8->inWallStructure(coords) ||
        CAILAS3_c9->inWallStructure(coords) ||
        CAILAS3_c10->inWallStructure(coords) ||
        CAILAS3_c11->inWallStructure(coords) ||
        CAILAS3_fw1->inWallStructure(coords) ||
        CAILAS3_hw1->inWallStructure(coords) ||
        CAILAS3_hw2->inWallStructure(coords) ||
        CAILAS3_hw3->inWallStructure(coords) ||
        CAILAS3_de1->inWallStructure(coords) ||
        CAILAS3_de2->inWallStructure(coords) ||
        CAILAS3_de3->inWallStructure(coords) ||
        CAILAS3_de4->inWallStructure(coords) ||
        CAILAS3_de5->inWallStructure(coords) ||
        CAILAS3_de6->inWallStructure(coords) ||
        CAILAS3_de7->inWallStructure(coords) ||
        CAILAS3_de8->inWallStructure(coords) ||
        CAILAS3_de9->inWallStructure(coords) ||
        CAILAS3_de10->inWallStructure(coords) ||
        CAILAS3_de11->inWallStructure(coords) ||
        CAILAS3_tj1->inWallStructure(coords) ||
        CAILAS3_tj2->inWallStructure(coords) ||
        CAILAS3_tj3->inWallStructure(coords) ||
        CAILAS3_tj4->inWallStructure(coords) ||
        CAILAS3_boss_room->inWallStructure(coords);
}

#endif  // MAZE_FOURTHQUADRANT_H