/* Copyright 2020 Samuel Dunny */
/* Main game class */

#include "Player.h"

using sf::RenderWindow;
using sf::Event;
using sf::VideoMode;
using sf::Vector2i;
using sf::Keyboard;

// speed of the sprite
#define speed 2.0

int main() {
    // instantiate window, and center coordinates
    RenderWindow window;
    Vector2i centerWindow((VideoMode::getDesktopMode().width/2)-755, (VideoMode::getDesktopMode().height/2)-390);

    // create and center window
    window.create(VideoMode(1500, 700), "Game Window", sf::Style::Titlebar | sf::Style::Close);
    window.clear(sf::Color::White);
    window.setPosition(centerWindow);

    // instantiate player object
    Player main_character("imgs/forward_1.png");

    // Main Loop
    while (window.isOpen()) {

        Event event;

        // Event Loop
        while (window.pollEvent(event)) {
            switch(event.type) {
                case Event::Closed:
                    window.close();
            }
        }

        window.clear(sf::Color::White);
        main_character.drawPlayer(window);
        window.display();

        while (Keyboard::isKeyPressed(Keyboard::Up)) {
            main_character.movePlayer('u', speed);
            window.clear(sf::Color::White);
            main_character.drawPlayer(window);
            window.display();
        }

        while (Keyboard::isKeyPressed(Keyboard::Down)) {
            main_character.movePlayer('d', speed);
            window.clear(sf::Color::White);
            main_character.drawPlayer(window);
            window.display();
        }
        
        while (Keyboard::isKeyPressed(Keyboard::Left)) {
            main_character.movePlayer('l', speed);
            window.clear(sf::Color::White);
            main_character.drawPlayer(window);
            window.display();
        }

        while (Keyboard::isKeyPressed(Keyboard::Right)) {
            main_character.movePlayer('r', speed);
            window.clear(sf::Color::White);
            main_character.drawPlayer(window);
            window.display();
        }
    }
}