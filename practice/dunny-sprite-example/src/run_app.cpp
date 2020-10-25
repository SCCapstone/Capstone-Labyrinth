/* Copyright 2020 Samuel Dunny */
// Audio added by Kurt Walker, 2020

#include <unistd.h>             // for usleep
#include <iostream>             // for output
#include <SFML/Graphics.hpp>    // for sfml methods
#include <SFML/Audio.hpp>       // for audio methods

#define width 64
#define length 112

#define walk_speed 15   // speed of character

int main() {
    // create window with size 800x800
    sf::RenderWindow window(sf::VideoMode(800, 800), "Walking");
    window.clear(sf::Color::White);

    // initialize music file
    sf::Music music;
    if (!music.openFromFile("mysterious-solitude.wav")) {
        std::cout << "Could not find music" << std::endl;
        return -1;
    }

    // starts music playing
    music.play();

    // forward_1 texture
    sf::Texture text_1;
    text_1.loadFromFile("forward_1.png");
    if (!text_1.loadFromFile("forward_1.png", sf::IntRect(0, 0, width, length))) {
        std::cout << "ERROR 1" << std::endl;
    }
    text_1.setSmooth(true);

    // forward_2 texture
    sf::Texture text_2;
    text_2.loadFromFile("forward_2.png");
    if (!text_2.loadFromFile("forward_2.png", sf::IntRect(0, 0, width, length))) {
        std::cout << "ERROR 2" << std::endl;
    }
    text_2.setSmooth(true);

    // forward_3 texture
    sf::Texture text_3;
    text_3.loadFromFile("forward_3.png");
    // 0, 160, 120, 100
    if (!text_3.loadFromFile("forward_3.png", sf::IntRect(0, 0, width, length))) {
        std::cout << "ERROR 3" << std::endl;
    }
    text_3.setSmooth(true);

    // first stage of walking
    sf::Sprite step_1;
    step_1.setTexture(text_1);
    step_1.setOrigin(32, 56);
    step_1.setPosition(100, 100);

    // second stage of walking
    sf::Sprite step_2;
    step_2.setTexture(text_2);
    step_2.setOrigin(32, 56);
    step_2.setPosition(100, 100);

    // third stage of walking
    sf::Sprite step_3;
    step_3.setTexture(text_3);
    step_3.setOrigin(32, 56);
    step_3.setPosition(100, 100);


    // backward_1 texture
    sf::Texture text_4;
    text_4.loadFromFile("backward_1.png");
    if (!text_4.loadFromFile("backward_1.png", sf::IntRect(0, 0, width, length))) {
        std::cout << "ERROR 4" << std::endl;
    }
    text_4.setSmooth(true);

    // backward_2 texture
    sf::Texture text_5;
    text_5.loadFromFile("backward_2.png");
    if (!text_5.loadFromFile("backward_2.png", sf::IntRect(0, 0, width, length))) {
        std::cout << "ERROR 5" << std::endl;
    }
    text_5.setSmooth(true);

    // backward_3 texture
    sf::Texture text_6;
    text_6.loadFromFile("backward_3.png");
    // 0, 160, 120, 100
    if (!text_6.loadFromFile("backward_3.png", sf::IntRect(0, 0, width, length))) {
        std::cout << "ERROR 6" << std::endl;
    }
    text_6.setSmooth(true);

    // first stage of walking backwards
    sf::Sprite step_4;
    step_4.setTexture(text_4);
    step_4.setOrigin(32, 56);
    step_4.setPosition(100, 100);

    // second stage of walking backwards
    sf::Sprite step_5;
    step_5.setTexture(text_5);
    step_5.setOrigin(32, 56);
    step_5.setPosition(100, 100);

    // third stage of walking backwrads
    sf::Sprite step_6;
    step_6.setTexture(text_6);
    step_6.setOrigin(32, 56);
    step_6.setPosition(100, 100);

    // right_1 texture
    sf::Texture text_7;
    text_7.loadFromFile("right_1.png");
    if (!text_7.loadFromFile("right_1.png", sf::IntRect(0, 0, width, length))) {
        std::cout << "ERROR 7" << std::endl;
    }
    text_7.setSmooth(true);

    // right_2 texture
    sf::Texture text_8;
    text_8.loadFromFile("right_2.png");
    if (!text_8.loadFromFile("right_2.png", sf::IntRect(0, 0, width, length))) {
        std::cout << "ERROR 8" << std::endl;
    }
    text_8.setSmooth(true);

    // right_3 texture
    sf::Texture text_9;
    text_9.loadFromFile("right_3.png");
    // 0, 160, 120, 100
    if (!text_9.loadFromFile("right_3.png", sf::IntRect(0, 0, width, length))) {
        std::cout << "ERROR 9" << std::endl;
    }
    text_9.setSmooth(true);

    // first stage of walking right
    sf::Sprite step_7;
    step_7.setTexture(text_7);
    step_7.setOrigin(32, 56);
    step_7.setPosition(100, 100);

    // second stage of walking right
    sf::Sprite step_8;
    step_8.setTexture(text_8);
    step_8.setOrigin(32, 56);
    step_8.setPosition(100, 100);

    // third stage of walking right
    sf::Sprite step_9;
    step_9.setTexture(text_9);
    step_9.setOrigin(32, 56);
    step_9.setPosition(100, 100);

    // left_1 texture
    sf::Texture text_10;
    text_10.loadFromFile("left_1.png");
    if (!text_10.loadFromFile("left_1.png", sf::IntRect(0, 0, width, length))) {
        std::cout << "ERROR 10" << std::endl;
    }
    text_10.setSmooth(true);

    // left_2 texture
    sf::Texture text_11;
    text_11.loadFromFile("left_2.png");
    if (!text_11.loadFromFile("left_2.png", sf::IntRect(0, 0, width, length))) {
        std::cout << "ERROR 11" << std::endl;
    }
    text_11.setSmooth(true);

    // left_3 texture
    sf::Texture text_12;
    text_12.loadFromFile("left_3.png");
    // 0, 160, 120, 100
    if (!text_12.loadFromFile("left_3.png", sf::IntRect(0, 0, width, length))) {
        std::cout << "ERROR 12" << std::endl;
    }
    text_12.setSmooth(true);

    // first stage of walking right
    sf::Sprite step_10;
    step_10.setTexture(text_10);
    step_10.setOrigin(32, 56);
    step_10.setPosition(100, 100);

    // second stage of walking right
    sf::Sprite step_11;
    step_11.setTexture(text_11);
    step_11.setOrigin(32, 56);
    step_11.setPosition(100, 100);

    // third stage of walking right
    sf::Sprite step_12;
    step_12.setTexture(text_12);
    step_12.setOrigin(32, 56);
    step_12.setPosition(100, 100);



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
            step_1.move(0, walk_speed);
            step_2.move(0, walk_speed);
            step_3.move(0, walk_speed);
            step_4.move(0, walk_speed);
            step_5.move(0, walk_speed);
            step_6.move(0, walk_speed);
            step_7.move(0, walk_speed);
            step_8.move(0, walk_speed);
            step_9.move(0, walk_speed);
            step_10.move(0, walk_speed);
            step_11.move(0, walk_speed);
            step_12.move(0, walk_speed);

            window.draw(step_1);
            window.display();
            usleep(100000);

            window.clear(sf::Color::White);
            step_1.move(0, walk_speed);
            step_2.move(0, walk_speed);
            step_3.move(0, walk_speed);
            step_4.move(0, walk_speed);
            step_5.move(0, walk_speed);
            step_6.move(0, walk_speed);
            step_7.move(0, walk_speed);
            step_8.move(0, walk_speed);
            step_9.move(0, walk_speed);
            step_10.move(0, walk_speed);
            step_11.move(0, walk_speed);
            step_12.move(0, walk_speed);

            window.draw(step_2);
            window.display();
            usleep(100000);

            window.clear(sf::Color::White);
            step_1.move(0, walk_speed);
            step_2.move(0, walk_speed);
            step_3.move(0, walk_speed);
            step_4.move(0, walk_speed);
            step_5.move(0, walk_speed);
            step_6.move(0, walk_speed);
            step_7.move(0, walk_speed);
            step_8.move(0, walk_speed);
            step_9.move(0, walk_speed);
            step_10.move(0, walk_speed);
            step_11.move(0, walk_speed);
            step_12.move(0, walk_speed);

            window.draw(step_3);
            window.display();
            usleep(100000);
        }

        while (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            window.clear(sf::Color::White);
            step_1.move(0, -walk_speed);
            step_2.move(0, -walk_speed);
            step_3.move(0, -walk_speed);
            step_4.move(0, -walk_speed);
            step_5.move(0, -walk_speed);
            step_6.move(0, -walk_speed);
            step_7.move(0, -walk_speed);
            step_8.move(0, -walk_speed);
            step_9.move(0, -walk_speed);
            step_10.move(0, -walk_speed);
            step_11.move(0, -walk_speed);
            step_12.move(0, -walk_speed);

            window.draw(step_4);
            window.display();
            usleep(100000);

            window.clear(sf::Color::White);
            step_1.move(0, -walk_speed);
            step_2.move(0, -walk_speed);
            step_3.move(0, -walk_speed);
            step_4.move(0, -walk_speed);
            step_5.move(0, -walk_speed);
            step_6.move(0, -walk_speed);
            step_7.move(0, -walk_speed);
            step_8.move(0, -walk_speed);
            step_9.move(0, -walk_speed);
            step_10.move(0, -walk_speed);
            step_11.move(0, -walk_speed);
            step_12.move(0, -walk_speed);

            window.draw(step_5);
            window.display();
            usleep(100000);

            window.clear(sf::Color::White);
            step_1.move(0, -walk_speed);
            step_2.move(0, -walk_speed);
            step_3.move(0, -walk_speed);
            step_4.move(0, -walk_speed);
            step_5.move(0, -walk_speed);
            step_6.move(0, -walk_speed);
            step_7.move(0, -walk_speed);
            step_8.move(0, -walk_speed);
            step_9.move(0, -walk_speed);
            step_10.move(0, -walk_speed);
            step_11.move(0, -walk_speed);
            step_12.move(0, -walk_speed);

            window.draw(step_6);
            window.display();
            usleep(100000);
        }

        while (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            window.clear(sf::Color::White);
            step_1.move(walk_speed, 0);
            step_2.move(walk_speed, 0);
            step_3.move(walk_speed, 0);
            step_4.move(walk_speed, 0);
            step_5.move(walk_speed, 0);
            step_6.move(walk_speed, 0);
            step_7.move(walk_speed, 0);
            step_8.move(walk_speed, 0);
            step_9.move(walk_speed, 0);
            step_10.move(walk_speed, 0);
            step_11.move(walk_speed, 0);
            step_12.move(walk_speed, 0);

            window.draw(step_7);
            window.display();
            usleep(100000);

            window.clear(sf::Color::White);
            step_1.move(walk_speed, 0);
            step_2.move(walk_speed, 0);
            step_3.move(walk_speed, 0);
            step_4.move(walk_speed, 0);
            step_5.move(walk_speed, 0);
            step_6.move(walk_speed, 0);
            step_7.move(walk_speed, 0);
            step_8.move(walk_speed, 0);
            step_9.move(walk_speed, 0);
            step_10.move(walk_speed, 0);
            step_11.move(walk_speed, 0);
            step_12.move(walk_speed, 0);

            window.draw(step_8);
            window.display();
            usleep(100000);

            window.clear(sf::Color::White);
            step_1.move(walk_speed, 0);
            step_2.move(walk_speed, 0);
            step_3.move(walk_speed, 0);
            step_4.move(walk_speed, 0);
            step_5.move(walk_speed, 0);
            step_6.move(walk_speed, 0);
            step_7.move(walk_speed, 0);
            step_8.move(walk_speed, 0);
            step_9.move(walk_speed, 0);
            step_10.move(walk_speed, 0);
            step_11.move(walk_speed, 0);
            step_12.move(walk_speed, 0);

            window.draw(step_9);
            window.display();
            usleep(100000);
        }

        while (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            window.clear(sf::Color::White);
            step_1.move(-walk_speed, 0);
            step_2.move(-walk_speed, 0);
            step_3.move(-walk_speed, 0);
            step_4.move(-walk_speed, 0);
            step_5.move(-walk_speed, 0);
            step_6.move(-walk_speed, 0);
            step_7.move(-walk_speed, 0);
            step_8.move(-walk_speed, 0);
            step_9.move(-walk_speed, 0);
            step_10.move(-walk_speed, 0);
            step_11.move(-walk_speed, 0);
            step_12.move(-walk_speed, 0);

            window.draw(step_10);
            window.display();
            usleep(100000);

            window.clear(sf::Color::White);
            step_1.move(-walk_speed, 0);
            step_2.move(-walk_speed, 0);
            step_3.move(-walk_speed, 0);
            step_4.move(-walk_speed, 0);
            step_5.move(-walk_speed, 0);
            step_6.move(-walk_speed, 0);
            step_7.move(-walk_speed, 0);
            step_8.move(-walk_speed, 0);
            step_9.move(-walk_speed, 0);
            step_10.move(-walk_speed, 0);
            step_11.move(-walk_speed, 0);
            step_12.move(-walk_speed, 0);

            window.draw(step_11);
            window.display();
            usleep(100000);

            window.clear(sf::Color::White);
            step_1.move(-walk_speed, 0);
            step_2.move(-walk_speed, 0);
            step_3.move(-walk_speed, 0);
            step_4.move(-walk_speed, 0);
            step_5.move(-walk_speed, 0);
            step_6.move(-walk_speed, 0);
            step_7.move(-walk_speed, 0);
            step_8.move(-walk_speed, 0);
            step_9.move(-walk_speed, 0);
            step_10.move(-walk_speed, 0);
            step_11.move(-walk_speed, 0);
            step_12.move(-walk_speed, 0);

            window.draw(step_12);
            window.display();
            usleep(100000);
        }

        // cleans the window each loop, set default image
        window.clear(sf::Color::White);
        window.draw(step_2);
        window.display();
        usleep(100000);
    }
}
