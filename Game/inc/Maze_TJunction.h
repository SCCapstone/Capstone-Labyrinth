/* Copyright 2021 Samuel Dunny */
/* Maze_TJunction (in header file) */

#ifndef MAZE_TJUNCTION_H
#define MAZE_TJUNCTION_H

#include "Maze_Component.h"

class Maze_TJunction : public Maze_Component {
private:
    // conditions for the orientation (not necessary, might use later)
    bool horizontal;
    bool facePositive;

    // 4 components
    Wall_Component* comp1;
    Wall_Component* comp2;
    Wall_Component* comp3;
    Wall_Component* comp4;

public:
    // constructor
    Maze_TJunction(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position, bool horizontal , bool facePositive);

    // destructor
    ~Maze_TJunction();

    // Draw method, draws all walls into referenced window
    void Draw(sf::RenderWindow& window);

    // returns true if Individual's Collider is many contact with any of the 3 wall segments
    bool ColliderCheck(Collider other, float push);

    bool inWallStructure(Vector2f pos);

};

// constructs Wall_Strip by passing 3/4 parameters to Wall_Component (polymorphism)
Maze_TJunction::Maze_TJunction(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position, bool horiz, bool fPA) :
    Maze_Component(texture, size, position) {

    // all components originally in the same place
    // straight peices can be initialized using parameters
    comp3 = new Wall_Strip(texture, size, position, horiz);
    comp4 = new Wall_Strip(texture, size, position, horiz);

    this->horizontal = horiz;
    this->facePositive = fPA;
    
    if (horiz == true && fPA == true) {
        comp1 = new Wall_Corner(texture, size, position, false, true);
        comp2 = new Wall_Corner(texture, size, position, true, true);

        comp1->shiftWallComponent(-1.0f, -1.0f);
        comp2->shiftWallComponent(1.0f, -1.0f);
        comp3->shiftWallComponent(-1.0f, 1.0f);
        comp4->shiftWallComponent(1.0f, 1.0f);
    }
    else if (horiz == true && fPA == false) {
        comp1 = new Wall_Corner(texture, size, position, false, false);
        comp2 = new Wall_Corner(texture, size, position, true, false);

        comp1->shiftWallComponent(-1.0f, 1.0f);
        comp2->shiftWallComponent(1.0f, 1.0f);
        comp3->shiftWallComponent(-1.0f, -1.0f);
        comp4->shiftWallComponent(1.0f, -1.0f);
    }
    else if (horiz == false && fPA == true) {
        comp1 = new Wall_Corner(texture, size, position, true, true);
        comp2 = new Wall_Corner(texture, size, position, true, false);

        comp1->shiftWallComponent(1.0f, -1.0f);
        comp2->shiftWallComponent(1.0f, 1.0f);
        comp3->shiftWallComponent(-1.0f, -1.0f);
        comp4->shiftWallComponent(-1.0f, 1.0f);
    }
    else {
        comp1 = new Wall_Corner(texture, size, position, false, true);
        comp2 = new Wall_Corner(texture, size, position, false, false);

        comp1->shiftWallComponent(-1.0f, -1.0f);
        comp2->shiftWallComponent(-1.0f, 1.0f);
        comp3->shiftWallComponent(1.0f, -1.0f);
        comp4->shiftWallComponent(1.0f, 1.0f);
    }
}

// empty destructor (handled in Game_Engine)
Maze_TJunction::~Maze_TJunction() { /* empty */ }

void Maze_TJunction::Draw(sf::RenderWindow& window) {
    comp1->Draw(window);
    comp2->Draw(window);
    comp3->Draw(window);
    comp4->Draw(window);
}

bool Maze_TJunction::ColliderCheck(Collider other, float push) {
    bool comp1_cond = comp1->ColliderCheck(other, push);
    bool comp2_cond = comp2->ColliderCheck(other, push);
    bool comp3_cond = comp3->ColliderCheck(other, push);
    bool comp4_cond = comp4->ColliderCheck(other, push);

    // note: leaving out collider check effectively create floor

    // seems to work just as well
    if (comp1_cond || comp2_cond || comp3_cond || comp4_cond)
        return true;

    return false;
}

bool Maze_TJunction::inWallStructure(Vector2f pos) {
    return comp1->inWallComponent(pos) ||
        comp2->inWallComponent(pos) ||
        comp3->inWallComponent(pos) ||
        comp4->inWallComponent(pos);
}


#endif  // MAZE_TJUNCTION_H