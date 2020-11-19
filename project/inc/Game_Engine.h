/* Copyright 2020 Samuel Dunny */
/* Game Engine class (in header file) */

#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include "inc/Player.h"
#include "inc/Enemy.h"
#include "inc/Wall.h"
// for random placement
#include <ctime>

using sf::View;
using sf::VideoMode;
using sf::Event;
using sf::Clock;
using sf::Color;

// speed of the sprite
const int speed = 300;

/* Class that acts as game engine
 * Creates window
 * Creates player
 * Creates enemy
 * Creates 2 wall instances
 */

class Game_Engine {
// private attributes
private:
    // variables for window creation
    RenderWindow* window;
    VideoMode videoMode;

    // variable for event checking
    Event ev;

    // variables for main character
    Player* player;
    View player_view;
    Texture base_movement;

    // variables for enemy character
    Enemy* minotaur;
    Texture min_texture;

    // temporary wall variables
    Wall* wall_one;
    Wall* wall_two;
    Texture brickwall;

    // using these so animation runs at same rate irrespective of machine
    float deltaTime;
    Clock clock;

    bool attacking;

    // initializer functions
    void initVariables();
    void initWindow();
    void initPlayer();
    void initWalls();
    void initEnemies();
    
// public attributes 
public:
    // constructor
    Game_Engine();

    // destructor, deletes dynamic objects
    ~Game_Engine();

    // accessors, returns true if window is still open
    const bool running() const {
        return window->isOpen();
    }

    // function to test if Individuals exist (player, enemy)
    bool exists(Individual* other) {
      if (other != nullptr)
         return true;
      return false;
   }

    // updates events
    void pollEvents();

    // function to resize view when window dimensions change
    void ResizeView(const RenderWindow& window, View& view);

    // responsible for updating players, animations, enemies, ect.
    void Update();

    // responsinle for drawing players, animations, enemies, ect.
    void Render();

};

// constructor and destructor
Game_Engine::Game_Engine() {
    // initializes 
    initVariables();
    initWindow();
}

Game_Engine::~Game_Engine() { 
    delete this->player;
    delete this->window;

    delete this->minotaur;

    // temporary wall stuff
    delete this->wall_one;
    delete this->wall_two;
}


// initializer functions
void Game_Engine::initVariables() {
    // clearing any previous memory, not necessary, but safe
    this->window = nullptr;

    initPlayer();
    initWalls();
    initEnemies();

    // initializing deltaTime 
    deltaTime = 0.0f;

    attacking = false;
}

