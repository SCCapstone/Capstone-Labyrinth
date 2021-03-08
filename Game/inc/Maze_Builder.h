/* Copyright 2021 Samuel Dunny */
/* Maze_Builder (in header file) */

#ifndef MAZE_BUILDER_H
#define MAZE_BUILDER_H

#include "Maze_Corner.h"
#include "Maze_FourWay.h"
#include "Maze_Hallway.h"
#include "Maze_DeadEnd.h"
#include "Maze_TJunction.h"
#include "Maze_BossRoom.h"
#include "Background_Map.h"

/* Purpose:
 *  This class instantiates many maze components into one maze (step up from maze components)
 */

class Maze_Builder {
protected:
    // wall variables

    // corners
    Maze_Component* SAMS_chamber_rd;
    Maze_Component* SAMS_chamber_ru;
    Maze_Component* SAMS_chamber_ld;
    Maze_Component* SAMS_chamber_lu;
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

    Maze_Component* SAMS_boss_room;

    // create tile map for background scene
    Background_Map* bg;

    // textures used for wall and background
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

    Vector2f getBackGroundBounds_X() { return Vector2f(X_NEG_RANGE, X_POS_RANGE); }
    Vector2f getBackGroundBounds_Y() { return Vector2f(Y_NEG_RANGE, Y_POS_RANGE); }
};

