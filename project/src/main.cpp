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
#define speed 200

// window dimensions
#define window_width 1400
#define window_height 700

int main() {
    // instantiate window, and center coordinates
    RenderWindow window;
    //Vector2i centerWindow((VideoMode::getDesktopMode().width/2)-755, (VideoMode::getDesktopMode().height/2)-390);

    // create and center window
    window.create(VideoMode(window_width, window_height), "Game Window", sf::Style::Titlebar | sf::Style::Close);
    window.clear(sf::Color(150, 150, 150));
    //window.setPosition(centerWindow);

    // loading sprite sheet
    sf::Texture base_movement;
    base_movement.loadFromFile("imgs/base_movement.png");
   
   // creating player (given reference to texture, how many images to expect by row and column, animation time, and player speed)
    Player player(&base_movement, Vector2u(4, 4), 0.25f, speed);

    // using these so animation runs at same rate irrespective of machine
    float deltaTime = 0.0f;
    sf::Clock clock;

    // start of game loop
    while(window.isOpen()) {
    
        // used in the update function
        deltaTime = clock.restart().asSeconds();

        Event event;
        while(window.pollEvent(event)) {
            switch (event.type) {
                case Event::Closed:
                    window.close();
                    break;
            }
        }

        player.Update(deltaTime);
        window.clear(sf::Color(150, 150, 150));
        player.Draw(window);
        window.display();
    }
    // end of game loop


    return 0;
}