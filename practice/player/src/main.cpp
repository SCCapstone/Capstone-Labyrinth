/* Copyright 2020 Samuel Dunny */
/* Main game class */

#include "Player.h"
#include "Animation.h"

using sf::RenderWindow;
using sf::Event;
using sf::VideoMode;
using sf::Vector2i;
using sf::Vector2f;
using sf::Keyboard;
using sf::View;

// speed of the sprite
#define speed 0.75

// window dimensions
#define window_width 1400
#define window_height 700

int main() {
    // instantiate window, and center coordinates
    RenderWindow window;
    Vector2i centerWindow((VideoMode::getDesktopMode().width/2)-755, (VideoMode::getDesktopMode().height/2)-390);

    // create and center window
    window.create(VideoMode(window_width, window_height), "Game Window", sf::Style::Titlebar | sf::Style::Close);
    window.clear(sf::Color::White);
    window.setPosition(centerWindow);

    // instantiate player object
    Player main_character("imgs/forward_1.png");

    // making player view (to maintain center-screen)
    View player_view(Vector2f(0.0f,0.0f), Vector2f(float(window_width), float(window_height)));



    // tree texture
    sf::Texture tree_text;
    tree_text.loadFromFile("imgs/trees_chest.png");
    if (!tree_text.loadFromFile("imgs/trees_chest.png")) {
        std::cout << "ERROR tree" << std::endl;
    }
    //tree_text.setSmooth(true);

    // creating tree sprite
    sf::Sprite tree;
    tree.setTexture(tree_text);
    tree.setOrigin(36, 37);
    tree.setPosition(750, 350);
    tree.setScale(4.0,4.0);




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

        player_view.setCenter(main_character.getPlayerPos());

        window.clear(sf::Color::White);
        window.setView(player_view);
        main_character.drawPlayer(window);
        window.draw(tree);
        window.display();

        while (Keyboard::isKeyPressed(Keyboard::Up)) {
            main_character.movePlayer('u', speed);
            player_view.setCenter(main_character.getPlayerPos());
            window.clear(sf::Color::White);
            window.setView(player_view);
            main_character.drawPlayer(window);
            window.draw(tree);
            window.display();
        }

        while (Keyboard::isKeyPressed(Keyboard::Down)) {
            main_character.movePlayer('d', speed);
            player_view.setCenter(main_character.getPlayerPos());
            window.clear(sf::Color::White);
            window.setView(player_view);
            main_character.drawPlayer(window);
            window.draw(tree);
            window.display();
        }
        
        while (Keyboard::isKeyPressed(Keyboard::Left)) {
            main_character.movePlayer('l', speed);
            player_view.setCenter(main_character.getPlayerPos());
            window.clear(sf::Color::White);
            window.setView(player_view);
            main_character.drawPlayer(window);
            window.draw(tree);
            window.display();
        }

        while (Keyboard::isKeyPressed(Keyboard::Right)) {
            main_character.movePlayer('r', speed);
            player_view.setCenter(main_character.getPlayerPos());
            window.clear(sf::Color::White);
            window.setView(player_view);
            main_character.drawPlayer(window);
            window.draw(tree);
            window.display();
        }

    }
}