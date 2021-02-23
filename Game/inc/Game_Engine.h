/* Copyright 2020 Samuel Dunny */
/* Game Engine class (in header file) */

#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include "Player.h"
#include "Enemy_Spawner.h"
#include "Wall.h"
#include <ctime>

using sf::View;
using sf::VideoMode;
using sf::Event;
using sf::Clock;
using sf::Color;

/* Class that acts as game engine
 * Creates window
 * Creates player
 * Creates enemy spawner
 * Creates 2 wall instances
 */

// how many minotaurs to spawn
const static int minotaur_amount = 2;

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
    Enemy_Spawner* minotaurs;
    Texture min_texture;

    // wall variables
    Wall* wall_one;
    Wall* wall_two;
    Texture brickwall;

    // using these so animation runs at same rate irrespective of machine
    float deltaTime;
    Clock clock;

    // initializer functions
    void initVariables();
    void initPlayer();
    void initEnemies();
    void initWalls();
    void initWindow();

    void ResizeView(const RenderWindow& window, View& view);

    void pollEvents();

    void WallContactUpdate(Individual* character, Wall* aWall, float push);

    // function to test if Individuals exist (player, enemy, etc.)
    bool exists(Individual* other) {
      if (other != nullptr)
         return true;
      return false;
   }
    
// public attributes 
public:
    Game_Engine();

    ~Game_Engine();

    void Update();

    void Render();

    // accessors, returns true if window is still open
    const bool running() const {
        return window->isOpen();
    }
};

/* Public Functions in order:
 * Game_Engine:     default constructor, calls all initializer functions
 * ~Game_Engine:    destructor, deletes dynamic objects
 * Update:          updates all game logic (interations between players, enemies, the environment, and movement in the window)
 * Render:          draws and displays all game objects (player, enemies, walls)
 */
Game_Engine::Game_Engine() {
    std::cout << "-----STARTING INITIALIZATION-----" << std::endl;

    // initializes
    initVariables();
    initWindow();

    std::cout << "-----INITIALIZATION FINISHED-----\n" << std::endl;
}

Game_Engine::~Game_Engine() { 
    delete this->window;

    delete this->player;

    // dont need destructor for enemies

    // temporary wall stuff
    delete this->wall_one;
    delete this->wall_two;
}

void Game_Engine::Update() {
    // used in the update function
    deltaTime = clock.restart().asSeconds();

    // poll events
    pollEvents();

    // update player information if it exists
    if (exists(player)) {
        // .Update() responds to keyboard input and updates the player in the respective direction
        player->Update(deltaTime);

        // must call this after player.Update(), otherwise cammera stutters
        player_view.setCenter(this->player->getIndividualPos());

        // makes wall the immovable object to player
        WallContactUpdate(player, wall_one, 1.0f);
        WallContactUpdate(player, wall_two, 1.0f);
    }

    // update enemy information if any exist
    if (!(minotaurs->Empty())) {
        // updates the minotaur's information
        minotaurs->Update(deltaTime);

        // makes wall the immovable object to minotaur
        minotaurs->UpdateWallCollisions(wall_one, 1.0f);
        minotaurs->UpdateWallCollisions(wall_two, 1.0f);
    }

    // make sure player and minotaur exists before you utilize them
    if (!(minotaurs->Empty()) && exists(player)) {

        // if the player and the enemy's field of vision collide, enemy chases player
        minotaurs->UpdateEnemyChase(*player, deltaTime);

        // if the player and an enemy collide, update attack and kill information (in enemy spawner)
        minotaurs->UpdateEnemyContact(*player);

        // delete player condition
        if (minotaurs->getKillStatus()) {
            player = nullptr;
            delete player;
            std::cout << "\nPlayer deleted" << std::endl;
        }
    }
}

void Game_Engine::Render() {
    // clears window
    window->clear(Color(150, 150, 150));

    window->setView(player_view);
    
    if (exists(player))
        player->Draw(*window);

    if (!(minotaurs->Empty()))
        minotaurs->Spawn(*window);

    // temporary wall stuff
    wall_one->Draw(*window);
    wall_two->Draw(*window);

    window->display();
}



