/* Copyright 2020 Samuel Dunny */
/* Main game */

#include "inc/Game_Engine.h"
#include "inc/MainMenu.h"

int main() {

   MainMenu mainMenu;
   while(mainMenu.running())
   {
       mainMenu.update();
       mainMenu.render();
   }

    
    Game_Engine game;
    while(game.running()) {
        game.Update();
        game.Render();
    }
    
    return 0;
}