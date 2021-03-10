/* Copyright 2021 Samuel Dunny */
/* Maze_SpawnChamber (in header file) */

#ifndef MAZE_SPAWNCHAMBER_H
#define MAZE_SPAWNCHAMBER_H

#include "Maze_Component.h"

class Maze_SpawnChamber : public Maze_Component {
private:
    // 8 corners
    Wall_Component* corn1;
    Wall_Component* corn2;
    Wall_Component* corn3;
    Wall_Component* corn4;
    Wall_Component* corn5;
    Wall_Component* corn6;
    Wall_Component* corn7;
    Wall_Component* corn8;

    // 8 strips
    Wall_Component* strip1;
    Wall_Component* strip2;
    Wall_Component* strip3;
    Wall_Component* strip4;
    Wall_Component* strip5;
    Wall_Component* strip6;
    Wall_Component* strip7;
    Wall_Component* strip8;

public:
    // constructor
    Maze_SpawnChamber(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position);

    // destructor
    ~Maze_SpawnChamber();

    // Draw method, draws all walls into referenced window
    void Draw(sf::RenderWindow& window);

    // returns true if Individual's Collider is many contact with any of the 3 wall segments
    bool ColliderCheck(Collider other, float push);

    bool inWallStructure(Vector2f pos);

};

// constructs Wall_Strip by passing 3/4 parameters to Wall_Component (polymorphism)
Maze_SpawnChamber::Maze_SpawnChamber(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position) :
    Maze_Component(texture, size, position) {

    // all components originally in the same place
    // orientation doesn't matter, symmetric shape on both axis

    // bottom left corners
    corn1 = new Wall_Corner(texture, size, position, true, true);
    corn2 = new Wall_Corner(texture, size, position, true, true);

    // top left corners
    corn3 = new Wall_Corner(texture, size, position, true, false);
    corn4 = new Wall_Corner(texture, size, position, true, false);

    // top right corners
    corn5 = new Wall_Corner(texture, size, position, false, false);
    corn6 = new Wall_Corner(texture, size, position, false, false);

    // bottom right corners
    corn7 = new Wall_Corner(texture, size, position, false, true);
    corn8 = new Wall_Corner(texture, size, position, false, true);

    // 4 horizontal strips
    strip1 = new Wall_Strip(texture, size, position, true);
    strip2 = new Wall_Strip(texture, size, position, true);
    strip3 = new Wall_Strip(texture, size, position, true);
    strip4 = new Wall_Strip(texture, size, position, true);

    // 4 vertical strips
    strip5 = new Wall_Strip(texture, size, position, false);
    strip6 = new Wall_Strip(texture, size, position, false);
    strip7 = new Wall_Strip(texture, size, position, false);
    strip8 = new Wall_Strip(texture, size, position, false);

    corn1->shiftWallComponent(-2.0f, 2.0f);
    corn2->shiftWallComponent(-4.0f, 4.0f);
    corn3->shiftWallComponent(-2.0f, -2.0f);
    corn4->shiftWallComponent(-4.0f, -4.0f);
    corn5->shiftWallComponent(2.0f, -2.0f);
    corn6->shiftWallComponent(4.0f, -4.0f);
    corn7->shiftWallComponent(2.0f, 2.0f);
    corn8->shiftWallComponent(4.0f, 4.0f);

    strip1->shiftWallComponent(-2.0f, 4.0f);
    strip2->shiftWallComponent(-2.0f, -4.0f);
    strip3->shiftWallComponent(2.0f, 4.0f);
    strip4->shiftWallComponent(2.0f, -4.0f);
    strip5->shiftWallComponent(-4.0f, 2.0f);
    strip6->shiftWallComponent(-4.0f, -2.0f);
    strip7->shiftWallComponent(4.0f, 2.0f);
    strip8->shiftWallComponent(4.0f, -2.0f);
    
}

// empty destructor (handled in Game_Engine)
Maze_SpawnChamber::~Maze_SpawnChamber() { /* empty */ }

void Maze_SpawnChamber::Draw(sf::RenderWindow& window) {
    corn1->Draw(window);
    corn2->Draw(window);
    corn3->Draw(window);
    corn4->Draw(window);
    corn5->Draw(window);
    corn6->Draw(window);
    corn7->Draw(window);
    corn8->Draw(window);

    strip1->Draw(window);
    strip2->Draw(window);
    strip3->Draw(window);
    strip4->Draw(window);
    strip5->Draw(window);
    strip6->Draw(window);
    strip7->Draw(window);
    strip8->Draw(window);
}

bool Maze_SpawnChamber::ColliderCheck(Collider other, float push) {
    bool corn1_cond = corn1->ColliderCheck(other, push);
    bool corn2_cond = corn2->ColliderCheck(other, push);
    bool corn3_cond = corn3->ColliderCheck(other, push);
    bool corn4_cond = corn4->ColliderCheck(other, push);
    bool corn5_cond = corn5->ColliderCheck(other, push);
    bool corn6_cond = corn6->ColliderCheck(other, push);
    bool corn7_cond = corn7->ColliderCheck(other, push);
    bool corn8_cond = corn8->ColliderCheck(other, push);

    bool strip1_cond = strip1->ColliderCheck(other, push);
    bool strip2_cond = strip2->ColliderCheck(other, push);
    bool strip3_cond = strip3->ColliderCheck(other, push);
    bool strip4_cond = strip4->ColliderCheck(other, push);
    bool strip5_cond = strip5->ColliderCheck(other, push);
    bool strip6_cond = strip6->ColliderCheck(other, push);
    bool strip7_cond = strip7->ColliderCheck(other, push);
    bool strip8_cond = strip8->ColliderCheck(other, push);

    // seems to work just as well
    if (corn1_cond ||
        corn2_cond ||
        corn3_cond ||
        corn4_cond ||
        corn5_cond ||
        corn6_cond ||
        corn7_cond ||
        corn8_cond ||
        strip1_cond ||
        strip2_cond ||
        strip3_cond ||
        strip4_cond ||
        strip5_cond ||
        strip6_cond ||
        strip7_cond ||
        strip8_cond)
        return true;

    return false;
}

bool Maze_SpawnChamber::inWallStructure(Vector2f pos) {
    // bottom left
    Vector2f bl_bounds = corn2->getCenterWallCoords();

    // top left
    Vector2f tl_bounds = corn4->getCenterWallCoords();

    // top right
    Vector2f tr_bounds = corn6->getCenterWallCoords();

    // bottom right
    Vector2f br_bounds = corn8->getCenterWallCoords();

    // return true if given coords are anywhere in spawn chamber bounds (keeps enemies out of spawn)
    if (pos.x <= br_bounds.x &&
        pos.x >= bl_bounds.x &&
        pos.y >= tl_bounds.y &&
        pos.y <= bl_bounds.y)
        return true;

    return false;
}

#endif  // MAZE_SPAWNCHAMBER_H