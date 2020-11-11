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


/*
// tree texture TODO make tree (and other design elements) class
    sf::Texture tree_text;
    tree_text.loadFromFile("imgs/trees_chest.png");
    if (!tree_text.loadFromFile("imgs/trees_chest.png")) {
        std::cout << "ERROR tree" << std::endl;
    }
    // creating tree sprite
    sf::Sprite tree;
    tree.setTexture(tree_text);
    tree.setOrigin(36, 37);
    tree.setPosition(750, 350);
    tree.setScale(4.0,4.0);
*/