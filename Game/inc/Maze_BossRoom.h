/* Copyright 2021 Samuel Dunny */
/* Maze_BossRoom (in header file) */

#ifndef MAZE_BOSSROOM_H
#define MAZE_BOSSROOM_H

#include "Maze_Component.h"

class Maze_BossRoom : public Maze_Component {
private:
    // 7 components (4 corners, 3 walls)
    Wall_Component* comp1;
    Wall_Component* comp2;
    Wall_Component* comp3;
    Wall_Component* comp4;

    Wall_Component* comp5;
    Wall_Component* comp6;
    Wall_Component* comp7;

    bool horizontal;
    bool facePos;

public:
    // constructor
    Maze_BossRoom(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position, bool horiz, bool facePos);

    // destructor
    ~Maze_BossRoom();

    // Draw method, draws all walls into referenced window
    void Draw(sf::RenderWindow& window);

    // returns true if Individual's Collider is many contact with any of the 3 wall segments
    bool ColliderCheck(Collider other, float push);

    bool inWallStructure(Vector2f pos);
};

// constructs Wall_Strip by passing 3/4 parameters to Wall_Component (polymorphism)
Maze_BossRoom::Maze_BossRoom(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position, bool horiz, bool facePos) :
    Maze_Component(texture, size, position) {

    this->horizontal = horiz;
    this->facePos = facePos;

    // all components originally in the same place
    // faceRight and faceUp don't matter, four-way is symmetric on both axis
    comp1 = new Wall_Corner(texture, size, position, true, true);
    comp2 = new Wall_Corner(texture, size, position, true, false);
    comp3 = new Wall_Corner(texture, size, position, false, false);
    comp4 = new Wall_Corner(texture, size, position, false, true);

    // at least 1 wall be vertical and 1 horizontal, regardless of orientation
    comp5 = new Wall_Strip(texture, size, position, false);
    comp6 = new Wall_Strip(texture, size, position, true);

    /* comp1 = comp2 = comp3 = comp4 = wall_corner (already oriented correctly)
     * ^ all of these currently in same location
     */
    comp1->shiftWallComponent(-2.0f, 2.0f);
    comp2->shiftWallComponent(-2.0f, -2.0f);
    comp3->shiftWallComponent(2.0f, -2.0f);
    comp4->shiftWallComponent(2.0f, 2.0f);

    // entrance on the left side
    if (facePos == true && horiz == true) {
        // need another horizontal strip
        comp7 = new Wall_Strip(texture, size, position, true);
        comp5->shiftWallComponent(-2.0f, 0.0f);
        comp6->shiftWallComponent(0.0f, -2.0f);
        comp7->shiftWallComponent(0.0f, 2.0f);
    }
    // entrance on the top side
    if (facePos == true && horiz == false) {
        // need another vertical strip
        comp7 = new Wall_Strip(texture, size, position, false);
        comp5->shiftWallComponent(2.0f, 0.0f);
        comp6->shiftWallComponent(0.0f, 2.0f);
        comp7->shiftWallComponent(-2.0f, 0.0f);
    }
    // entrance on the left side
    if (facePos == false && horiz == true) {
        // need another horizontal strip
        comp7 = new Wall_Strip(texture, size, position, true);
        comp5->shiftWallComponent(2.0f, 0.0f);
        comp6->shiftWallComponent(0.0f, -2.0f);
        comp7->shiftWallComponent(0.0f, 2.0f);
    }
    // entrance is on the bottom
    else {
        // need another vertical strip
        comp7 = new Wall_Strip(texture, size, position, false);
        comp5->shiftWallComponent(2.0f, 0.0f);
        comp6->shiftWallComponent(0.0f, -2.0f);
        comp7->shiftWallComponent(-2.0f, 0.0f);
    }
}

// empty destructor (handled in Game_Engine)
Maze_BossRoom::~Maze_BossRoom() { /* empty */ }

void Maze_BossRoom::Draw(sf::RenderWindow& window) {
    comp1->Draw(window);
    comp2->Draw(window);
    comp3->Draw(window);
    comp4->Draw(window);
    comp5->Draw(window);
    comp6->Draw(window);
    comp7->Draw(window);
}

bool Maze_BossRoom::ColliderCheck(Collider other, float push) {
    bool comp1_cond = comp1->ColliderCheck(other, push);
    bool comp2_cond = comp2->ColliderCheck(other, push);
    bool comp3_cond = comp3->ColliderCheck(other, push);
    bool comp4_cond = comp4->ColliderCheck(other, push);
    bool comp5_cond = comp5->ColliderCheck(other, push);
    bool comp6_cond = comp6->ColliderCheck(other, push);
    bool comp7_cond = comp7->ColliderCheck(other, push);

    // seems to work just as well
    if (comp1_cond || comp2_cond || comp3_cond || comp4_cond || comp5_cond || comp6_cond || comp7_cond)
        return true;

    return false;
}

bool Maze_BossRoom::inWallStructure(Vector2f pos) {
    return comp1->inWallComponent(pos) ||
        comp2->inWallComponent(pos) ||
        comp3->inWallComponent(pos) ||
        comp4->inWallComponent(pos) ||
        comp5->inWallComponent(pos) ||
        comp6->inWallComponent(pos) ||
        comp7->inWallComponent(pos);
}


#endif  // MAZE_BOSSROOM_H