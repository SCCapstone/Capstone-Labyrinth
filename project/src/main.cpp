/* Copyright 2020 Samuel Dunny */
/* Main game class */

#include "inc/Game_Engine.h"

int main() {
    
    Game_Engine game;
    while(game.running()) {
        game.Update();
        game.Render();
    }

    return 0;
}