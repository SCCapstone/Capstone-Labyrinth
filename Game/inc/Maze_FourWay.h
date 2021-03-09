/* Copyright 2021 Samuel Dunny */
/* Maze_FourWay (in header file) */

#ifndef MAZE_FOURWAY_H
#define MAZE_FOURWAY_H

#include "Maze_Component.h"

class Maze_FourWay : public Maze_Component {
private:
    // 4 components
    Wall_Component* comp1;
    Wall_Component* comp2;
    Wall_Component* comp3;
    Wall_Component* comp4;

public:
    // constructor
    Maze_FourWay(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position);

    // destructor
    ~Maze_FourWay();

    // Draw method, draws all walls into referenced window
    void Draw(sf::RenderWindow& window);

    // returns true if Individual's Collider is many contact with any of the 3 wall segments
    bool ColliderCheck(Collider other, float push);

    bool inWallStructure(Vector2f pos);

};

// constructs Wall_Strip by passing 3/4 parameters to Wall_Component (polymorphism)
Maze_FourWay::Maze_FourWay(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position) :
    Maze_Component(texture, size, position) {

    // all components originally in the same place
    // faceRight and faceUp don't matter, four-way is symmetric on both axis
    comp1 = new Wall_Corner(texture, size, position, true, true);
    comp2 = new Wall_Corner(texture, size, position, true, false);
    comp3 = new Wall_Corner(texture, size, position, false, false);
    comp4 = new Wall_Corner(texture, size, position, false, true);

    /* comp1 = comp2 = comp3 = comp4 = wall_corner (already oriented correctly)
     * ^ all of these currently in same location
     */

    comp1->shiftWallComponent(1.0f, -1.0f);
    comp2->shiftWallComponent(1.0f, 1.0f);
    comp3->shiftWallComponent(-1.0f, 1.0f);
    comp4->shiftWallComponent(-1.0f, -1.0f);
}

// empty destructor (handled in Game_Engine)
Maze_FourWay::~Maze_FourWay() { /* empty */ }

void Maze_FourWay::Draw(sf::RenderWindow& window) {
    comp1->Draw(window);
    comp2->Draw(window);
    comp3->Draw(window);
    comp4->Draw(window);
}

bool Maze_FourWay::ColliderCheck(Collider other, float push) {
    bool comp1_cond = comp1->ColliderCheck(other, push);
    bool comp2_cond = comp2->ColliderCheck(other, push);
    bool comp3_cond = comp3->ColliderCheck(other, push);
    bool comp4_cond = comp4->ColliderCheck(other, push);

    // seems to work just as well
    if (comp1_cond || comp2_cond || comp3_cond || comp4_cond)
        return true;

    return false;
}

bool Maze_FourWay::inWallStructure(Vector2f pos) {
    return comp1->inWallComponent(pos) ||
            comp2->inWallComponent(pos) ||
            comp3->inWallComponent(pos) ||
            comp4->inWallComponent(pos);
}

#endif  // MAZE_FOURWAY_H