/* Copyright 2020 Samuel Dunny */
/* Game_Engine class (in header file) */

#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include "Player.h"
#include "Enemy_Spawner.h"
#include "Wall_Corner.h"
#include "Wall_Strip.h"
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
 * Creates various wall instances (TODO make MazeBuilder)
 */

// how many minotaurs to spawn
const static int minotaur_amount = 0;

// factor to see more maze
const static int zoomOutFactor = 3;

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
    WallBuilder* w_str1;
    WallBuilder* w_low1;
    WallBuilder* w_low2;
    WallBuilder* w_str2;
    Texture brickwall_small;
    Texture brickwall_big;

    // using these so animation runs at same rate irrespective of machine
    float deltaTime;
    Clock clock;

    // initializer functions
    void initVariables();
    void initPlayer();
    void initEnemies();
    void initWalls();
    void initWindow();

    // function to keep ratio accurate in event of window resizing
    void ResizeView(const RenderWindow& window, View& view);

    // function responsible for catching and dealing with all Events
    void pollEvents();

    // function to update contact between walls and player (syntactic sugar)
    void WallContactUpdate(Individual* character, WallBuilder* aWall, float push);

    // function to test if Individuals exist (player, enemy, etc.)
    bool exists(Individual* other) {
      if (other != nullptr)
         return true;
      return false;
    }
    
// public attributes 
public:
    
    Game_Engine();      // constructor
    ~Game_Engine();     // destructor
    void Update();      // updates all game objects, states (contact, attack, moving)
    void Render();      // renders all objects and states in window

    // accessor, returns true if window is still open
    const bool running() const { return window->isOpen(); }
};

/* Public Functions in order:
 * Game_Engine():   default constructor, calls all initializer functions
 * ~Game_Engine():  destructor, deletes dynamic objects
 * Update():        updates all game logic (interactions between players, enemies, the environment, and movement in the window)
 * Render():        draws and displays all game objects (player, enemies, walls)
 */
Game_Engine::Game_Engine() {
    std::cout << "-----STARTING INITIALIZATION-----" << std::endl;

    // initializes
    initVariables();
    initWindow();

    std::cout << "-----INITIALIZATION FINISHED-----\n" << std::endl;
}

Game_Engine::~Game_Engine() {
    // Window destructor
    delete this->window;

    // Player destructor
    delete this->player;

    // dont need destructor for enemies

    // WallBuilder children destructors
    delete this->w_str1;
    delete this->w_low1;
    delete this->w_low2;
    delete this->w_str2;
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
        WallContactUpdate(player, w_str1, 1.0f);
        WallContactUpdate(player, w_low1, 1.0f);
        WallContactUpdate(player, w_low2, 1.0f);
        WallContactUpdate(player, w_str2, 1.0f);
    }

    // update enemy information if any exist
    if (!(minotaurs->Empty())) {
        // updates the minotaur's information
        minotaurs->Update(deltaTime);

        // makes wall the immovable object to minotaur
        minotaurs->UpdateWallCollisions(w_str1, 1.0f);
        minotaurs->UpdateWallCollisions(w_low1, 1.0f);
        minotaurs->UpdateWallCollisions(w_low2, 1.0f);
        minotaurs->UpdateWallCollisions(w_str2, 1.0f);
    }

    // make sure player and minotaur exists before you utilize them
    if (!(minotaurs->Empty()) && exists(player)) {
        minotaurs->UpdateHealthBarContact(*player);

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

    // centers window view on player
    window->setView(player_view);
    
    // draws all walls
    w_str1->Draw(*window);
    w_low1->Draw(*window);
    w_low2->Draw(*window);
    w_str2->Draw(*window);

    // draws player (if it exists)
    if (exists(player))
        player->Draw(*window);

    // draws enemies (if they exist)
    if (!(minotaurs->Empty()))
        minotaurs->Spawn(*window);

    // display all drawn objects
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
     * 300              enemy health
     */
    minotaurs = new Enemy_Spawner(minotaur_amount, 20, Vector2f(125.0f,175.0f), &min_texture, Vector2u(10, 5), 0.35f, 37.0f, 150);
}

void Game_Engine::initWalls() {
    // ensure all instance variables are empty
    this->w_str1 = nullptr;
    this->w_low1 = nullptr;
    this->w_low2 = nullptr;
    this->w_str2 = nullptr;

    // scales values to window
    float scale = 250.0f;

    // load wall texture from img/ directory
    brickwall_small.loadFromFile("imgs/wall.png");
    brickwall_big.loadFromFile("imgs/wall_texture.png");

    /* Initializing walls
     * &brickwall:              reference to texture
     * Vector2f(float, float):  size of object
     * Vector2f(float, float):  position in the window
     * 
     * Wall_Corner:
     * bool:                    if corner is facing right
     * bool:                    if corner is facing up
     * 
     * Wall_Strip:
     * bool:                    if strip is horizontal
     */
    
    // straight line (horizontal)
    w_str1 = new Wall_Strip(&brickwall_big, Vector2f(1.0f * scale, 1.0f * scale), Vector2f(2.0f * scale, 0.0f * scale), true);

    // russian G
    w_low1 = new Wall_Corner(&brickwall_big, Vector2f(1.0f * scale, 1.0f * scale), Vector2f(0.0f * scale, 0.0f * scale), true, false);
    w_low2 = new Wall_Corner(&brickwall_big, Vector2f(1.0f * scale, 1.0f * scale), Vector2f(2.0f * scale, 2.0f * scale), true, false);

    // straight line (vertical)
    w_str2 = new Wall_Strip(&brickwall_big, Vector2f(1.0f * scale, 1.0f * scale), Vector2f(0.0f * scale, 2.0f * scale), false);
    
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
    player_view.setSize(Vector2f(videoMode.width * zoomOutFactor, videoMode.height * zoomOutFactor));

    std::cout << "[5] Initialized Window" << std::endl;
}



/* Game Driver functions in order:
 * pollEvents():                        gets called in Update(), constantly checks for events (pressing keys, lifting keys, exiting window)
 * WallContactUpdate():                 gets called in Update(), updates the contact settings between Individuals and the walls
 * ResizeView(RenderWindow&, View&):    used to keep proportions in event of window resizing
 */
void Game_Engine::ResizeView(const RenderWindow& window, View& view) {
    // calculating aspect ratio
    float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
    view.setSize(videoMode.width * aspectRatio * zoomOutFactor, videoMode.height * zoomOutFactor);
}

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

void Game_Engine::WallContactUpdate(Individual* character, WallBuilder* aWall, float push) {
    // a value of 1.0f is an immovable object, wheres 0.0f would move quickly
    aWall->ColliderCheck(character->GetCollider(), push);
}

#endif  // GAME_ENGINE_H