Maze_Builder::Maze_Builder(sf::Vector2f size) {
    // ensure all instance variables are empty
    this->SAMS_chamber_rd = nullptr;
    this->SAMS_chamber_ru = nullptr;
    this->SAMS_chamber_ld = nullptr;
    this->SAMS_chamber_lu = nullptr;
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

    this->SAMS_boss_room = nullptr;

    this->bg = nullptr;

    // scale defined in Wall_Component class

    // load wall texture from img/ directory
    // not in parameter so we have the freedom to have multiple textures for walls
    brickwall_big.loadFromFile("imgs/wall_texture.png");

    background.loadFromFile("imgs/sand.png");

    /* Initializing walls
     * &brickwall:              reference to texture
     * Vector2f(float, float):  size of object
     * Vector2f(float, float):  position in the window
     * bool:                    if corner is facing right
     * bool:                    if corner is facing up
     */

    // position is assumed to be centered at 0.0f, 0.0f, creates starting chamber
    SAMS_chamber_rd = new Maze_Corner(&brickwall_big, size, Vector2f(-3.0f * scale, -3.0f * scale), true, false);
    SAMS_chamber_ru = new Maze_Corner(&brickwall_big, size, Vector2f(-3.0f * scale, 3.0f * scale), true, true);
    SAMS_chamber_ld = new Maze_Corner(&brickwall_big, size, Vector2f(3.0f * scale, -3.0f * scale), false, false);
    SAMS_chamber_lu = new Maze_Corner(&brickwall_big, size, Vector2f(3.0f * scale, 3.0f * scale), false, true);
    SAMS_c1 = new Maze_Corner(&brickwall_big, size, Vector2f(0.0f * scale, -11.0f * scale), true, false);
    SAMS_c2 = new Maze_Corner(&brickwall_big, size, Vector2f(0.0f * scale, -15.0f * scale), true, true);
    SAMS_c3 = new Maze_Corner(&brickwall_big, size, Vector2f(15.0f * scale, -16.0f * scale), false, true);
    SAMS_c4 = new Maze_Corner(&brickwall_big, size, Vector2f(15.0f * scale, -4.0f * scale), false, true);
    SAMS_c5 = new Maze_Corner(&brickwall_big, size, Vector2f(15.0f * scale, -11.0f * scale), false, false);
    SAMS_c6 = new Maze_Corner(&brickwall_big, size, Vector2f(15.0f * scale, -19.0f * scale), true, false);

    SAMS_fw1 = new Maze_FourWay(&brickwall_big, size, Vector2f(7.0f * scale, 0.0f * scale));
    SAMS_fw2 = new Maze_FourWay(&brickwall_big, size, Vector2f(0.0f * scale, -7.0f * scale));
    SAMS_fw3 = new Maze_FourWay(&brickwall_big, size, Vector2f(11.0f * scale, 0.0f * scale));
    SAMS_fw4 = new Maze_FourWay(&brickwall_big, size, Vector2f(11.0f * scale, -11.0f * scale));

    SAMS_hw1 = new Maze_Hallway(&brickwall_big, size, Vector2f(5.0f * scale, -7.0f * scale), true);
    SAMS_hw2 = new Maze_Hallway(&brickwall_big, size, Vector2f(7.0f * scale, -2.0f * scale), false);
    SAMS_hw3 = new Maze_Hallway(&brickwall_big, size, Vector2f(7.0f * scale, -11.0f * scale), false);
    SAMS_hw4 = new Maze_Hallway(&brickwall_big, size, Vector2f(11.0f * scale, 3.0f * scale), false);
    SAMS_hw5 = new Maze_Hallway(&brickwall_big, size, Vector2f(11.0f * scale, -19.0f * scale), false);
    SAMS_hw6 = new Maze_Hallway(&brickwall_big, size, Vector2f(15.0f * scale, -9.0f * scale), false);
    SAMS_hw7 = new Maze_Hallway(&brickwall_big, size, Vector2f(13.0f * scale, -16.0f * scale), true);

    SAMS_de1 = new Maze_DeadEnd(&brickwall_big, size, Vector2f(7.0f * scale, 3.0f * scale), false, true);
    SAMS_de2 = new Maze_DeadEnd(&brickwall_big, size, Vector2f(14.0f * scale, 0.0f * scale), true, false);
    SAMS_de3 = new Maze_DeadEnd(&brickwall_big, size, Vector2f(11.0f * scale, -13.0f * scale), false, true);
    SAMS_de4 = new Maze_DeadEnd(&brickwall_big, size, Vector2f(4.0f * scale, -19.0f * scale), true, true);
    SAMS_de5 = new Maze_DeadEnd(&brickwall_big, size, Vector2f(0.0f * scale, -19.0f * scale), false, false);
    SAMS_de6 = new Maze_DeadEnd(&brickwall_big, size, Vector2f(17.0f * scale, -7.0f * scale), true, false);
    SAMS_de7 = new Maze_DeadEnd(&brickwall_big, size, Vector2f(11.0f * scale, -21.0f * scale), false, false);

    SAMS_tj1 = new Maze_TJunction(&brickwall_big, size, Vector2f(8.0f * scale, -15.0f * scale), true, true);
    SAMS_tj2 = new Maze_TJunction(&brickwall_big, size, Vector2f(7.0f * scale, -7.0f * scale), true, false);
    SAMS_tj3 = new Maze_TJunction(&brickwall_big, size, Vector2f(11.0f * scale, -7.0f * scale), false, false);
    SAMS_tj4 = new Maze_TJunction(&brickwall_big, size, Vector2f(11.0f * scale, -4.0f * scale), false, true);
    SAMS_tj5 = new Maze_TJunction(&brickwall_big, size, Vector2f(3.0f * scale, -11.0f * scale), true, true);
    SAMS_tj6 = new Maze_TJunction(&brickwall_big, size, Vector2f(3.0f * scale, -15.0f * scale), true, false);
    SAMS_tj7 = new Maze_TJunction(&brickwall_big, size, Vector2f(8.0f * scale, -19.0f * scale), true, false);

    SAMS_boss_room = new Maze_BossRoom(&brickwall_big, size, Vector2f(20.0f * scale, -19.0f * scale), true, false);

    // smallest co-ordinate to largest co-ordinate for both x and y
    bg = new Background_Map(&background, size, X_NEG_RANGE, X_POS_RANGE, Y_NEG_RANGE, Y_POS_RANGE);

    std::cout << "[4] Initialized Walls" << std::endl;
}

Maze_Builder::~Maze_Builder() { /* empty */ }

void Maze_Builder::MazeContactUpdate_Player(Player* character, float push) {
    // a value of 1.0f is an immovable object, wheres 0.0f would move quickly
    SAMS_chamber_rd->ColliderCheck(character->GetCollider(), push);
    SAMS_chamber_ru->ColliderCheck(character->GetCollider(), push);
    SAMS_chamber_ld->ColliderCheck(character->GetCollider(), push);
    SAMS_chamber_lu->ColliderCheck(character->GetCollider(), push);
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

    SAMS_boss_room->ColliderCheck(character->GetCollider(), push);
}

