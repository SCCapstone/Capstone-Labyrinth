/* Copyright 2020 Samuel Dunny */

#include <unistd.h>             // for usleep
#include <iostream>             // for output
#include <SFML/Graphics.hpp>    // for sfml methods
#include <SFML/Audio.hpp>       // for audio methods

int main() {
    // create window with size 800x800
    sf::RenderWindow window(sf::VideoMode(800, 800), "Walking");
    window.clear(sf::Color::White);

    while (window.isOpen()) {
        // creates event
        sf::Event event;

        // constantly polls window event
        while (window.pollEvent(event)) {
            // if event = closed, close window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // cleans the window each loop
        window.clear();
        window.display();
        usleep(100000);
    }

    return 0;
}