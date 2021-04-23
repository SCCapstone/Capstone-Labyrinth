/* Copyright 2021 Samuel Dunny */
/* Maze_Builder (in header file) */

#ifndef MAZE_BUILDER_H
#define MAZE_BUILDER_H

// include all maze quadrants
#include "Maze_FirstQuadrant.h"
#include "Maze_SecondQuadrant.h"
#include "Maze_ThirdQuadrant.h"
#include "Maze_FourthQuadrant.h"

#include "Maze_SpawnChamber.h"
#include "Background_Map.h"

/* Purpose:
 *  This class instantiates 4 maze quadrants into one maze (step up from maze quadrants)
 */

class Maze_Builder {
protected:    
    // spawn chamber
    Maze_Component* spawnChamber;

    Maze_FirstQuadrant* Sams_Quad;

    Maze_SecondQuadrant* scnd_Quad;
    Maze_ThirdQuadrant* thrd_Quad;
    Maze_FourthQuadrant* frth_Quad;

    // create tile map for background scene
    Background_Map* bg;
    Background_Map* docks_bg;
    Background_Map* docks_bg2;
    Background_Map* docks_bg3;
    Background_Map* docks_bg4;
    Background_Map* docks_bg5;
    Background_Map* butcher_bg;
    Background_Map* butcher_bg2;
    Background_Map* butcher_bg3;
    Background_Map* butcher_bg4;

    // textures used for spawn chamber and background
    Texture brickwall_big;
    Texture docks_wall;
    Texture butcher_wall;
    Texture background;
    Texture docks_background;
    Texture butcher_background;
    Texture sewer_wall;

    Vector2f mazeSizeFactor;

public:
    // constructor
    Maze_Builder(sf::Vector2f factor);

    // destructor
    ~Maze_Builder();

    // contact update functions between walls and the player
    void MazeContactUpdate_Player(Player* player, float push);

    // contact update functions between walls and the boss
    void MazeContactUpdate_Boss(Enemy* boss, float push);

    // contact update function between walls and enemies
    void MazeContactUpdate_Enemies(Enemy_Spawner* enemies, float push);

    // Draw method, draws all walls into referenced window (virtual so it gets overriden)
    void Draw(sf::RenderWindow& window);

    // returns true if Individual's Collider is many contact with any of part of the maze
    bool ColliderCheck(Collider other, float push);

    // function that returns true if given coordinates are in a wall component
    bool inMazeWalls(Vector2f coords);

    Vector2f getFirstQuadBossCoords() { return Sams_Quad->getBossRoomCoords(); }
    Vector2f getSecondQuadBossCoords() { return scnd_Quad->getBossRoomCoords(); }
    Vector2f getThirdQuadBossCoords() { return thrd_Quad->getBossRoomCoords(); }
    Vector2f getFourthQuadBossCoords() { return frth_Quad->getBossRoomCoords(); }

    Vector2f getFirstQuadSizeFactor() { return Sams_Quad->getQuadrantScale(); }
    Vector2f getSecondQuadSizeFactor() { return scnd_Quad->getQuadrantScale(); }
    Vector2f getThirdQuadSizeFactor() { return thrd_Quad->getQuadrantScale(); }
    Vector2f getFourthQuadSizeFactor() { return frth_Quad->getQuadrantScale(); }
};

Maze_Builder::Maze_Builder(sf::Vector2f size) {
    // ensure all instance variables are empty
    this->spawnChamber = nullptr;
    this->Sams_Quad = nullptr;
    this->scnd_Quad = nullptr;
    this->thrd_Quad = nullptr;
    this->frth_Quad = nullptr;
    this->bg = nullptr;
    this->docks_bg = nullptr;
    this->docks_bg2 = nullptr;
    this->docks_bg3 = nullptr;
    this->docks_bg4 = nullptr;
    this->docks_bg5 = nullptr;
    this->butcher_bg = nullptr;
    this->butcher_bg2 = nullptr;
    this->butcher_bg3 = nullptr;
    this->butcher_bg4 = nullptr;

    // scale defined in Wall_Component class

    // load wall and background texture from img/ directory
    // not in parameter so we have the freedom to have multiple textures for walls
    brickwall_big.loadFromFile("imgs/wall_texture.png");
    docks_wall.loadFromFile("imgs/docks_wallV1.png");
    butcher_wall.loadFromFile("imgs/butchery_wallsV3.png");
    background.loadFromFile("imgs/base_floorV2.png");
    docks_background.loadFromFile("imgs/docks_floorV2.png");
    butcher_background.loadFromFile("imgs/butchery_floorV1.png");
    sewer_wall.loadFromFile("imgs/sewer.png");

    this->mazeSizeFactor = size;

    // smallest co-ordinate to largest co-ordinate for both x and y
    // all range parameters defined in Wall.h
    bg = new Background_Map(&background, mazeSizeFactor, 2.0f * X_NEG_RANGE, 2.0f * X_POS_RANGE, 2.0f * Y_NEG_RANGE, 2.0f * Y_POS_RANGE);
                                                             
    // Can add custom backgrounds HERE TODO
    docks_bg = new Background_Map(&docks_background, mazeSizeFactor, -1, 25, 5, 25);
    docks_bg2 = new Background_Map(&docks_background, mazeSizeFactor, -4, -1, 9, 22);
    docks_bg3 = new Background_Map(&docks_background, mazeSizeFactor, -6, -3, 13, 15);
    docks_bg4 = new Background_Map(&docks_background, mazeSizeFactor, 13, 17, 25, 28);
    docks_bg5 = new Background_Map(&docks_background, mazeSizeFactor, 1, 4, 22, 25);
    butcher_bg = new Background_Map(&butcher_background, mazeSizeFactor, -26, -4, 5, 32);
    butcher_bg2 = new Background_Map(&butcher_background, mazeSizeFactor, -25, -4, 2, 5);
    butcher_bg3 = new Background_Map(&butcher_background, mazeSizeFactor, -4, 5, 22, 30);
    butcher_bg4 = new Background_Map(&butcher_background, mazeSizeFactor, -5, -1, 4, 9);

    // position is assumed to be centered at 0.0f, 0.0f, creates starting chamber
    spawnChamber = new Maze_SpawnChamber(&brickwall_big, mazeSizeFactor, Vector2f(0.0f * scale, 0.0f * scale));

    // position is assumed to be centered at 0.0f, 0.0f, creates upper right quadrant
    Sams_Quad = new Maze_FirstQuadrant(mazeSizeFactor);
    scnd_Quad = new Maze_SecondQuadrant(mazeSizeFactor);
    thrd_Quad = new Maze_ThirdQuadrant(mazeSizeFactor);
    frth_Quad = new Maze_FourthQuadrant(mazeSizeFactor);
}

