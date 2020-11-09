/* Copyright 2020 Samuel Dunny */
/* Main game class */

#include "inc/Player.h"

using sf::RenderWindow;
using sf::Event;
using sf::VideoMode;
using sf::Vector2i;
using sf::Vector2f;
using sf::Keyboard;
using sf::View;

// speed of the sprite
#define speed 300

// window dimensions (square)
static const float window_dim = 1000.0f;

// resize view function TODO move to Game_engine
void ResizeView(const sf::RenderWindow& window, sf::View& view) {
    float aspectRatio = float(window.getSize().x) / float (window.getSize().y);
    view.setSize(window_dim * aspectRatio, window_dim);
}

int main() {
    // instantiate window, and center coordinates
    RenderWindow window;

    // create and center window
    window.create(VideoMode(window_dim, window_dim), "Game Window", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
    window.clear(sf::Color(150, 150, 150));

    // loading sprite sheet
    sf::Texture base_movement;
    base_movement.loadFromFile("imgs/base_movement.png");
   
    // creating player (given reference to texture, how many images to expect by row and column, animation time, and player speed)
    Player player(&base_movement, Vector2u(4, 4), 0.25f, speed);

    // making player view (to maintain center-screen)
    View player_view(Vector2f(0.0f,0.0f), Vector2f(window_dim, window_dim));

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


    // using these so animation runs at same rate irrespective of machine
    float deltaTime = 0.0f;
    sf::Clock clock;

    // start of game loop
    while(window.isOpen()) {
    
        // used in the update function
        deltaTime = clock.restart().asSeconds();

        // polls for window close event
        Event event;
        while(window.pollEvent(event)) {
            switch (event.type) {
                case Event::Closed:
                    window.close();
                    break;
                case Event::Resized:
                    ResizeView(window, player_view);
                    break;

            }
        }

        

        // .Update() responds to keyboard input and updates the player in the respective direction
        player.Update(deltaTime);

        // must call this after Update, otherwise cammera stutters
        player_view.setCenter(player.getPlayerPos());
       
        window.clear(sf::Color(150, 150, 150));
        window.setView(player_view);
        

        // .Draw() uses this window instance to display the player
        player.Draw(window);
        window.draw(tree);
        window.display();
    }
    // end of game loop


    return 0;
}



/*
 

*/