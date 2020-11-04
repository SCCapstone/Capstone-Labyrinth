/* Copyright 2020 Samuel Dunny */

#include <unistd.h>             // for usleep
#include "Player.h"             // player class
#include <iostream>             // for output

// dimensions of textures
#define text_width 64
#define text_length 112

// speed of character
#define walk_speed 15

// window dimensions
#define window_width 800
#define window_length 800

// used to load textures
void load_texture(sf::Texture ex_text, std::string name, int w, int l);

int main() {
    // create window with size 800x800
    sf::RenderWindow window(sf::VideoMode(window_width, window_length), "Walking");
    window.clear(sf::Color::White);

    // initializing player
    Player main_char = Player(10.0);
    main_char.setOrigin(text_width/2, text_length/2);
    main_char.setPosition(window_width/2, window_length/2);

     // forward_1 texture
    sf::Texture text_1;
    load_texture(text_1, "imgs/forward_1.png", text_width, text_length);
    // forward_2 texture
    sf::Texture text_2;
    load_texture(text_2, "imgs/forward_2.png", text_width, text_length);
    // forward_3 texture
    sf::Texture text_3;
    load_texture(text_3, "imgs/forward_3.png", text_width, text_length);

    // backward_1 texture
    sf::Texture text_4;
    load_texture(text_4, "imgs/backward_1.png", text_width, text_length);
    // backward_2 texture
    sf::Texture text_5;
    load_texture(text_5, "imgs/backward_2.png", text_width, text_length);
    // backward_3 texture
    sf::Texture text_6;
    load_texture(text_6, "imgs/backward_3.png", text_width, text_length);

    // right_1 texture
    sf::Texture text_7;
    load_texture(text_7, "imgs/right_1.png", text_width, text_length);
    // right_2 texture
    sf::Texture text_8;
    load_texture(text_8, "imgs/right_2.png", text_width, text_length);
    // right_3 texture
    sf::Texture text_9;
    load_texture(text_9, "imgs/right_3.png", text_width, text_length);

    // left_1 texture
    sf::Texture text_10;
    load_texture(text_10, "imgs/left_1.png", text_width, text_length);
    // left_2 texture
    sf::Texture text_11;
    load_texture(text_11, "imgs/left_2.png", text_width, text_length);
    // left_3 texture
    sf::Texture text_12;
    load_texture(text_12, "imgs/left_3.png", text_width, text_length);

    // setting character textures
    main_char.setTextures(text_1, text_2, text_3, text_4,
                            text_5, text_6, text_7, text_8,
                            text_9, text_10, text_11, text_12);


    // main loop
    while (window.isOpen()) {
        // creates event
        sf::Event event;

        // constantly polls window event
        while (window.pollEvent(event)) {
            // if event = closed, close window
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        while (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            window.clear(sf::Color::White);
            main_char.move(0, walk_speed);
            main_char.getSp1().draw(window);
            //std::cout << main_char.getSp1().getPosition() << std::endl;
            window.display();
            usleep(100000);

            window.clear(sf::Color::White);
            main_char.move(0, walk_speed);
            main_char.getSp2().draw(window);
            //std::cout << main_char.getSp2().getPosition() << std::endl;
            window.display();
            usleep(100000);

            window.clear(sf::Color::White);
            main_char.move(0, walk_speed);
            main_char.getSp3().draw(window);
            //std::cout << main_char.getSp3().getPosition() << std::endl;
            window.display();
            usleep(100000);
        }

        while (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        }

        while (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        }

        while (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        }


        // cleans the window each loop, set default image
        window.clear(sf::Color::White);
        window.display();
        usleep(100000);
    }

}

// texture loading function
void load_texture(sf::Texture ex_text, std::string name, int w, int l) {
    ex_text.loadFromFile(name);
    if (!ex_text.loadFromFile(name, sf::IntRect(0, 0, w, l)))
        std::cout << "ERROR opening " << name << " file" << std::endl;
    ex_text.setSmooth(true);

}