void Maze_Builder::MazeContactUpdate_Enemies(Enemy_Spawner* enemies, float push) {
    // makes wall the immovable object to minotaur
    enemies->UpdateWallCollisions(SAMS_chamber_rd, 1.0f);
    enemies->UpdateWallCollisions(SAMS_chamber_ru, 1.0f);
    enemies->UpdateWallCollisions(SAMS_chamber_ld, 1.0f);
    enemies->UpdateWallCollisions(SAMS_chamber_lu, 1.0f);
    enemies->UpdateWallCollisions(SAMS_c1, 1.0f);
    enemies->UpdateWallCollisions(SAMS_c2, 1.0f);
    enemies->UpdateWallCollisions(SAMS_c3, 1.0f);
    enemies->UpdateWallCollisions(SAMS_c4, 1.0f);
    enemies->UpdateWallCollisions(SAMS_c5, 1.0f);
    enemies->UpdateWallCollisions(SAMS_c6, 1.0f);

    enemies->UpdateWallCollisions(SAMS_fw1, 1.0f);
    enemies->UpdateWallCollisions(SAMS_fw2, 1.0f);
    enemies->UpdateWallCollisions(SAMS_fw3, 1.0f);
    enemies->UpdateWallCollisions(SAMS_fw4, 1.0f);

    enemies->UpdateWallCollisions(SAMS_hw1, 1.0f);
    enemies->UpdateWallCollisions(SAMS_hw2, 1.0f);
    enemies->UpdateWallCollisions(SAMS_hw3, 1.0f);
    enemies->UpdateWallCollisions(SAMS_hw4, 1.0f);
    enemies->UpdateWallCollisions(SAMS_hw5, 1.0f);
    enemies->UpdateWallCollisions(SAMS_hw6, 1.0f);
    enemies->UpdateWallCollisions(SAMS_hw7, 1.0f);

    enemies->UpdateWallCollisions(SAMS_de1, 1.0f);
    enemies->UpdateWallCollisions(SAMS_de2, 1.0f);
    enemies->UpdateWallCollisions(SAMS_de3, 1.0f);
    enemies->UpdateWallCollisions(SAMS_de4, 1.0f);
    enemies->UpdateWallCollisions(SAMS_de5, 1.0f);
    enemies->UpdateWallCollisions(SAMS_de6, 1.0f);
    enemies->UpdateWallCollisions(SAMS_de7, 1.0f);

    enemies->UpdateWallCollisions(SAMS_tj1, 1.0f);
    enemies->UpdateWallCollisions(SAMS_tj2, 1.0f);
    enemies->UpdateWallCollisions(SAMS_tj3, 1.0f);
    enemies->UpdateWallCollisions(SAMS_tj4, 1.0f);
    enemies->UpdateWallCollisions(SAMS_tj5, 1.0f);
    enemies->UpdateWallCollisions(SAMS_tj6, 1.0f);
    enemies->UpdateWallCollisions(SAMS_tj7, 1.0f);

    enemies->UpdateWallCollisions(SAMS_boss_room, 1.0f);
}

void Maze_Builder::Draw(sf::RenderWindow& window) {
    // draw background first, so it gets drawn over
    bg->Draw(window);

    // draws all walls
    SAMS_chamber_rd->Draw(window);
    SAMS_chamber_ru->Draw(window);
    SAMS_chamber_ld->Draw(window);
    SAMS_chamber_lu->Draw(window);
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

    SAMS_boss_room->Draw(window);
}

bool Maze_Builder::ColliderCheck(Collider other, float push) {
    bool piece1_cond = SAMS_chamber_rd->ColliderCheck(other, push);
    bool piece2_cond = SAMS_chamber_ru->ColliderCheck(other, push);
    bool piece3_cond = SAMS_chamber_ld->ColliderCheck(other, push);
    bool piece4_cond = SAMS_chamber_lu->ColliderCheck(other, push);
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

    bool piece36_cond = SAMS_boss_room->ColliderCheck(other, push);

    // seems to work just as well
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
        piece36_cond)
        return true;

    return false;
    
}
#endif  // MAZE_BUILDER