void Game_Engine::initWindow() {
    // setting dimensions of the window
    videoMode.height = 1000.0f;
    videoMode.width = 1000.0f;

    // initializing window (dynamic allocation)
    this->window = new RenderWindow(videoMode, "Game Window", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
    window->setKeyRepeatEnabled(false);

    // sets player view and centers player in window
    player_view.setCenter(Vector2f(0.0f,0.0f));
    player_view.setSize(Vector2f(videoMode.width, videoMode.height)); 
}

void Game_Engine::initPlayer() {
    this->player = nullptr;

    // loading sprite sheet
    base_movement.loadFromFile("imgs/base_movement.png");

    // initializing player
    player = new Player(&base_movement, Vector2u(4, 4), 0.25f, speed);

    std::cout << "Player Total Health: " << player->getTotalHealth() << std::endl;
    std::cout << "Player Attack Value: " << player->getAttackValue() << "\n" << std::endl;
}
    
void Game_Engine::initWalls() {
    // temporary wall stuff
    this->wall_one = nullptr;
    this->wall_two = nullptr;

    // temporary wall stuff
    brickwall.loadFromFile("imgs/wall.png");
    wall_one = new Wall(&brickwall, Vector2f(100.0f, 100.0f), Vector2f(500.0f, 200.0f));
    wall_two = new Wall(&brickwall, Vector2f(100.0f, 100.0f), Vector2f(500.0f, 800.0f));
}

void Game_Engine::initEnemies() {
    this->minotaur = nullptr;

    // loading sprite sheet
    min_texture.loadFromFile("imgs/minotaur.png");

    // initializing enemy
    minotaur = new Enemy(&min_texture, Vector2u(10, 5), 0.45f, speed/8);

    // for random positions
    srand((unsigned) time(0));

    // sets minotaurs position
    minotaur->setRandPos();
    minotaur->setAttackValue(20.0f);

    std::cout << "Enemy Total Health: " << minotaur->getTotalHealth() << std::endl;
    std::cout << "Enemy Attack Val: " << minotaur->getAttackValue() << "\n" << std::endl;
}


// ResizeView function
void Game_Engine::ResizeView(const RenderWindow& window, View& view) {
    float aspectRatio = float(window.getSize().x) / float (window.getSize().y);
    view.setSize(videoMode.width * aspectRatio, videoMode.height);
}


// game driver functions
void Game_Engine::pollEvents() {
    // polls for window close event
    while(window->pollEvent(ev)) {
        switch (ev.type) {

            // window is closing
            case Event::Closed:
                window->close();
                std::cout << "Window Closed (X)" << std::endl;
                break;

            // window is resized
            case Event::Resized:
                ResizeView(*window, player_view);
                std::cout << "Window Resized" << std::endl;
                break;

            // keys have been pressed
            case Event::KeyPressed:
                if (this->ev.key.code == Keyboard::Escape) {
                    window->close();
                    std::cout << "Window Closed (Esc)" << std::endl;
                }
                break;

            // keys have been released
            case Event::KeyReleased:
                // player attacking using the space bar
                if (this->ev.key.code == Keyboard::Space) {
                    if (exists(minotaur) && exists(player)) {
                        if (attacking) {
                            if (minotaur->getTotalHealth() > player->getAttackValue()) {
                                player->commitAttack(*minotaur);
                            }
                            else {
                                minotaur = nullptr;
                                delete minotaur;
                                std::cout << "\nEnemy deleted" << std::endl;
                            }
                        }
                    }
                }
                break;

            // default case
            default:
                break;
        }
    }
}

void Game_Engine::Update() {

    // used in the update function
    deltaTime = clock.restart().asSeconds();

    pollEvents();

    if (exists(player)) {
        // .Update() responds to keyboard input and updates the player in the respective direction
        player->Update(deltaTime);

        // must call this after player.Update(), otherwise cammera stutters
        player_view.setCenter(this->player->getIndividualPos());

        // makes wall the immovable object to player
        wall_one->ColliderCheck(player->GetCollider(), 1.0f);
        wall_two->ColliderCheck(player->GetCollider(), 1.0f);
    }
    if (exists(minotaur)) {
        // updates the minotaur's information
        minotaur->Update(deltaTime);

        // makes wall the immovable object to minotaur
        // a value of 1.0f is an immovable object, wheres 0.0f would move quickly
        wall_one->ColliderCheck(minotaur->GetCollider(), 1.0f);
        wall_two->ColliderCheck(minotaur->GetCollider(), 1.0f);
    }

    // make sure mintaur exits before you utilize it
    if (exists(minotaur) && exists(player)) {

        // if the player and the minotaur's field of vision collide, minotaur chase
        if (player->VisionColliderCheck(minotaur->GetCollider(), 0.0f))
        {
            //std::cout << "Player in View" << std::endl;
            minotaur->Chase(*player, deltaTime);
        }
        
        // if player and enemy collide, proceed to attack each other
        if (player->ColliderCheck(minotaur->GetCollider(), 0.05)) {
            //std::cout << "Colliding" << std::endl;
            if (Keyboard::isKeyPressed(Keyboard::Space)) {
                attacking = true;
                pollEvents();
            }
            else {
                attacking = false;
            }
            // minotaur attacks player
            if (player->getTotalHealth() > minotaur->getAttackValue()) {
                minotaur->ConstantAttack(*player);
            }
            else {
                player = nullptr;
                delete player;
                std::cout << "\nPlayer deleted" << std::endl;
            }
        }
    }    
}

void Game_Engine::Render() {

    // clears window
    window->clear(Color(150, 150, 150));

    window->setView(player_view);
    
    if (exists(player))
        player->Draw(*window);

    if (exists(minotaur))
        minotaur->Draw(*window);

    // temporary wall stuff
    wall_one->Draw(*window);
    wall_two->Draw(*window);

    window->display();
}

#endif  // GAME_ENGINE_H