/* Initializer functions in order:
 * initVariables(): initilizes all variables, calls initPlayer(), initEnemies(), and initWalls()
 * initPlayer():    initializes main player, sets it to sprite sheet, reports player base health and attack value
 * initEnemies():   initializes enemy objects, sets their position, reports enemy base health and attack value
 * initWalls():     initializes wall objects (2), loads texture for them
 * initWindow():    initializes game window, sets view to be center with player
 */
void Game_Engine::initVariables() {
    // clearing any previous memory, not necessary, but safe
    this->window = nullptr;

    // initializing deltaTime 
    deltaTime = 0.0f;

    std::cout << "[1] Initialized Variables" << std::endl;

    // calls all initializers
    initPlayer();
    initEnemies();
    initWalls();
}

void Game_Engine::initPlayer() {
    this->player = nullptr;

    // loading sprite sheet
    base_movement.loadFromFile("imgs/running_updated.png");

    /* Initializing player
     * &base_movement:      reference to texture
     * Vector2u(12, 4):     sprite sheet is 12x4 images
     * 0.05f:               how fast the animations switch between images
     * 300.0f:              player speed in the relation to objects in the window
     * 200:                 player total health (initial)
     */
    player = new Player(&base_movement, Vector2u(12, 4), 0.05f, 300.0f, 200);

    std::cout << "[2] Initialized Player" << std::endl;

    // reports player statistics
    std::cout << "\t**Player Total Health: " << player->getTotalHealth() << "**" << std::endl;
    std::cout << "\t**Player Attack Value: " << player->getAttackValue() << "**" << std::endl;
}

void Game_Engine::initEnemies() {
    this->minotaurs = nullptr;

    // for random positions
    srand((unsigned) time(0));

    // loading sprite sheet
    min_texture.loadFromFile("imgs/minotaur.png");

    /* Initializing enemy
     * enemy_amount:    how many enemies to spawn
     * 20:              enemy attack value
     * &min_texture:    reference to texture
     * Vector2u(10, 5): sprite sheet is 10x5 images
     * 0.35f:           how fast the animations switch between images
     * 37.0f:          player speed in the relation to objects in the window
     */
    minotaurs = new Enemy_Spawner(minotaur_amount, 20, &min_texture, Vector2u(10, 5), 0.35f, 37.0f);
}

void Game_Engine::initWalls() {
    // temporary wall stuff
    this->wall_one = nullptr;
    this->wall_two = nullptr;

    /* Initializing walls
     * &brickwall:              reference to texture
     * Vector2f(float, float):  size of object
     * Vector2f(float, float):  position in the window
     */
    brickwall.loadFromFile("imgs/wall.png");
    wall_one = new Wall(&brickwall, Vector2f(500.0f, 150.0f), Vector2f(500.0f, 200.0f));
    wall_two = new Wall(&brickwall, Vector2f(500.0f, 150.0f), Vector2f(500.0f, 800.0f));

    std::cout << "[4] Initialized Walls" << std::endl;
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

    std::cout << "[5] Initialized Window" << std::endl;
}


// ResizeView function, used to keep proportions in event of window resizing
void Game_Engine::ResizeView(const RenderWindow& window, View& view) {
    // calculating aspect ratio
    float aspectRatio = float(window.getSize().x) / float (window.getSize().y);
    view.setSize(videoMode.width * aspectRatio, videoMode.height);
}


/* Game Driver functions in order:
 * pollEvents():            gets called in Update(), constantly checks for events (pressing keys, lifting keys, exiting window)
 * WallContactUpdate():     gets called in Update(), updates the contact settings between Individuals and the walls
 * Update():                main driver of this class, updates all game objects (position, health, settings)
 * Render():                main drawing function of this class, draws all updated objects
 */
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
                //std::cout << "Window Resized" << std::endl;
                break;

            // keys have been pressed
            case Event::KeyPressed:
                if (this->ev.key.code == Keyboard::Escape) {
                    window->close();
                    std::cout << "Window Closed (Esc)" << std::endl;
                }
                break;

            // default case
            default:
                break;
        }
    }
}

void Game_Engine::WallContactUpdate(Individual* character, Wall* aWall, float push) {
    // a value of 1.0f is an immovable object, wheres 0.0f would move quickly
    aWall->ColliderCheck(character->GetCollider(), push);
}

#endif  // GAME_ENGINE_H