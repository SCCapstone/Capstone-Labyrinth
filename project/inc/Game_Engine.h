/* Copyright 2020 Samuel Dunny */
/* Game Engine class (in header file) */

#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include <iostream>
#include <SFML/Graphics.hpp>

/* acts as game engine
 * for all functionality in game, except homescreen
 */

class Game_Engine {
// private attributes
private:

// public attributes 
public:
    // constructor and destructor
    Game_Engine();
    ~Game_Engine();

    // responsible for updating players, animations, enemies, ect.
    void Update();

    // responsinle for drawing players, animations, enemies, ect.
    void Render();
    
};

void Game_Engine::Update() {

}

void Game_Engine::Render() {

}


#endif  // GAME_ENGINE_H