/* Copyright 2021 Samuel Dunny */
/* Maze_Corner (in header file) */

#ifndef MAZE_CORNER_H
#define MAZE_CORNER_H

#include "Maze_Component.h"

class Maze_Corner : public Maze_Component {
private:
    // conditions for the corner orientation (not necessary, might use later)
    bool faceRight;
    bool faceUp;

    // 4 components
    Wall_Component* comp1;
    Wall_Component* comp2;
    Wall_Component* comp3;
    Wall_Component* comp4;

public:
    // constructor
    Maze_Corner(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position, bool faceRight, bool faceUp);

    // destructor
    ~Maze_Corner();

    // Draw method, draws all walls into referenced window
    void Draw(sf::RenderWindow& window);

    // returns true if Individual's Collider is many contact with any of the 3 wall segments
    bool ColliderCheck(Collider other, float push);

    bool inWallStructure(Vector2f pos);

    Vector2f getOuterCornerCoord();

};

// constructs Wall_Strip by passing 3/4 parameters to Wall_Component (polymorphism)
Maze_Corner::Maze_Corner(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position, bool faceRight, bool faceUp) :
    Maze_Component(texture, size, position) {
    
    // all components originally in the same place
    // strip 2 will always needs to be horizontal instead of vertical (I picked arbitrarily)
    comp1 = new Wall_Strip(texture, size, position, false);
    comp2 = new Wall_Strip(texture, size, position, true);

    // need to intitiate two more wall components (can initiate using parameters)
    comp3 = new Wall_Corner(texture, size, position, faceRight, faceUp);
    comp4 = new Wall_Corner(texture, size, position, faceRight, faceUp);

    this->faceRight = faceRight;
    this->faceUp = faceUp;

    /* comp1 = vertical wall_strip
     * comp2 = horizontal wall_strip
     * comp3 = comp4 = wall_corner (already oriented correctly)
     * ^ all of these currently in same location
     */

    // right up
    if (faceRight == true && faceUp == true) {
        comp1->shiftWallComponent(-1.0f, -1.0f);
        comp2->shiftWallComponent(1.0f, 1.0f);
        comp3->shiftWallComponent(-1.0f, 1.0f);
        comp4->shiftWallComponent(1.0f, -1.0f);
    }
    // right down
    if (faceRight == true && faceUp == false) {
        comp1->shiftWallComponent(-1.0f, 1.0f);
        comp2->shiftWallComponent(1.0f, -1.0f);
        comp3->shiftWallComponent(-1.0f, -1.0f);
        comp4->shiftWallComponent(1.0f, 1.0f);
    }
    // left up
    if (faceRight == false && faceUp == true) {
        comp1->shiftWallComponent(1.0f, -1.0f);
        comp2->shiftWallComponent(-1.0f, 1.0f);
        comp3->shiftWallComponent(1.0f, 1.0f);
        comp4->shiftWallComponent(-1.0f, -1.0f);
    }
    // left down
    if (faceRight == false && faceUp == false) {
        comp1->shiftWallComponent(1.0f, 1.0f);
        comp2->shiftWallComponent(-1.0f, -1.0f);
        comp3->shiftWallComponent(1.0f, -1.0f);
        comp4->shiftWallComponent(-1.0f, 1.0f);
    }
}

// empty destructor (handled in Game_Engine)
Maze_Corner::~Maze_Corner() { /* empty */ }

void Maze_Corner::Draw(sf::RenderWindow& window) {
    comp1->Draw(window);
    comp2->Draw(window);
    comp3->Draw(window);
    comp4->Draw(window);
}

bool Maze_Corner::ColliderCheck(Collider other, float push) {
    bool comp1_cond = comp1->ColliderCheck(other, push);
    bool comp2_cond = comp2->ColliderCheck(other, push);
    bool comp3_cond = comp3->ColliderCheck(other, push);
    bool comp4_cond = comp4->ColliderCheck(other, push);

    // overkill, but just to be safe (should be impossible to have contact with all pieces at once)
    /*
    if (comp1_cond)
        return true;
    if (comp2_cond)
        return true;
    if (comp3_cond)
        return true;
    if (comp4_cond)
        return true;

    if (comp1_cond && comp2_cond)
        return true;
    if (comp1_cond && comp3_cond)
        return true;
    if (comp1_cond && comp4_cond)
        return true;
    if (comp2_cond && comp3_cond)
        return true;
    if (comp2_cond && comp4_cond)
        return true;
    if (comp3_cond && comp4_cond)
        return true;

    if (comp1_cond && comp2_cond && comp3_cond)
        return true;
    if (comp1_cond && comp2_cond && comp4_cond)
        return true;
    if (comp1_cond && comp3_cond && comp4_cond)
        return true;
    if (comp2_cond && comp3_cond && comp4_cond)
        return true;

    if (comp1_cond && comp2_cond && comp3_cond && comp4_cond)
        return true;
        */

    // seems to work just as well
    if (comp1_cond || comp2_cond || comp3_cond || comp4_cond)
        return true;

    return false;
}

bool Maze_Corner::inWallStructure(Vector2f pos) {
    return comp1->inWallComponent(pos) ||
        comp2->inWallComponent(pos) ||
        comp3->inWallComponent(pos) ||
        comp4->inWallComponent(pos);
}

Vector2f Maze_Corner::getOuterCornerCoord() {
    // comp3 is always the furthest corner coordinate
    return comp3->getCenterWallCoords();
}


#endif  // MAZE_CORNER_H