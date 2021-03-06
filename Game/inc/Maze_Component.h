/* Copyright 2021 Samuel Dunny */
/* Maze_Component (in header file) */

#ifndef MAZE_COMPONENT_H
#define MAZE_COMPONENT_H

#include "Wall_Strip.h"
#include "Wall_Corner.h"

/* Purpose:
 *  This class instantiates 1 wall component (more added in child classes), 
 *  and any child class that inherits from this base class will be able to modify 
 *  the configuration of those components to create maze structures (step up from wall components)
 */

class Maze_Component {
public:
    // constructor
    Maze_Component(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position) {};

    // destructor
    ~Maze_Component() {};

    // Draw method, draws all walls into referenced window (virtual so it gets overriden)
    virtual void Draw(sf::RenderWindow& window) {};

    // returns true if Individual's Collider is many contact with any of the 3 wall segments (virtual so it gets overriden)
    virtual bool ColliderCheck(Collider other, float push) { return false; }

    // TODO add move function to move whole maze components
};

#endif  // MAZE_COMPONENT_H