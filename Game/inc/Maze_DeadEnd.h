/* Copyright 2021 Samuel Dunny */
/* Maze_DeadEnd (in header file) */

#ifndef MAZE_DEADEND_H
#define MAZE_DEADEND_H

#include "Maze_Component.h"

class Maze_DeadEnd : public Maze_Component {
private:
    // conditions for the orientation (not necessary, might use later)
    bool sideways;
    bool facePositive;

    // 4 components
    Wall_Component* comp1;
    Wall_Component* comp2;
    Wall_Component* comp3;

public:
    // constructor
    Maze_DeadEnd(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position, bool sideways, bool facePositive);

    // destructor
    ~Maze_DeadEnd();

    // Draw method, draws all walls into referenced window
    void Draw(sf::RenderWindow& window);

    // returns true if Individual's Collider is many contact with any of the 3 wall segments
    bool ColliderCheck(Collider other, float push);

    bool inWallStructure(Vector2f pos);

};

// constructs Wall_Strip by passing 3/4 parameters to Wall_Component (polymorphism)
Maze_DeadEnd::Maze_DeadEnd(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position, bool sW, bool fPA) :
    Maze_Component(texture, size, position) {

    this->sideways = sW;
    this->facePositive = fPA;
   
    // all components originally in the same place
    if (sW) {
        // 2 horizontal pieces, 1 vertical piece
        comp1 = new Wall_Strip(texture, size, position, true);
        comp2 = new Wall_Strip(texture, size, position, true);
        comp3 = new Wall_Strip(texture, size, position, false);
        comp1->shiftWallComponent(0.0f, -1.0f);
        comp2->shiftWallComponent(0.0f, 1.0f);
        if (fPA) {
            comp3->shiftWallComponent(-1.0f, 0.0f);
        }
        else {
            comp3->shiftWallComponent(1.0f, 0.0f);
        }
    }
    else {
        // 2 vertical pieces, 1 horizontal piece
        comp1 = new Wall_Strip(texture, size, position, false);
        comp2 = new Wall_Strip(texture, size, position, false);
        comp3 = new Wall_Strip(texture, size, position, true);
        comp1->shiftWallComponent(-1.0f, 0.0f);
        comp2->shiftWallComponent(1.0f, 0.0f);
        if (fPA) {
            comp3->shiftWallComponent(0.0f, 1.0f);
        }
        else {
            comp3->shiftWallComponent(0.0f, -1.0f);
        }
    }    
}

// empty destructor (handled in Game_Engine)
Maze_DeadEnd::~Maze_DeadEnd() { /* empty */ }

void Maze_DeadEnd::Draw(sf::RenderWindow& window) {
    comp1->Draw(window);
    comp2->Draw(window);
    comp3->Draw(window);
}

bool Maze_DeadEnd::ColliderCheck(Collider other, float push) {
    bool comp1_cond = comp1->ColliderCheck(other, push);
    bool comp2_cond = comp2->ColliderCheck(other, push);
    bool comp3_cond = comp3->ColliderCheck(other, push);

    // note: leaving out collider check effectively create floor

    // seems to work just as well
    if (comp1_cond || comp2_cond || comp3_cond)
        return true;

    return false;
}

bool Maze_DeadEnd::inWallStructure(Vector2f pos) {
    return comp1->inWallComponent(pos) ||
        comp2->inWallComponent(pos) ||
        comp3->inWallComponent(pos);
}

#endif  // MAZE_DEADEND_H