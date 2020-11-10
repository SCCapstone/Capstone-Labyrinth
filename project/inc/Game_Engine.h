/* Copyright 2020 Samuel Dunny */
/* Game Engine class (in header file) */

#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include "inc/Player.h"

// speed of the sprite
#define speed 300

/* acts as game engine
 * for all functionality in game, except homescreen
 */

class Game_Engine {
// private attributes
private:
    sf::RenderWindow* window;
    sf::VideoMode videoMode;
    sf::Event ev;    
        
    void initVariables();
    void initWindow();  
    
// public attributes 
public:
    // constructor and destructor
    Game_Engine();
    ~Game_Engine();

    // accessors
    const bool running() const;

    // updates events
    void pollEvents();

    // responsible for updating players, animations, enemies, ect.
    void Update();

    // responsinle for drawing players, animations, enemies, ect.
    void Render();

};

void Game_Engine::initVariables() {
    this->window = nullptr;
}

void Game_Engine::initWindow() {
    // setting dimensions of the window
    this->videoMode.height = 1000.0f;
    this->videoMode.width = 1000.0f;
    this->window = new sf::RenderWindow(videoMode, "Game Window", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);   
}

const bool Game_Engine::running() const {
    return window->isOpen();
}

void Game_Engine::pollEvents() {
    // polls for window close event
    while(this->window->pollEvent(ev)) {
        switch (ev.type) {
            case sf::Event::Closed:
                this->window->close();
                break;
            case sf::Event::Resized:
                // TODO add view
                //ResizeView(*window, player_view);
                break;
            case sf::Event::KeyPressed:
                if (this->ev.key.code == sf::Keyboard::Escape)
                    this->window->close();
                break;
        }
    }
}

void Game_Engine::Update() {
    pollEvents();
}

void Game_Engine::Render() {

    // clears window
    this->window->clear(sf::Color(150, 150, 150));

    // TODO draw game objects (player)

    this->window->display();
}


Game_Engine::Game_Engine() {
    this->initVariables();
    this->initWindow();
}

Game_Engine::~Game_Engine() {
    delete this->window;
}


#endif  // GAME_ENGINE_H