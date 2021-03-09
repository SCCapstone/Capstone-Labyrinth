/* Copyright 2021 Samuel Dunny */
/* Maze_Hallway (in header file) */

#ifndef MAZE_HALLWAY_H
#define MAZE_HALLWAY_H

#include "Maze_Component.h"

class Maze_Hallway : public Maze_Component {
private:
    // conditions for the orientation (not necessary, might use later)
    bool horizontal;

    // 4 components
    Wall_Component* comp1;
    Wall_Component* comp2;

public:
    // constructor
    Maze_Hallway(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position, bool horizontal);

    // destructor
    ~Maze_Hallway();

    // Draw method, draws all walls into referenced window
    void Draw(sf::RenderWindow& window);

    // returns true if Individual's Collider is many contact with any of the 3 wall segments
    bool ColliderCheck(Collider other, float push);

    bool inWallStructure(Vector2f pos);

};

// constructs Wall_Strip by passing 3/4 parameters to Wall_Component (polymorphism)
Maze_Hallway::Maze_Hallway(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position, bool hor) :
    Maze_Component(texture, size, position) {

    // all components originally in the same place
    comp1 = new Wall_Strip(texture, size, position, hor);
    comp2 = new Wall_Strip(texture, size, position, hor);

    this->horizontal = hor;

    /* comp1 = vertical wall_strip
     * comp2 = vertical wall_strip
     * ^ all of these currently in same location
     */

    if (hor) {
        comp1->shiftWallComponent(0.0f, -1.0f);
        comp2->shiftWallComponent(0.0f, 1.0f);
    }
    else {
        comp1->shiftWallComponent(-1.0f, 0.0f);
        comp2->shiftWallComponent(1.0f, 0.0f);
    }
}

// empty destructor (handled in Game_Engine)
Maze_Hallway::~Maze_Hallway() { /* empty */ }

void Maze_Hallway::Draw(sf::RenderWindow& window) {
    comp1->Draw(window);
    comp2->Draw(window);
}

bool Maze_Hallway::ColliderCheck(Collider other, float push) {
    bool comp1_cond = comp1->ColliderCheck(other, push);
    bool comp2_cond = comp2->ColliderCheck(other, push);

    // seems to work just as well
    if (comp1_cond || comp2_cond)
        return true;

    return false;
}

bool Maze_Hallway::inWallStructure(Vector2f pos) {
    return comp1->inWallComponent(pos) ||
            comp2->inWallComponent(pos);
}


#endif  // MAZE_HALLWAY_H