Maze_Builder::~Maze_Builder() { /* empty */ }

void Maze_Builder::MazeContactUpdate_Player(Player* character, float push) {
    // a value of 1.0f is an immovable object, wheres 0.0f would move quickly
    spawnChamber->ColliderCheck(character->GetCollider(), push);
    Sams_Quad->ColliderCheck(character->GetCollider(), push);
    scnd_Quad->ColliderCheck(character->GetCollider(), push);
    thrd_Quad->ColliderCheck(character->GetCollider(), push);
    frth_Quad->ColliderCheck(character->GetCollider(), push);
}

void Maze_Builder::MazeContactUpdate_Boss(Enemy* boss, float push) {
    // a value of 1.0f is an immovable object, wheres 0.0f would move quickly
    spawnChamber->ColliderCheck(boss->GetCollider(), push);
    Sams_Quad->ColliderCheck(boss->GetCollider(), push);
    scnd_Quad->ColliderCheck(boss->GetCollider(), push);
    thrd_Quad->ColliderCheck(boss->GetCollider(), push);
    frth_Quad->ColliderCheck(boss->GetCollider(), push);
}

void Maze_Builder::MazeContactUpdate_Enemies(Enemy_Spawner* enemies, float push) {
    // makes wall the immovable object to minotaur
    enemies->UpdateWallCollisions(spawnChamber, push);
    Sams_Quad->MazeContactUpdate_Enemies(enemies, push);
    scnd_Quad->MazeContactUpdate_Enemies(enemies, push);
    thrd_Quad->MazeContactUpdate_Enemies(enemies, push);
    frth_Quad->MazeContactUpdate_Enemies(enemies, push);
}

void Maze_Builder::Draw(sf::RenderWindow& window) {
    // draw background first, so it gets drawn over
    bg->Draw(window);
    docks_bg->Draw(window);
    docks_bg2->Draw(window);
    docks_bg4->Draw(window);
    butcher_bg->Draw(window);
    butcher_bg2->Draw(window);
    docks_bg3->Draw(window);
    butcher_bg3->Draw(window);
    butcher_bg4->Draw(window);
    docks_bg5->Draw(window);

    // draws all walls
    spawnChamber->Draw(window);
    Sams_Quad->Draw(window);
    scnd_Quad->Draw(window);
    thrd_Quad->Draw(window);
    frth_Quad->Draw(window);
    // TODO get it display on window
    
    
}

bool Maze_Builder::ColliderCheck(Collider other, float push) {

    // all solid objects need a collider
    bool piece1_cond = spawnChamber->ColliderCheck(other, push);
    bool piece2_cond = Sams_Quad->ColliderCheck(other, push);
    bool piece3_cond = scnd_Quad->ColliderCheck(other, push);
    bool piece4_cond = thrd_Quad->ColliderCheck(other, push);
    bool piece5_cond = frth_Quad->ColliderCheck(other, push);

    // return true if anything is in contact with walls
    if (piece1_cond || piece2_cond ||
        piece3_cond || piece4_cond ||
        piece5_cond)
        return true;

    return false;
}

bool Maze_Builder::inMazeWalls(Vector2f coords) {
    return spawnChamber->inWallStructure(coords) ||
            Sams_Quad->inMazeWalls(coords) ||
            scnd_Quad->inMazeWalls(coords) ||
            thrd_Quad->inMazeWalls(coords) ||
            frth_Quad->inMazeWalls(coords);
}

#endif  // MAZE_BUILDER_H
